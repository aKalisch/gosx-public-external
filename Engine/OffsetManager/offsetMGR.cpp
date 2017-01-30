#include "offsetMGR.h"

bool debug = false;

cOffsetManager::cOffsetManager(cMemoryManager* memManager) {
	memoryManager = memManager;
    if(memoryManager->GetPid() != -1 && memoryManager->GetTask() != 0) {
        sModule clientDLL = memoryManager->getModule("/client.dylib");
        sModule engineDLL = memoryManager->getModule("/engine.dylib");
    
        cPatternScanner * clientScanner = new cPatternScanner(memoryManager, clientDLL);
        cPatternScanner * engineScanner = new cPatternScanner(memoryManager, engineDLL);
    
        client.m_dwGlowManager = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x48\x8D\x3D\x00\x00\x00\x05\xE8\x00\x00\x00\x00\x85\xC0\x0F\x84\x00\x00\x00\x00\x48\xC7\x00\x00\x00\x00\x00\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00",
            "xxx???xx????xxxx????xx?????????xx?????",
            0x22
        ) + 0x4;
    
        client.m_dwEntityList = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x48\x8D\x1D\x00\x00\x00\x00\x48\x89\x00\xE8\x28\xD6\x00\x00",
            "xxx????xx?xxx??",
            0x3
        ) + 0x2C;
    
        client.m_dwLocalPlayer = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x89\xD6\x41\x89\x00\x49\x89\x00\x48\x8B\x1D\x00\x00\x00\x00\x48\x85\xDB\x74\x00",
            "xxxx?xx?xxx????xxxx?",
            0xB
        ) + 0x4;
    
        client.m_dwForceAttack = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x8B\x00\x00\x00\x00\x00\xA8\x00\x00\x95\xC1\x00\xB6\xC9\x09\xD1\x44\x89",
            "x?????x??xx?xxxxxx",
            0x2
        ) + 0x4;
    
        client.m_dwForceAttack2 = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x8B\x00\x00\x00\x00\x00\xA8\x00\x00\x95\xC1\x00\xB6\xC9\x09\xD1\x44\x89",
            "x?????x??xx?xxxxxx",
            0x2
        ) + 0x10;
    
        client.m_dwForceDuck = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x21\xC1\x89\x00\x00\x00\x00\x00\x8B\x00\x00\x00\x00\x00\x89\xD1\x83\x00\x00",
            "xxx?????x?????xxx??",
            0x4
        ) + 0x4;
    
        client.m_dwForceJump = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x44\x89\xE1\xC1\xE9\x00\x83\xE1\x00\x83\xF1\x00\x21\xC1\x89\x0D\x00\x00\x00\x00\x8B\x05\x00\x00\x00\x00\x89\xD1\x83\xC9\x00\xA8\x00\x0F\x44\xCA\x44\x89\xE2\xD1\xEA\x83\xE2\x00",
            "xxxxx?xx?xx?xxxx????xx????xxxx?x?xxxxxxxxxx?",
            0x16
        ) + 0x4;
    
        client.m_dwForceAlt1 = client.m_dwForceDuck + 0xC;
        client.m_dwForceAlt2 = client.m_dwForceAlt1 + 0xC;
    
        client.m_dwRadarBase = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x50\x49\x89\xFD\x49\x8B\x7D\x00\x48\x85\xFF\x74\x56\x41\x8B\x75\x00\xE8\x6D\x00\x00\x00\x41\x88\xC6\x45\x84\xF6\x75\x45\x41\x80\xF6\x00\x45\x8B\x65\x00\x45\x85\xE4\x7E\x3B\x31\xDB\x4C\x8D\x3D\x00\x00\x00\x00\x66\x66\x66\x66\x66\x66\x2E\x0F\x1F\x84\x00\x00\x00\x00\x00",
            "xxxxxxxxxxxxxxxxxxxx?xxxxxxxx?xxxxxxxxxxxxxxxx?xxx?xxxxxxxxxx????xxxxxxxxxxxxxxx",
            0x3D
        ) + 0x3C;
        
        client.m_dwPlayerResource = clientDLL.base + clientScanner->getPointer(
            (Byte*)"\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x83\xEC\x00\x48\x89\xF3\x48\x8D\x7D\xB0\xBE\x00\x00\x00\x00\xE8\xAE\x2F\xDC\xFF\x4C\x8B\x75\xD0\x48\x8B\x03\x48\x8B\x80\x00\x00\x00\x00\x48\x89\xDF\xFF\xD0\x41\x80\x4E\x00\x00\x49\x89\x46\x00\x48\x8D\x1D\x00\x00\x00\x00\x48\x8B\x3B\x48\x8B\x07\x48\x8B\x80\x00\x00\x00\x00\xFF\xD0\x4C\x8D\x25\x00\x00\x00\x00",
            "xxxxxxxxxxxxxxxx?xxxxxxxx????xxxxxxxxxxxxxxx????xxxxxxxx??xxx?xxx????xxxxxxxxx????xxxxx????",
            0x57
        ) + 0x4;
    
        engine.m_dwCEngineClient = engineDLL.base + engineScanner->getPointer(
            (Byte*)"\x55\x48\x89\xE5\x48\x8B\x00\x00\x00\x00\x00\x48\x83\x00\x00\x5D\xC3\x66\x66\x66\x66\x66\x66\x2E\x0F\x1F\x84\x00\x00\x00\x00\x00",
            "xxxxxx?????xx??xxxxxxxxxxxxxxxxx",
            0x7
        ) + 0x4;
    
        engine.m_szGameDirectory = engineDLL.base + engineScanner->getPointer(
            (Byte*)"\x55\x48\x89\xE5\x41\x57\x41\x56\x41\x55\x41\x54\x53\x48\x81\xEC\x00\x00\x00\x00\x48\x89\xF3\x49\x89\xFE\x4C\x8B\x2D\x00\x00\x00\x00\x49\x8B\x45\x00\x48\x89\x45\x00\x48\x8D\x3D\x00\x00\x00\x00",
            "xxxxxxxxxxxxxxxx????xxxxxxxxx????xxxxxxx?xxx????",
            0x2C
        ) + 0x4;
        
        if(debug) {
            printf("client.m_dwGlowManager      : 0x%llx\n", client.m_dwGlowManager);
            printf("client.m_dwEntityList       : 0x%llx\n", client.m_dwEntityList);
            printf("client.m_dwLocalPlayer      : 0x%llx\n", client.m_dwLocalPlayer);
            printf("client.m_dwForceAttack      : 0x%llx\n", client.m_dwForceAttack);
            printf("client.m_dwForceAttack2     : 0x%llx\n", client.m_dwForceAttack2);
            printf("client.m_dwForceDuck        : 0x%llx\n", client.m_dwForceDuck);
            printf("client.m_dwForceJump        : 0x%llx\n", client.m_dwForceJump);
            printf("client.m_dwForceAlt1        : 0x%llx\n", client.m_dwForceAlt1);
            printf("client.m_dwForceAlt2        : 0x%llx\n", client.m_dwForceAlt2);
            printf("client.m_dwRadarBase        : 0x%llx\n", client.m_dwRadarBase);
            printf("client.m_dwPlayerResource   : 0x%llx\n", client.m_dwPlayerResource);
            printf("engine.m_dwCEngineClient    : 0x%llx\n", engine.m_dwCEngineClient);
            printf("engine.m_szGameDirectory    : 0x%llx\n", engine.m_szGameDirectory);
            exit(0);
        }
    }
}
