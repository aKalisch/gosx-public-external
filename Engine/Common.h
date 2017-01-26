#pragma once
#ifndef GSK_ENGINE_COMMON
#define GSK_ENGINE_COMMON

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
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
	TEAM_Unk = 0,
	TEAM_Unk2,
	TEAM_T,
	TEAM_CT
};

struct sGlowEntity {
public:
	uint64_t entityPointer;         // 0x0  => 0x8  (len: 0x8)
    float r;                        // 0x8  => 0xC  (len: 0x4)
    float g;                        // 0xC  => 0x10 (len: 0x4)
    float b;                        // 0x10 => 0x14 (len: 0x4)
    float a;                        // 0x14 => 0x18 (len: 0x4)
	char unk1[0x10];                // 0x18 => 0x28 (len: 0x10)
	bool RenderWhenOccluded;        // 0x28 => 0x29 (len: 0x1)
	bool RenderWhenUnoccluded;      // 0x29 => 0x2A (len: 0x1)
	bool FullBloom;                 // 0x2A => 0x2B (len: 0x1)
	char unk2[0x15];                // 0x2B => 0x40 (len: 0x15)
    
    bool isValidGlowEntity() {
        return !RenderWhenOccluded && entityPointer != 0x0;
    }
};

struct WeaponEntity {
    int     m_clip1                       = 0x3A64;
    int     m_clip2                       = 0x3A68;
    int     m_primaryReserveAmmoCount     = 0x3A6C;
    int     m_secondaryReserveAmmoCount   = 0x3A70;
};

#endif
