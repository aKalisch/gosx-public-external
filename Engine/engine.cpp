#include "engine.h"

cEngine::cEngine(const char* processName) {
    _pName = processName;
    _initEngine(_pName);
}

void cEngine::Refresh() {
    _initEngine(_pName);
}

void cEngine::_initEngine(const char* processName) {
    Mem = new cMemoryManager(_pName);
    Offset = new cOffsetManager(Mem);
    SettingsManager = new cSettingsManager();
    EngineClient = new cEngineClient(Mem, Offset);
    if(EngineClient->isInGame()) {
        if(currentMap == "") {
            currentMap = EngineClient->GetMapFile();
            BspParser = new cBspParser(EngineClient->GetGameDirectory(), currentMap);
            BspParser->readBSP();
            GlowManager = new cGlowManager(Mem, Offset);
            RadarManager = new cRadarManager(Mem, Offset);
            PlayerResource = new cPlayerResource(Mem, Offset);
        }
    }
}

cMemoryManager* cEngine::GetMemory() {
    return Mem;
}

cOffsetManager* cEngine::GetOffsets() {
    return Offset;
}

cEntityManager* cEngine::GetEntity(int eID) {
	return new cEntityManager(eID, Mem, Offset);
}

cEntityManager* cEngine::GetLocalEntity() {
	return new cEntityManager(Mem, Offset);
}

cEntityManager* cEngine::DefineGlowEntity(uint64_t entityAddress) {
    return new cEntityManager(entityAddress, Mem, Offset);
}

cEngineClient* cEngine::GetEngineClient() {
    return EngineClient;
}

cKeyManager* cEngine::GetKeyManager() {
    return KeyManager;
}

cGlowManager* cEngine::GetGlowManager() {
    return GlowManager;
}

cBspParser* cEngine::GetBspParser() {
    if(currentMap != "" && currentMap != BspParser->GetMapFile()) {
        currentMap = EngineClient->GetMapFile();
        BspParser->SetMapFile(currentMap);
        BspParser->readBSP();
    }
    return BspParser;
}

cSettingsManager* cEngine::GetSettingsManager() {
    return SettingsManager;
}

cRadarManager* cEngine::GetRadarManager() {
    return RadarManager;
}

cPlayerResource* cEngine::GetPlayerResource() {
    return PlayerResource;
}

int cEngine::GetPid() {
    return Mem->GetPid();
}

int cEngine::GetTask() {
    return Mem->GetTask();
}

