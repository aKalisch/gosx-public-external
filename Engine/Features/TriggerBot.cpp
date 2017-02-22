//
//  TriggerBot.cpp
//  GOSXV3
//
//  Created by Andre Kalisch on 26.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "TriggerBot.h"

cTriggerBot::cTriggerBot(cEngine* engine) {
    engineFactory = engine;
    hitboxMngr = new cHitboxManager();
    bsp = engineFactory->GetBspParser();
}

bool cTriggerBot::canHit(Vector locPostOffset, QAngle locViewAngle, Vector hitboxMin, Vector hitboxMax) {
    Vector viewDirection = cMath::AngleToDirection(locViewAngle);
    cViewRay* ray = new cViewRay(locPostOffset, viewDirection);
    float distance;
    
    if (!ray->Trace(hitboxMin, hitboxMax, distance))
    {
        delete ray;
        return false;
    }
    delete ray;
    return true;
}

void cTriggerBot::apply() {
    LocalPlayer = engineFactory->GetLocalEntity();
    if(!LocalPlayer->isValidLivePlayer()) {
        return;
    }
    
    int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
    if (
        cWeaponManager::isC4(currentWeapon) ||
        cWeaponManager::isKnife(currentWeapon) ||
        cWeaponManager::isGrenade(currentWeapon)
    ) {
        return;
    }
    if (LocalPlayer->isPressingAlt()) {
        eTeam lTeam = LocalPlayer->GetTeam();
        Vector posOffset = LocalPlayer->GetPositionOffset();
        QAngle locViewAngle = LocalPlayer->GetViewAngle();
        for(int i = 1; i < engineFactory->GetEngineClient()->getMaxPlayers(); i++) {
            cEntityManager* entity = engineFactory->GetEntity(i);
            if(!entity->isValidLivePlayer())
            {
                continue;
            }
            
            if(lTeam == entity->GetTeam()) {
                delete entity;
                continue;
            }
            
            Hitbox_t hitbox;
            Vector entityHitbox;
            bool triggerCanHit =  false;
            for(int b = BONE_PELVIS; b <= BONE_HEAD; b++) {
                hitbox = hitboxMngr->getHitboxByBone(b);
                
                if(b != hitbox.iBone) {
                    continue;
                }
                
                entityHitbox = entity->GetBonePosition(hitbox.iBone);
                if(!bsp->isVisible(posOffset, entityHitbox)) {
                    continue;
                }
                
                Vector hitboxMin = entityHitbox + hitbox.vMin;
                Vector hitboxMax = entityHitbox + hitbox.vMax;
                
                if(!canHit(posOffset, locViewAngle, hitboxMin, hitboxMax)) {
                    continue;
                }
                
                triggerCanHit = true;
            }
            
            if(!triggerCanHit) {
                delete entity;
                continue;
            }
            
            LocalPlayer->forceAttack();
            delete entity;
            usleep(cWeaponManager::getDelay(currentWeapon) * 10000);
        }
    }
}

void cTriggerBot::burstShot(int delay) {
    usleep(delay);
    LocalPlayer->forceAttack();
    usleep(delay);
    LocalPlayer->forceAttack();
    usleep(delay);
    LocalPlayer->forceAttack();
}

