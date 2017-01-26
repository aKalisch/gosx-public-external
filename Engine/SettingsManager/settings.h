//
//  settings.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef settings_hpp
#define settings_hpp

#include "SimpleIni.h"
#include <vector>
#include <unistd.h>
#include <libproc.h>
#include <fstream>

class cSettingsManager {
public:
    cSettingsManager();
    std::string DirName(std::string source);
    bool fileExist(std::string fileName);
    int getAimPosition(int weaponID);
    
    template<typename T>
    std::vector<T> split(const T & str, const T & delimiters)
    {
        std::vector<T> v;
        size_t start = 0;
        auto pos = str.find_first_of(delimiters, start);
        while(pos != T::npos)
        {
            if(pos != start)
            {
                v.emplace_back(str, start, pos - start);
            }
            start = pos + 1;
            pos = str.find_first_of(delimiters, start);
        }
        if(start < str.length())
        {
            v.emplace_back(str, start, str.length() - start);
        }
        return v;
    }
    bool GetHackenabled();
    bool GetGlowenabled();
    bool GetHopenabled();
    bool GetTriggerenabled();
    bool GetNoFlashEnabled();
    bool GetTeamglow();
    float GetGlowalpha();
    std::string GetColorT();
    std::string GetColorCT();
    std::string GetColorTvisible();
    std::string GetColorCTvisible();
    bool GetTriggerBurstShot();
    bool GetAutoPistol();
    bool GetAutoKnife();
    bool GetAimbot();
    int GetAimPosition();
    std::string GetBoneMode();
    std::string GetAimTarget();
    bool GetSmoothAiming();
    float GetSmoothingFactor();
    bool GetFovEnabled();
    float GetFieldOfView();
    bool GetRecoilControl();
    float GetRecoilLevel();
    bool GetGlowHoverHealth();
    int GetWoundedHealth();
    bool GetGlowWounded();
    bool GetVisibilityCheck();
    bool GetOnlyBspVis();
    bool GetKnifeBot();
    bool GetAutoCrouch();
    float GetMaxFlashAlpha();
private:
    std::string     glowType            = "old";
    CSimpleIniA     ini;
    char *          iniFile;
    bool            hackenabled         = true;
    bool            glowenabled         = true;
    bool            hopenabled          = true;
    bool            triggerenabled      = false;
    bool            noFlashEnabled      = false;
    bool            teamglow            = false;
    float           glowalpha           = 0.8f;
    std::string     colorT              = "255,0,0";
    std::string     colorCT             = "0,255,0";
    std::string     colorTvisible       = "255,255,0";
    std::string     colorCTvisible      = "0,255,255";
    bool            triggerBurstShot    = false;
    bool            autoPistol          = false;
    bool            autoKnife           = false;
    bool            aimbot              = false;
    int             aimPosition         = 4;
    std::string     boneMode            = "dynamic";
    std::string     aimTarget           = "closest";
    bool            smoothAiming        = true;
    float           smoothingFactor     = 2;
    bool            fovEnabled          = true;
    float           fieldOfView         = 20.0f;
    bool            recoilControl       = false;
    float           recoilLevel         = 0.5f;
    bool            glowHoverHealth     = false;
    int             woundedHealth       = 25;
    bool            glowWounded         = true;
    bool            visibilityCheck     = true;
    bool            onlyBspVis          = true;
    bool            knifeBot            = true;
    bool            autoCrouch          = true;
    float           maxFlashAlpha       = 225.f;
};

#endif /* settings_hpp */
