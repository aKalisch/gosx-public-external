#pragma once
#ifndef GSK_ENGINE_OFFSETMGR
#define GSK_ENGINE_OFFSETMGR

#include "../MemoryManager/memory.h"
#include "../MemoryManager/pattern.h"
#include "offsetStructs.h"

class cOffsetManager {
public:
	cOffsetManager(cMemoryManager* memManager);
    sClientOffsets client;
    sEngineOffsets engine;

private:
	cMemoryManager* memoryManager;
};

#endif
