//
//  AimHelper.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "AimHelper.h"

cAimHelper::cAimHelper(cEngine* engine) {
    engineFactory = engine;
    settingsManager = engineFactory->GetSettingsManager();
    hitboxManager = new cHitboxManager();
    bsp = engineFactory->GetBspParser();
}

int cAimHelper::getBestBone(cEntityManager* entity)
{
    int bestBone = 7;
    float closestBone = settingsManager->GetFieldOfView();
    for( int i = 0; i < HITBOX_MAX; i++ )
    {
        Hitbox_t hitbox = hitboxManager->getHitbox(i);
        Vector bone = entity->GetBonePosition(hitbox.iBone);
        cBspParser* bsp = engineFactory->GetBspParser();
        if(!bsp->isVisible(LocalPlayer->GetPositionOffset(), bone))
        {
            continue;
        }
        
        float fov = cMath::GetFov(
            LocalPlayer->GetViewAngle(),
            LocalPlayer->GetPositionOffset(),
            bone
        );
        
        if(fov < closestBone)
        {
            bestBone = hitbox.iBone;
            closestBone = fov;
        }
    }
    
    return bestBone;
}

int cAimHelper::findTarget()
{
    float m_bestfov = settingsManager->GetFieldOfView();
    float m_bestdist = 8192.0f;
    float m_bestthreat = 0.0f;
    int m_bestent = -1;
    cEngineClient* engineClient = engineFactory->GetEngineClient();
    Vector posOffset = LocalPlayer->GetPositionOffset();
    QAngle viewAngle = LocalPlayer->GetViewAngle();
    for(int i = 1; i <= engineClient->getMaxPlayers(); i++) {
        cEntityManager* entity = engineFactory->GetEntity(i);
        if(!entity->isValidLivePlayer()) {
            reset();
            continue;
        }
        
        if(LocalPlayer->GetTeam() == entity->GetTeam()) {
            reset();
            continue;
        }
        
        if(entity->isInAir()) {
            // reset();
            // continue;
        }
        
        int aimBone = getBestBone(entity);
        Vector hitbox = entity->GetBonePosition(aimBone);
        
        if(settingsManager->GetVisibilityCheck() && !bsp->isVisible(posOffset, hitbox))
        {
            continue;
        }
        
        if(settingsManager->GetAimTarget() == "crosshair")
        {
            float fov = cMath::GetFov(viewAngle, posOffset, hitbox);
            if(fov < m_bestfov)
            {
                m_bestfov = fov;
                m_bestent = i;
            }
        }
        
        if(settingsManager->GetAimTarget() == "closest")
        {
            float fov = cMath::GetFov(viewAngle, posOffset, hitbox);
            float dist = cMath::VecDist(posOffset, hitbox);
            if(dist < m_bestdist && fov < m_bestfov)
            {
                m_bestdist = dist;
                m_bestent = i - 1;
            }
        }
        
        if(settingsManager->GetAimTarget() == "threat")
        {
            float fov = cMath::GetFov(viewAngle, posOffset, hitbox);
            float dist = cMath::VecDist(posOffset, hitbox);
            float health = (float)entity->GetHealth();
            
            float threat = health / dist;
            
            if( threat > m_bestthreat && fov < m_bestfov )
            {
                m_bestthreat = threat;
                m_bestent = i - 1;
            }
        }
        delete entity;
    }
    return m_bestent;
}

void cAimHelper::VelocityComp(Vector& EnemyPos, Vector EnemyVecVelocity, Vector PlayerVecVelocity)
{
    EnemyPos += EnemyVecVelocity  * 0.15f;
    EnemyPos -= PlayerVecVelocity * 0.15f;
}

void cAimHelper::aimTarget(cEntityManager* entity, int entityIndex)
{
    QAngle AimAngles;
    
    int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
    int aimBone;
    if(m_lockedBone == -5) {
        aimBone = getBestBone(entity);
        m_lockedBone = aimBone;
    } else {
        aimBone = m_lockedBone;
    }
    
    Vector EnemyPos = entity->GetBonePosition(aimBone);
    Vector dir = LocalPlayer->GetPositionOffset() - EnemyPos;
    
    cMath::VectorNormalize(dir);
    cMath::VectorAngles(dir, AimAngles);
    
    cMath::ClampAngle(AimAngles);
    
    if(
       settingsManager->GetRecoilControl() &&
       LocalPlayer->GetShotsFired() > 1 &&
       cWeaponManager::isRCSWeapon(currentWeapon)
    )
    {
        AimAngles -= LocalPlayer->GetAimPunchAngle() * settingsManager->GetRecoilLevel();
        cMath::ClampAngle(AimAngles);
    }

    if(settingsManager->GetSmoothAiming() && cWeaponManager::needsSmooth(currentWeapon))
    {
        cMath::SmoothAngle(LocalPlayer->GetViewAngle(), AimAngles, settingsManager->GetSmoothingFactor());
    }
    
    engineFactory->GetEngineClient()->setViewAngles(AimAngles);
}

void cAimHelper::reset() {
    m_lockedBone = -5;
    m_lockedEntity = -5;
}

void cAimHelper::apply()
{
    LocalPlayer = engineFactory->GetLocalEntity();
    if(!LocalPlayer->isValidLivePlayer()) {
        reset();
        return;
    }
    
    if(LocalPlayer->isInAir())
    {
        reset();
        return;
    }
    
    int currentWeapon = LocalPlayer->GetActiveWeaponEntityID();
    if(
       cWeaponManager::isC4(currentWeapon) ||
       cWeaponManager::isKnife(currentWeapon) ||
       cWeaponManager::isGrenade(currentWeapon) ||
       cWeaponManager::isNonAimWeapon(currentWeapon)
    )
    {
        reset();
        return;
    }
    
    if(
       (!LocalPlayer->isAttacking() && currentWeapon != WEAPON_REVOLVER) ||
       (!LocalPlayer->isAttacking2() && currentWeapon == WEAPON_REVOLVER)
    )
    {
        reset();
        return;
    }
    
    int closest = -1;
    if(m_lockedEntity == -5) {
        closest = this->findTarget();
        if(closest == -1)
        {
            reset();
            return;
        }
        m_lockedEntity = closest;
    } else {
        closest = m_lockedEntity;
    }
    
    cEntityManager* entity = engineFactory->GetEntity(closest);
    if(!entity->isValidLivePlayer()) {
        reset();
        return;
    }
    
    aimTarget(entity, closest);
    delete entity;
}
