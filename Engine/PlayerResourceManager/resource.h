//
//  resource.hpp
//  GOSXV3
//
//  Created by Andre Kalisch on 29.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef resource_hpp
#define resource_hpp

#include "Common.h"

#include "memory.h"
#include "offsetMGR.h"

static const char *Ranks[] =
{
    "-",
    "Silver I",
    "Silver II",
    "Silver III",
    "Silver IV",
    "Silver Elite",
    "Silver Elite Master",
    "Gold Nova I",
    "Gold Nova II",
    "Gold Nova III",
    "Gold Nova Master",
    "Master Guardian I",
    "Master Guardian II",
    "Master Guardian Elite",
    "Distinguished Master Guardian",
    "Legendary Eagle",
    "Legendary Eagle Master",
    "Supreme Master First Class",
    "The Global Elite"
};

class cPlayerResource {
public:
    cPlayerResource(cMemoryManager* memMngr, cOffsetManager* offMngr);
    int GetKills(int index);
    int GetAssists(int index);
    int GetDeaths(int index);
    int GetArmor(int index);
    const char* GetCompetitiveRank(int index);
    int GetCompetitiveWins(int index);
    bool hasHelmet(int index);
    bool hasDefuser(int index);
    bool isConnected(int index);
private:
    cMemoryManager* mem;
    cOffsetManager* offset;
    uint64_t PlayerResource;
};

#endif /* resource_hpp */
