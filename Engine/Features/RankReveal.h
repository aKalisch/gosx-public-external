//
//  RankReveal.hpp
//  GOSXV3
//
//  Created by Andre Kalisch on 27.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef RankReveal_hpp
#define RankReveal_hpp

#include "engine.h"
#include "sdk.h"
#include "weapons.h"

class cRankReveal
{
public:
    cRankReveal(cEngine* engine);
    void run();
private:
    cEngine* engineFactory;
    cSettingsManager* settingsManager;
};

#endif /* RankReveal_hpp */
