#pragma once
#ifndef GSK_ENGINE_ENTITY
#define GSK_ENGINE_ENTITY

#include "memory.h"
#include "offsetMGR.h"

#include "sdk.h"
#include "bsp.h"

class cEntityManager {
public:
    // Constructors
	cEntityManager(int entityID, cMemoryManager* memManager, cOffsetManager* offManager);
    cEntityManager(uint64_t entityAddress, cMemoryManager* memManager, cOffsetManager* offManager);
	cEntityManager(cMemoryManager* memManager, cOffsetManager* offManager);
    
    // Getters
	int             GetHealth();
	Byte            GetFlags();
	int             GetGlowIndex();
    Vector          GetVelocity();
	eTeam           GetTeam();
    uint64_t        GetGlowObjectsManager();
    int             GetActiveWeaponEntityID();
    int             GetShotsFired();
    QAngle          GetAimPunchAngle();
    Vector          GetBonePosition(int bone);
    Vector          GetVecOrigin();
    Vector          GetViewOffset();
    const Vector    GetPositionOffset();
    const QAngle    GetViewAngle();
    sGlowEntity     GetGlowObject();
    std::string     GetEntityClass();
    float           GetFlashAlpha();
    WeaponEntity    GetActiveWeaponData();
    bool            GetHasMovedSinceSpawn();
    
    // Bool Getters
    bool        isInAir();
    bool        isDormant();
	bool        isValidLivePlayer();
    bool        isValidGlowEntity();
    bool        isAttacking();
    bool        isAttacking2();
    bool        isCrouching();
    bool        isPressingAlt();
    bool        isPressingAlt2();
    bool        isVisible(Vector bone);
    bool        isWeapon();
    bool        isBomb();
    bool        isChicken();
    
    // Actions
    void        forceJump();
    void        forceAttack();
    void        forceAttack2();
    void        forceDuck(bool on = false);
    void        setGlow(float r, float g, float b, float a, bool throughWalls);
    void        setGlow(sGlowEntity glow, int index);
    void        setFlashAlpha(float alpha);
    
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
private:
	cMemoryManager* memoryManager;
	cOffsetManager* offsetManager;
	uint64_t entityPointer;
	int entityID;
    uint64_t glowObjectsManager = 0xF;
    uint64_t activeWeaponEntity = 0xF;
    uint64_t GetActiveWeaponEntity();
    uint64_t boneMatrixPointer = 0xF;
    uint64_t GetBoneMatrixPointer();
    Vector PositionOffset = {0.123456f, 0.f, 0.f};
};

#endif
