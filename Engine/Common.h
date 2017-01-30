#pragma once
#ifndef GSK_ENGINE_COMMON
#define GSK_ENGINE_COMMON

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <wchar.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>
#include <regex>
#include <thread>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

#define GetArgs(from, to) va_list args; va_start(args, from); vsprintf_s(to, from, args); va_end(args);

#define FL_ONGROUND (1 << 0)

enum eTeam {
    TEAM_UInit = -1,
	TEAM_Unk = 0,
	TEAM_Unk2,
	TEAM_T,
	TEAM_CT
};

struct sGlowEntity {
public:
	uint64_t entityPointer;
    float r;
    float g;
    float b;
    float a;
	char unk1[0x10];
	bool RenderWhenOccluded;
	bool RenderWhenUnoccluded;
	bool FullBloom;
	char unk2[0x15];
    
    bool isValidGlowEntity() {
        return entityPointer != 0x0;
    }
};

struct WeaponEntity {
    int     m_clip1                       = 0x3A64;
    int     m_clip2                       = 0x3A68;
    int     m_primaryReserveAmmoCount     = 0x3A6C;
    int     m_secondaryReserveAmmoCount   = 0x3A70;
};

#endif
