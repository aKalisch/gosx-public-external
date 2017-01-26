#include "memory.h"

cMemoryManager::cMemoryManager(const char* processName) {
	_processName = processName;
    _PID = get(_processName);
    _PHandle = task(_PID);
}

cMemoryManager::~cMemoryManager() {
    
}

int cMemoryManager::get(const char* procname) {
    pid_t pids[1024];
    int numberOfProcesses = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    for (int i = 0; i < numberOfProcesses; ++i)
    {
        if (pids[i] == 0) { continue; }
        char name[1024];
        proc_name(pids[i], name, sizeof(name));
        if (!strncmp(name, (const char *)procname, sizeof(procname)))
        {
            return pids[i];
        }
    }
    return -1;
}

int cMemoryManager::task(pid_t pid)
{
    task_t task;
    task_for_pid(current_task(), pid, &task);
    
    return task;
}

sModule cMemoryManager::getModule(const char* moduleName) {
    for (auto m : loadedModules) {
        if (!strcmp(moduleName, m.moduleName)) {
            return m;
        }
    }
    int localAttempts = 0;
    while (!retrieveModule(moduleName)) {
        if (localAttempts > 120) {
            return sModule(moduleName);
        }
        localAttempts++;
        usleep(1000000);
    }
    return loadedModules.back();
}

bool cMemoryManager::retrieveModule(const char* moduleName) {
    
    struct task_dyld_info dyld_info;
    mach_vm_address_t address;
    mach_msg_type_number_t count = TASK_DYLD_INFO_COUNT;
    if (task_info(_PHandle, TASK_DYLD_INFO, (task_info_t)&dyld_info, &count) == KERN_SUCCESS)
    {
        address = dyld_info.all_image_info_addr;
    }
    
    struct dyld_all_image_infos *dyldaii;
    mach_msg_type_number_t size = sizeof(dyld_all_image_infos);
    vm_offset_t readMem;
    kern_return_t kr = vm_read(_PHandle, address, size, &readMem, &size);
    if (kr != KERN_SUCCESS)
    {
        return false;
    }
    
    dyldaii = (dyld_all_image_infos *) readMem;
    int imageCount = dyldaii->infoArrayCount;
    mach_msg_type_number_t dataCnt = imageCount * 24;
    struct dyld_image_info *g_dii = NULL;
    g_dii = (struct dyld_image_info *) malloc (dataCnt);
    // 32bit bs 64bit
    kern_return_t kr2 = vm_read(_PHandle, (mach_vm_address_t)dyldaii->infoArray, dataCnt, &readMem, &dataCnt);
    if (kr2)
    {
        return false;
    }
    struct dyld_image_info *dii = (struct dyld_image_info *) readMem;
    for (int i = 0; i < imageCount; i++)
    {
        dataCnt = 1024;
        vm_read(_PHandle, (mach_vm_address_t)dii[i].imageFilePath, dataCnt, &readMem, &dataCnt);
        char *imageName = (char *)readMem;
        if (imageName)
        {
            g_dii[i].imageFilePath = strdup(imageName);
        }
        else
        {
            g_dii[i].imageFilePath = NULL;
        }
        g_dii[i].imageLoadAddress = dii[i].imageLoadAddress;
        if (strstr(imageName, moduleName) != NULL)
        {
            struct stat st;
            stat(imageName, &st);
            
            sModule tempModule(moduleName);
            tempModule.base = (mach_vm_address_t)dii[i].imageLoadAddress;
            tempModule.size = st.st_size;
            tempModule.end = tempModule.base + tempModule.size;
            loadedModules.push_back(tempModule);
            
            return true;
        }
    }
    
    return false;
}

Byte * cMemoryManager::readModule(vm_address_t moduleStart, size_t moduleSize)
{
    uint8_t * buffer = nullptr;
    vm_offset_t readMem;
    mach_msg_type_number_t sizeMax = (mach_msg_type_number_t)moduleSize;
    vm_read(_PHandle, (vm_address_t)moduleStart, sizeMax, &readMem, &sizeMax);
    uint64_t address = (uint64_t)readMem;
    buffer = (uint8_t *)address;
    
    return buffer;
}

std::string cMemoryManager::readstring(mach_vm_address_t address)
{
    std::string str;
    StringChar_t temp = read<StringChar_t>(address);
    for(int c = 0; c < sizeof(StringChar_t); c++)
    {
        if(temp.buffer[c] == '\0')
        {
            break;
        }
        str += temp.buffer[c];
    };
    return str;
}

int cMemoryManager::GetPid() {
    return _PID;
}

int cMemoryManager::GetTask() {
    return _PHandle;
}
