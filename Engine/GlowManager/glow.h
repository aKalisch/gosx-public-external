//
//  glow.hpp
//  gosx
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef glow_hpp
#define glow_hpp

#include "memory.h"
#include "offsetMGR.h"

class cGlowManager {
public:
    cGlowManager(cMemoryManager* memMngr, cOffsetManager* offMngr);
    int GetGlowCount();
    sGlowEntity GetGlowEntity(int index);
private:
    cMemoryManager* mem;
    cOffsetManager* off;
    uint64_t glowObjectManagerPointer;
};

#endif /* glow_hpp */
