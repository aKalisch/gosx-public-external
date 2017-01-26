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

void cExtraManager::AutoPistolSwitch()
{
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

void cExtraManager::AutoPistolToKnifeSwitch()
{
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

void cExtraManager::KnifeBot()
{
    for(int i = 1; i < engineFactory->GetEngineClient()->getMaxPlayers(); i++) {
        int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
        if(!cWeaponManager::isKnife(currentWeapon)) {
            continue;
        }
        
        cEntityManager* entity = engineFactory->GetEntity(i);
        if(!entity->isValidLivePlayer()) {
            continue;
        }
        
        if(LocalPlayer->GetTeam() == entity->GetTeam()) {
            continue;
        }
        
        Vector hitbox = entity->GetBonePosition(5);
        float dist = cMath::VecDist(LocalPlayer->GetPositionOffset(), hitbox);
        
        if(dist > 64) {
            continue;
        }
        
        float fov = cMath::GetFov(LocalPlayer->GetViewAngle(), LocalPlayer->GetPositionOffset(), hitbox);
        
        if(fov > 50) {
            continue;
        }
        
        LocalPlayer->forceAttack2();
    }
}

void cExtraManager::AutoDuck()
{
    if(
       !engineFactory->GetKeyManager()->isPressed(kVK_Shift) &&
       !engineFactory->GetKeyManager()->isPressed(kVK_Control)
    ) {
        LocalPlayer->forceDuck();
        return;
    }
    
    if(LocalPlayer->isInAir()) {
        return;
    }
    
    if(LocalPlayer->GetHasMovedSinceSpawn()) {
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
    
    int shotsFiredAmount = 1;
    
    if(LocalPlayer->GetShotsFired() < shotsFiredAmount) {
        return;
    }
    
    if(LocalPlayer->isCrouching()) {
        return;
    }
    
    if(LocalPlayer->GetActiveWeaponData().m_clip1 == 0 && LocalPlayer->GetShotsFired() == 0) {
        LocalPlayer->forceDuck();
        return;
    }
    
    LocalPlayer->forceDuck(true);
}
