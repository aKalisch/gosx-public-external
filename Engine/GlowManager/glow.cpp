//
//  glow.cpp
//  gosx
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "glow.h"

cGlowManager::cGlowManager(cMemoryManager* memMngr, cOffsetManager* offMngr) {
    mem = memMngr;
    off = offMngr;
    glowObjectManagerPointer = mem->read<uint64_t>(off->client.m_dwGlowManager);
}

int cGlowManager::GetGlowCount() {
    return mem->read<int>(off->client.m_dwGlowManager + off->client.m_dwGlowCount);
}

sGlowEntity cGlowManager::GetGlowEntity(int index) {
    return mem->read<sGlowEntity>(glowObjectManagerPointer + (off->client.m_dwGlowLoopDistance * index));
}
