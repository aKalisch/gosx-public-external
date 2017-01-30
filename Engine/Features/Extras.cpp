//
//  Extras.cpp
//  GOSXV3
//
//  Created by Andre Kalisch on 26.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "Extras.h"

cExtraManager::cExtraManager(cEngine* engine) {
    engineFactory = engine;
    settingsManager = engineFactory->GetSettingsManager();
    LocalPlayer = engine->GetLocalEntity();
}

void cExtraManager::FlashReducer() {
    if(!LocalPlayer->isValidLivePlayer()) {
        return;
    }
    
    float maxFlashAlpha = settingsManager->GetMaxFlashAlpha();
    float currAlpha = LocalPlayer->GetFlashAlpha();
    if(currAlpha == 0) {
        return;
    }
    
    if(currAlpha == maxFlashAlpha) {
        return;
    }
    
    LocalPlayer->setFlashAlpha(settingsManager->GetMaxFlashAlpha());
}

void cExtraManager::AutoPistolSwitch() {
    if(!LocalPlayer->isValidLivePlayer()) {
        return;
    }
    
    int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
    if(
       !cWeaponManager::isPistol(currentWeapon) &&
       !cWeaponManager::isKnife(currentWeapon) &&
       LocalPlayer->GetActiveWeaponData().m_clip1 == 0 &&
       LocalPlayer->isAttacking() &&
       LocalPlayer->GetHealth() > 0 &&
       LocalPlayer->GetShotsFired() == 0
    ) {
        engineFactory->GetKeyManager()->sendKey(kVK_ANSI_2, 5000);
    }
}

void cExtraManager::AutoPistolToKnifeSwitch() {
    if(!LocalPlayer->isValidLivePlayer()) {
        return;
    }
    
    int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
    if(
       cWeaponManager::isPistol(currentWeapon) &&
       LocalPlayer->GetActiveWeaponData().m_clip1 == 0 &&
       LocalPlayer->isAttacking() &&
       LocalPlayer->GetHealth() > 0 &&
       LocalPlayer->GetShotsFired() == 0
    ) {
        engineFactory->GetKeyManager()->sendKey(kVK_ANSI_3, 5000);
    }
}

void cExtraManager::KnifeBot() {
    if(!LocalPlayer->isValidLivePlayer()) {
        return;
    }
    
    int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
    if(!cWeaponManager::isKnife(currentWeapon)) {
        return;
    }
    
    eTeam lTeam = LocalPlayer->GetTeam();
    Vector posOffset = LocalPlayer->GetPositionOffset();
    QAngle locViewAngle = LocalPlayer->GetViewAngle();
    for(int i = 1; i < engineFactory->GetEngineClient()->getMaxPlayers(); i++) {
        cEntityManager* entity = engineFactory->GetEntity(i);
        if(!entity->isValidLivePlayer()) {
            continue;
        }
        
        if(lTeam == entity->GetTeam()) {
            delete entity;
            continue;
        }
        entity->setBoneMatrixBones();
        Vector hitbox = entity->GetBonePosition(5);
        float fov = cMath::GetFov(locViewAngle, posOffset, hitbox);
        if(fov > 30) {
            delete entity;
            continue;
        }
        
        float dist = cMath::VecDist(posOffset, hitbox);
        if(dist > 67) {
            delete entity;
            continue;
        }
        
        LocalPlayer->forceAttack2();
        delete entity;
    }
}

void cExtraManager::AutoDuck() {
    if(!LocalPlayer->isValidLivePlayer()) {
        return;
    }
    
    int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
    if(
       cWeaponManager::isGrenade(currentWeapon) ||
       cWeaponManager::isC4(currentWeapon) ||
       cWeaponManager::isKnife(currentWeapon) ||
       cWeaponManager::isSniper(currentWeapon) ||
       cWeaponManager::isShotgun(currentWeapon)
    ) {
        return;
    }
    
    if(LocalPlayer->isInAir()) {
        return;
    }
    
    if(LocalPlayer->GetHasMovedSinceSpawn()) {
        return;
    }
    
    if(
       !engineFactory->GetKeyManager()->isPressed(kVK_Shift) &&
       !engineFactory->GetKeyManager()->isPressed(kVK_Control)
    ) {
        LocalPlayer->forceDuck();
        return;
    }
    
    int shotsFiredAmount = 1;
    int currShotsFired = LocalPlayer->GetShotsFired();
    
    if(currShotsFired < shotsFiredAmount) {
        return;
    }
    
    if(LocalPlayer->isCrouching()) {
        return;
    }
    
    if(LocalPlayer->GetActiveWeaponData().m_clip1 == 0 && currShotsFired == 0) {
        LocalPlayer->forceDuck();
        return;
    }
    
    LocalPlayer->forceDuck(true);
}
