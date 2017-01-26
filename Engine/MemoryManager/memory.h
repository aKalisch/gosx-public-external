#pragma once
#ifndef GSK_ENGINE_MEMORYM
#define GSK_ENGINE_MEMORYM

#include "Common.h"

#include <stdio.h>
#include <stdlib.h>
#include <mach/mach_traps.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach.h>
#include <mach-o/dyld_images.h>
#include <mach-o/loader.h>
#include <libproc.h>
#include <sys/stat.h>
#include <string>

struct sModule {
	sModule(const char* modName) {
        base = 0x0;
        size = 0;
        end = 0x0;
		strcpy(moduleName, modName);
	}
	char moduleName[32];
    uint64_t base;
    size_t size;
    uint64_t end;
};

struct StringChar_t
{
    char buffer[256];
};

class cMemoryManager {
public:
	cMemoryManager(const char* processName);
	sModule getModule(const char* moduleName);
    int get(const char * procname);
    int task(pid_t pid);
    
    template <typename type>
    type read(mach_vm_address_t address, size_t extraSize = sizeof(type), bool debug = false)
    {
        if(debug) {
            printf("read: 0x%llx => size: %lu\n", address, extraSize);
        }
        
        type content;
        
        vm_offset_t data;
        uint32_t sz;
        auto re = vm_read(_PHandle, (vm_address_t)address, extraSize, &data, &sz);
        if(re == KERN_SUCCESS)
        {
            content = (type) *(type *)(data);
            vm_deallocate(current_task(), data, sz);
        }
        return content;
    }
    
    template <typename type>
    bool write(mach_vm_address_t address, type data, bool debug = false)
    {
        if(debug) {
            printf("write: 0x%llx => size: %lu\n", address, sizeof(data));
        }
        
        if(address == 0)
        {
            return false;
        }
        
        auto re = vm_write(_PHandle, address, (vm_offset_t)&data, sizeof(data));
        if (re == KERN_SUCCESS)
        {
            return true;
        }
        
        return false;
    }
    
    Byte * readModule(vm_address_t moduleStart, size_t moduleSize);
    std::string readstring(mach_vm_address_t address);
    
    int GetPid();
    int GetTask();

private:
    ~cMemoryManager();
	const char* _processName;
	int _PID;
	int _PHandle;
    bool retrieveModule(const char* moduleName);
	std::vector<sModule> loadedModules;
    Byte* pRemote;
    size_t bufferSize;
    uint64_t moduleStart;
};

#endif
