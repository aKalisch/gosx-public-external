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

bool cTriggerBot::canHit(Vector hitboxMin, Vector hitboxMax) {
    Vector viewDirection = cMath::AngleToDirection(LocalPlayer->GetViewAngle());
    cViewRay* ray = new cViewRay(LocalPlayer->GetPositionOffset(), viewDirection);
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
        for(int i = 1; i < engineFactory->GetEngineClient()->getMaxPlayers(); i++)
        {
            cEntityManager* entity = engineFactory->GetEntity(i);
            if(!entity->isValidLivePlayer())
            {
                continue;
            }
            
            Hitbox_t hitbox;
            Vector entityHitbox;
            bool triggerCanHit =  false;
            for(int b = BONE_PELVIS; b <= BONE_HEAD; b++)
            {
                hitbox = hitboxMngr->getHitboxByBone(b);
                
                if(b != hitbox.iBone) {
                    continue;
                }
                
                entityHitbox = entity->GetBonePosition(hitbox.iBone);
                
                if(!bsp->isVisible(LocalPlayer->GetPositionOffset(), entityHitbox)) {
                    continue;
                }
                
                Vector hitboxMin = entityHitbox + hitbox.vMin;
                Vector hitboxMax = entityHitbox + hitbox.vMax;
                
                if(!canHit(hitboxMin, hitboxMax)) {
                    continue;
                }
                
                triggerCanHit = true;
            }
            
            if(!triggerCanHit) {
                continue;
            }
            
            if (
                !cWeaponManager::isPistol(currentWeapon) &&
                !cWeaponManager::isSniper(currentWeapon) &&
                !cWeaponManager::isShotgun(currentWeapon) &&
                settingsManager->GetTriggerBurstShot()
            ) {
                burstShot(cWeaponManager::getDelay(currentWeapon) * 1000);
            } else {
                usleep(cWeaponManager::getDelay(currentWeapon) * 1000);
                LocalPlayer->forceAttack();
            }
            
            delete entity;
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

