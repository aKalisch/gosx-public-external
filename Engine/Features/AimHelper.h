//
//  AimHelper.h
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef AimHelper_h
#define AimHelper_h

#include "engine.h"
#include "sdk.h"
#include "weapons.h"

class cAimHelper
{
public:
    cAimHelper(cEngine* engine);
    int getBestBone(cEntityManager* entity);
    int findTarget();
    void VelocityComp(Vector& EnemyPos, Vector EnemyVecVelocity, Vector PlayerVecVelocity);
    void aimTarget(cEntityManager* enemy, int entityIndex);
    void reset();
    void apply();
protected:
    int m_lockedEntity = -5;
    int m_lockedBone = -5;
private:
    cEngine* engineFactory;
    cEntityManager* LocalPlayer;
    cHitboxManager* hitboxManager;
    cSettingsManager* settingsManager;
};


#endif /* AimHelper_h */
