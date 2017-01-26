//
//  Extras.hpp
//  GOSXV3
//
//  Created by Andre Kalisch on 26.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Extras_hpp
#define Extras_hpp

#include "engine.h"
#include "sdk.h"
#include "weapons.h"

class cExtraManager
{
public:
    cExtraManager(cEngine* engine);
    void FlashReducer();
    void AutoPistolSwitch();
    void AutoPistolToKnifeSwitch();
    void KnifeBot();
    void AutoDuck();
private:
    cEngine* engineFactory;
    cEntityManager* LocalPlayer;
    cSettingsManager* settingsManager;
};

#endif /* Extras_hpp */
