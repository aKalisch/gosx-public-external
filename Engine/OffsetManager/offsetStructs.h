//
//  offsetStructs.h
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef offsetStructs_h
#define offsetStructs_h

struct sClientOffsets {
    // Pointer Offsets
    uint64_t m_dwLocalPlayer;
    uint64_t m_dwEntityList;
    uint64_t m_dwGlowManager;
    uint64_t m_dwForceAttack;
    uint64_t m_dwForceAttack2;
    uint64_t m_dwForceDuck;
    uint64_t m_dwForceJump;
    uint64_t m_dwForceWalk;
    uint64_t m_dwForceAlt1;
    uint64_t m_dwForceAlt2;
    uint64_t m_dwRadarBase;
    
    uint64_t m_dwEntityLoopDistance         = 0x20;
    uint64_t m_dwBoneDistance               = 0x30;
    uint64_t m_dwGlowLoopDistance           = 0x40;
    uint64_t m_dwGlowCount                  = 0x10;
    uint64_t m_dwGlowColorStruct            = 0x8;
    uint64_t m_dwGlowEnable                 = 0x28;
    uint64_t m_clrRender                    = 0xA8;
    uint64_t m_bDormant                     = 0x121;
    uint64_t m_iTeam                        = 0x128;
    uint64_t m_iHealth                      = 0x134;
    uint64_t m_iFlags                       = 0x138;
    uint64_t m_vecViewOffset                = 0x13C;
    uint64_t m_vecVelocity                  = 0x148;
    uint64_t m_angRotation                  = 0x160;
    uint64_t m_vecOrigin                    = 0x16C;
    uint64_t m_lifeState                    = 0x293;
    uint64_t m_bSpotted                     = 0xECD;
    uint64_t m_bSpottedByMask               = 0xF10;
    uint64_t m_dwBoneMatrix                 = 0x2C70;
    uint64_t m_hMyWeapons                   = 0x3528;
    uint64_t m_hActiveWeapon                = 0x3628;
    uint64_t m_Local                        = 0x36F0;
    uint64_t m_hViewModelIndex              = 0x3AD4;
    uint64_t m_bHasMovedSinceSpawn          = 0x4179;
    uint64_t m_iShotsFired                  = 0xABB0;
    uint64_t m_iFlashAlpha                  = 0xABF4;
    uint64_t m_flFlashDuration              = 0xABF8;
    uint64_t m_iGlowIndex                   = 0xAC10;
    uint64_t m_dwCrosshairID                = 0xB390;
    uint64_t m_iCompetitiveRanking          = 0x20DC;
    uint64_t m_iCompetitiveWins             = 0x21E0;
    uint64_t m_viewPunchAngle               = m_Local + 0x68;
    uint64_t m_aimPunchAngle                = m_Local + 0x74;
    uint64_t m_aimPunchAngleVel             = m_Local + 0x80;
    uint64_t m_Item                         = 0x60;
    uint64_t m_iItemDefinitionIndex         = 0x268;
    uint64_t m_AttributeManager             = 0x34C0;
    uint64_t m_iClip1                       = 0x3A64;
    uint64_t m_iClip2                       = 0x3A68;
    uint64_t m_iPrimaryReserveAmmoCount     = 0x3A6C;
    uint64_t m_iSecondaryReserveAmmoCount   = 0x3A70;
    uint64_t m_dwRealWeaponID               = m_AttributeManager + m_Item + m_iItemDefinitionIndex;
};

struct sEngineOffsets {
    uint64_t m_dwCEngineClient;
    uint64_t m_szGameDirectory;
    uint64_t m_dwIsInGame                   = 0x198;
    uint64_t m_dwFullUpdate                 = 0x204;
    uint64_t m_iLocalPlayer                 = 0x210;
    uint64_t m_szMapFile                    = 0x218;
    uint64_t m_szMapName                    = 0x31C;
    uint64_t m_dwGetMaxClients              = 0x3A0;
    uint64_t m_setViewAngle                 = 0x8E20;
};

#endif /* offsetStructs_h */
