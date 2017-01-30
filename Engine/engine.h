#pragma once
#ifndef GSK_ENGINE
#define GSK_ENGINE

#include "Common.h"

#include "memory.h"
#include "offsetMGR.h"

#include "entity.h"
#include "engineClient.h"
#include "glow.h"
#include "radar.h"
#include "resource.h"

#include "Keys.h"
#include "bsp.h"
#include "settings.h"

class cEngine {
public:
	cEngine(const char* processName);
    void Refresh();
    void _initEngine(const char* processName);
	cMemoryManager* Mem;
    cMemoryManager* GetMemory();
	cOffsetManager* Offset;
    cOffsetManager* GetOffsets();
    cEngineClient* EngineClient;
    cEngineClient* GetEngineClient();
    cKeyManager* KeyManager;
    cKeyManager* GetKeyManager();
	cEntityManager* GetEntity(int eID);
    cEntityManager* DefineGlowEntity(uint64_t entityAddress);
	cEntityManager* GetLocalEntity();
    cBspParser* BspParser;
    cBspParser* GetBspParser();
    cSettingsManager* SettingsManager;
    cSettingsManager* GetSettingsManager();
    cGlowManager* GlowManager;
    cGlowManager* GetGlowManager();
    cRadarManager* RadarManager;
    cRadarManager* GetRadarManager();
    cPlayerResource* PlayerResource;
    cPlayerResource* GetPlayerResource();
    
    int GetPid();
    int GetTask();
private:
    const char* _pName;
    std::string currentMap = "";
};

#endif
