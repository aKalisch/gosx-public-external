//
//  radar.hpp
//  GOSXV3
//
//  Created by Andre Kalisch on 27.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef radar_hpp
#define radar_hpp

#include "Common.h"

#include "memory.h"
#include "offsetMGR.h"

struct PlayerChar_t
{
    wchar_t name[32];
};

class cRadarManager {
public:
    cRadarManager(cMemoryManager* memMngr, cOffsetManager* offMngr);
    uint64_t GetEntityBase(int index);
    PlayerChar_t GetEntityName(int index);
private:
    uint64_t RadarBase;
    cMemoryManager* mem;
    cOffsetManager* off;
};

#endif /* radar_hpp */
