//
//  settings.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "settings.h"

cSettingsManager::cSettingsManager() {
    char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
    proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
    auto dirname = DirName(pathbuf);
    std::string settingsFile = dirname + "/settings.ini";
    if(fileExist(settingsFile))
    {
        iniFile = strdup(settingsFile.c_str());
        
        ini.SetUnicode();
        ini.LoadFile(iniFile);
        
        hackenabled                 = ini.GetBoolValue("Main", "enabled", true);
        glowenabled                 = ini.GetBoolValue("Features", "wallhack", true);
        hopenabled                  = ini.GetBoolValue("Features", "bunnyhop", true);
        triggerenabled              = ini.GetBoolValue("Features", "triggerbot", false);
        noFlashEnabled              = ini.GetBoolValue("Features", "noflash", false);
        teamglow                    = ini.GetBoolValue("Glow", "teamglow", false);
        glowalpha                   = (float)ini.GetDoubleValue("Glow", "glowalpha", 0.8f);
        colorT                      = ini.GetValue("Glow", "color_t", "255,0,0");
        colorCT                     = ini.GetValue("Glow", "color_ct", "0,255,0");
        colorTvisible               = ini.GetValue("Glow", "color_t_visible", "255,255,0");
        colorCTvisible              = ini.GetValue("Glow", "color_ct_visible", "0,255,255");
        glowHoverHealth             = ini.GetBoolValue("Glow", "glow_hover_health", false);
        woundedHealth               = (int)ini.GetLongValue("Glow", "wounded_health", 25);
        glowWounded                 = ini.GetBoolValue("Glow", "glow_wounded", false);
        triggerBurstShot            = ini.GetBoolValue("Trigger", "burstshot", false);
        autoPistol                  = ini.GetBoolValue("Extra", "autopistol", false);
        autoKnife                   = ini.GetBoolValue("Extra", "autoknife", false);
        aimbot                      = ini.GetBoolValue("Aimbot", "autoaim", false);
        boneMode                    = ini.GetValue("Aimbot", "bone_mode", "dynamic");
        aimPosition                 = (int)ini.GetLongValue("Aimbot", "aim_position", 4);
        aimTarget                   = ini.GetValue("Aimbot", "aim_target", "closest");
        smoothAiming                = ini.GetBoolValue("Aimbot", "smoothaim", true);
        smoothingFactor             = (float)ini.GetDoubleValue("Aimbot", "smoothing_factor", 2.0f);
        fovEnabled                  = ini.GetBoolValue("Aimbot", "fov_enabled", true);
        fieldOfView                 = (float)ini.GetDoubleValue("Aimbot", "field_of_view", 20.0f);
        
        /*weapon_bones                = ini.GetValue("Aimbot", "weapon_bones", "");
        
        std::vector<std::string> wb = split<std::string>(weapon_bones, "|");
        
        for (auto &weap : wb)
        {
            std::vector<std::string> bw = split<std::string>(weap, ":");
            weaponBones[atoi(bw[0].c_str())] = atoi(bw[1].c_str());
        }*/
        
        recoilControl               = ini.GetBoolValue("Aimbot", "recoil_control", false);
        recoilLevel                 = (float)ini.GetDoubleValue("Aimbot", "recoil_level", 0.5f);
        knifeBot                    = ini.GetBoolValue("Extra", "knife_bot", true);
        autoCrouch                  = ini.GetBoolValue("Extra", "auto_crouch", true);
        visibilityCheck             = ini.GetBoolValue("Aimbot", "visibility_check", true);
        onlyBspVis                  = ini.GetBoolValue("Aimbot", "only_bsp_visibility", true);
        maxFlashAlpha               = (float)ini.GetDoubleValue("Extra", "max_flash_alpha", 225.f);
    }
}

bool cSettingsManager::fileExist(std::string fileName) {
    std::ifstream infile(fileName);
    bool result = infile.good();
    infile.close();
    return result;
}

std::string cSettingsManager::DirName(std::string source)
{
    source.erase(find(source.rbegin(), source.rend(), '/').base(), source.end());
    return source;
}

bool cSettingsManager::GetHackenabled() {
    return hackenabled;
}

bool cSettingsManager::GetGlowenabled() {
    return glowenabled;
}

bool cSettingsManager::GetHopenabled() {
    return hopenabled;
}

bool cSettingsManager::GetTriggerenabled() {
    return triggerenabled;
}

bool cSettingsManager::GetNoFlashEnabled() {
    return noFlashEnabled;
}
bool cSettingsManager::GetTeamglow() {
    return teamglow;
}
float cSettingsManager::GetGlowalpha() {
    return glowalpha;
}
std::string cSettingsManager::GetColorT() {
    return colorT;
}
std::string cSettingsManager::GetColorCT() {
    return colorCT;
}
std::string cSettingsManager::GetColorTvisible() {
    return colorTvisible;
}
std::string cSettingsManager::GetColorCTvisible() {
    return colorCTvisible;
}
bool cSettingsManager::GetTriggerBurstShot() {
    return triggerBurstShot;
}
bool cSettingsManager::GetAutoPistol() {
    return autoPistol;
}
bool cSettingsManager::GetAutoKnife() {
    return autoKnife;
}
bool cSettingsManager::GetAimbot() {
    return aimbot;
}
int cSettingsManager::GetAimPosition() {
    return aimPosition;
}
std::string cSettingsManager::GetBoneMode() {
    return boneMode;
}
std::string cSettingsManager::GetAimTarget() {
    return aimTarget;
}
bool cSettingsManager::GetSmoothAiming() {
    return smoothAiming;
}
float cSettingsManager::GetSmoothingFactor() {
    return smoothingFactor;
}
bool cSettingsManager::GetFovEnabled() {
    return fovEnabled;
}
float cSettingsManager::GetFieldOfView() {
    return fieldOfView;
}
bool cSettingsManager::GetRecoilControl() {
    return recoilControl;
}
float cSettingsManager::GetRecoilLevel() {
    return recoilLevel;
}
bool cSettingsManager::GetGlowHoverHealth() {
    return glowHoverHealth;
}
int cSettingsManager::GetWoundedHealth() {
    return woundedHealth;
}
bool cSettingsManager::GetGlowWounded() {
    return glowWounded;
}
bool cSettingsManager::GetVisibilityCheck() {
    return visibilityCheck;
}
bool cSettingsManager::GetOnlyBspVis() {
    return onlyBspVis;
}
bool cSettingsManager::GetKnifeBot() {
    return knifeBot;
}
bool cSettingsManager::GetAutoCrouch() {
    return autoCrouch;
}
float cSettingsManager::GetMaxFlashAlpha() {
    return maxFlashAlpha;
}
