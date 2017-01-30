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
    int getBestBone(Vector posOffset, QAngle locViewAngle, cEntityManager* entity);
    cEntityManager* findTarget(Vector posOffset, QAngle locViewAngle);
    void VelocityComp(Vector& EnemyPos, Vector EnemyVecVelocity, Vector PlayerVecVelocity);
    void aimTarget(Vector posOffset, QAngle locViewAngle, cEntityManager* enemy);
    void reset();
    void apply();
protected:
    cEntityManager* m_lockedEntity = nullptr;
    int m_lockedBone = -5;
private:
    cEngine* engineFactory;
    cEntityManager* LocalPlayer = nullptr;
    cHitboxManager* hitboxManager;
    cSettingsManager* settingsManager;
    cBspParser* bsp;
};


#endif /* AimHelper_h */
