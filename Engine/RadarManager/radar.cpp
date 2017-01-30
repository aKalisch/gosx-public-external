//
//  radar.cpp
//  GOSXV3
//
//  Created by Andre Kalisch on 27.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "radar.h"

cRadarManager::cRadarManager(cMemoryManager* memMngr, cOffsetManager* offMngr) {
    mem = memMngr;
    off = offMngr;
    uint64_t radarPointer = mem->read<uint64_t>(off->client.m_dwRadarBase);
    RadarBase = mem->read<uint64_t>(radarPointer + off->client.m_dwRadarStructBase) + off->client.m_dwRadarArray;
}

uint64_t cRadarManager::GetEntityBase(int index) {
    return RadarBase + off->client.m_dwRadarDistance * index;
}

PlayerChar_t cRadarManager::GetEntityName(int index) {
    return mem->read<PlayerChar_t>(GetEntityBase(index) + off->client.m_szRadarName);
}
