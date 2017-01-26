//
//  weapons.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "weapons.h"

int cWeaponManager::getDelay(int weaponID)
{
    if(isPistol(weaponID) && weaponID != WEAPON_TEC9)
    {
        return 70;
    }
    
    if(isShotgun(weaponID))
    {
        return 30;
    }
    
    if(isSniper(weaponID))
    {
        return 100;
    }
    
    return 3;
}

bool cWeaponManager::isKnife(int weaponID)
{
    if(
       weaponID == WEAPON_KNIFE ||
       weaponID == WEAPON_KNIFE_T ||
       weaponID == WEAPON_KNIFE_BAYONET ||
       weaponID == WEAPON_KNIFE_FLIP ||
       weaponID == WEAPON_KNIFE_GUT ||
       weaponID == WEAPON_KNIFE_KARAMBIT ||
       weaponID == WEAPON_KNIFE_M9_BAYONET ||
       weaponID == WEAPON_KNIFE_TACTICAL ||
       weaponID == WEAPON_KNIFE_FALCHION ||
       weaponID == WEAPON_KNIFE_SURVIVAL_BOWIE ||
       weaponID == WEAPON_KNIFE_BUTTERFLY ||
       weaponID == WEAPON_KNIFE_PUSH
    )
    {
        return true;
    }
    
    return false;
}

bool cWeaponManager::isGrenade(int weaponID)
{
    if(
       weaponID == WEAPON_FLASHBANG ||
       weaponID == WEAPON_HEGRENADE ||
       weaponID == WEAPON_SMOKEGRENADE ||
       weaponID == WEAPON_MOLOTOV ||
       weaponID == WEAPON_DECOY ||
       weaponID == WEAPON_INCGRENADE
    )
    {
        return true;
    }
    
    return false;
}

bool cWeaponManager::isC4(int weaponID)
{
    if(weaponID == WEAPON_C4)
    {
        return true;
    }
    
    return false;
}

bool cWeaponManager::isPistol(int weaponID)
{
    if(
       weaponID == WEAPON_DEAGLE ||
       weaponID == WEAPON_ELITE ||
       weaponID == WEAPON_FIVESEVEN ||
       weaponID == WEAPON_GLOCK ||
       weaponID == WEAPON_TEC9 ||
       weaponID == WEAPON_TASER ||
       weaponID == WEAPON_HKP2000 ||
       weaponID == WEAPON_P250 ||
       weaponID == WEAPON_USP_SILENCER ||
       weaponID == WEAPON_CZ75A ||
       weaponID == WEAPON_REVOLVER
    )
    {
        return true;
    }
    
    return false;
}

bool cWeaponManager::isShotgun(int weaponID)
{
    if(
       weaponID == WEAPON_XM1014 ||
       weaponID == WEAPON_MAG7 ||
       weaponID == WEAPON_NOVA ||
       weaponID == WEAPON_SAWEDOFF
    )
    {
        return true;
    }
    
    return false;
}


bool cWeaponManager::isSniper(int weaponID)
{
    if(
       weaponID == WEAPON_G3SG1 ||
       weaponID == WEAPON_SCAR20 ||
       weaponID == WEAPON_SSG08 ||
       weaponID == WEAPON_AWP
    )
    {
        return true;
    }
    
    return false;
}

bool cWeaponManager::needsSmooth(int weaponID)
{
    bool ret = true;
    if(isSniper(weaponID))
    {
        ret = false;
    }
    
    if(isShotgun(weaponID))
    {
        ret = false;
    }
    
    return ret;
}

bool cWeaponManager::isRCSWeapon(int weaponID)
{
    bool ret = true;
    if(isSniper(weaponID))
    {
        ret = false;
    }
    
    if(isPistol(weaponID))
    {
        ret = false;
    }
    
    if(isShotgun(weaponID))
    {
        ret = false;
    }
    
    return ret;
}

bool cWeaponManager::isNonAimWeapon(int weaponID)
{
    if(
       weaponID == WEAPON_SCAR20 ||
       weaponID == WEAPON_G3SG1
    )
    {
        return true;
    }
    
    return false;
}
