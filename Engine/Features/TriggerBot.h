//
//  TriggerBot.hpp
//  GOSXV3
//
//  Created by Andre Kalisch on 26.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef TriggerBot_hpp
#define TriggerBot_hpp

#include "engine.h"
#include "sdk.h"
#include "weapons.h"
#include "ray.h"

class cTriggerBot
{
public:
    cTriggerBot(cEngine* engine);
    void apply();
private:
    bool canHit(Vector locPostOffset, QAngle locViewAngle, Vector hitboxMin, Vector hitboxMax);
    void burstShot(int delay);
    cEngine* engineFactory;
    cEntityManager* LocalPlayer;
    cSettingsManager* settingsManager;
    cHitboxManager* hitboxMngr;
    cBspParser* bsp;
};

#endif /* TriggerBot_hpp */
