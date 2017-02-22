#include "entity.h"

cEntityManager::cEntityManager(int eID, cMemoryManager* memManager, cOffsetManager* offManager) {
	entityID = eID;
	memoryManager = memManager;
	offsetManager = offManager;
	entityPointer = memoryManager->read<uint64_t>(offsetManager->client.m_dwEntityList + (entityID * offManager->client.m_dwEntityLoopDistance));
}

cEntityManager::cEntityManager(uint64_t entityAddress, cMemoryManager* memManager, cOffsetManager* offManager) {
    memoryManager = memManager;
    offsetManager = offManager;
    entityPointer = entityAddress;
}

cEntityManager::cEntityManager(cMemoryManager* memManager, cOffsetManager* offManager) {
	memoryManager = memManager;
	offsetManager = offManager;
	entityPointer = memoryManager->read<uint64_t>(offsetManager->client.m_dwLocalPlayer);
}

uint64_t cEntityManager::GetPointer() {
    return entityPointer;
}

int cEntityManager::GetHealth() {
    return memoryManager->read<int>(entityPointer + offsetManager->client.m_iHealth);
}

Byte cEntityManager::GetFlags() {
	return memoryManager->read<Byte>(entityPointer + offsetManager->client.m_iFlags);
}

eTeam cEntityManager::GetTeam() {
    if(team == TEAM_UInit) {
        team = memoryManager->read<eTeam>(entityPointer + offsetManager->client.m_iTeam);
    }
    
    return team;
}

bool cEntityManager::isInAir() {
	return !(GetFlags() & FL_ONGROUND);
}

bool cEntityManager::isDormant() {
    return memoryManager->read<bool>(entityPointer + offsetManager->client.m_bDormant);
}

bool cEntityManager::isAttacking() {
    return memoryManager->read<int>(offsetManager->client.m_dwForceAttack) == 5;
}

bool cEntityManager::isAttacking2() {
    return memoryManager->read<int>(offsetManager->client.m_dwForceAttack2) == 5;
}

bool cEntityManager::isPressingAlt() {
    return memoryManager->read<int>(offsetManager->client.m_dwForceAlt1) == 5;
}

bool cEntityManager::isPressingAlt2() {
    return memoryManager->read<int>(offsetManager->client.m_dwForceAlt2) == 5;
}

bool cEntityManager::isCrouching() {
    return memoryManager->read<int>(offsetManager->client.m_dwForceDuck) == 5;
}

bool cEntityManager::GetHasMovedSinceSpawn() {
    return memoryManager->read<bool>(entityPointer + offsetManager->client.m_bHasMovedSinceSpawn);
}

void cEntityManager::forceJump() {
    memoryManager->write<int>(offsetManager->client.m_dwForceJump, 6);
}

void cEntityManager::forceAttack() {
    memoryManager->write<int>(offsetManager->client.m_dwForceAttack, 6);
}

void cEntityManager::forceAttack2() {
    memoryManager->write<int>(offsetManager->client.m_dwForceAttack2, 6);
}

void cEntityManager::forceDuck(bool on) {
    memoryManager->write<int>(offsetManager->client.m_dwForceDuck, on ? 5 : 4);
}

int cEntityManager::GetGlowIndex() {
	int idx = memoryManager->read<int>(entityPointer + offsetManager->client.m_iGlowIndex);
    return idx;
}

Vector cEntityManager::GetVelocity() {
    return memoryManager->read<int>(entityPointer + offsetManager->client.m_vecVelocity);
}

int cEntityManager::GetActiveWeaponEntityID() {
    return memoryManager->read<int>(GetActiveWeaponEntity() + offsetManager->client.m_dwRealWeaponID);
}

Vector cEntityManager::GetVecOrigin() {
    return memoryManager->read<Vector>(entityPointer + offsetManager->client.m_vecOrigin);
}

Vector cEntityManager::GetViewOffset() {
    return memoryManager->read<Vector>(entityPointer + offsetManager->client.m_vecViewOffset);
}

const QAngle cEntityManager::GetViewAngle() {
    return memoryManager->read<QAngle>(entityPointer + offsetManager->client.m_angRotation);
}

QAngle cEntityManager::GetAimPunchAngle() {
    return memoryManager->read<QAngle>(entityPointer + offsetManager->client.m_aimPunchAngle);
}

int cEntityManager::GetShotsFired() {
    return memoryManager->read<int>(entityPointer + offsetManager->client.m_iShotsFired);
}

const Vector cEntityManager::GetPositionOffset() {
    return GetVecOrigin() + GetViewOffset();
}

uint64_t* cEntityManager::GetAllWeapons() {
    for(int i = 0; i < 10; i++) {
        uint32_t weaponHandle = memoryManager->read<uint32_t>(entityPointer + offsetManager->client.m_hMyWeapons + (0x4 * i));
        if((int)weaponHandle != -1) {
            weaponArray[i] = memoryManager->read<uint64_t>(
                offsetManager->client.m_dwEntityList +
                (((weaponHandle & 0xFFF) - 1) * offsetManager->client.m_dwEntityLoopDistance)
            );
        } else {
            weaponArray[i] = 0x0;
        }
    }
    
    return weaponArray;
}

void cEntityManager::setBoneMatrixBones() {
    for(int i = BONE_PELVIS; i < BONE_MAX; i++) {
        entityBones[i] = memoryManager->read<Matrix3x4>(GetBoneMatrixPointer() + (offsetManager->client.m_dwBoneDistance * i));
    }
}
Vector cEntityManager::GetBonePosition(int bone) {
    Matrix3x4 m_bone = memoryManager->read<Matrix3x4>(GetBoneMatrixPointer() + (offsetManager->client.m_dwBoneDistance * bone));
    
    Vector bonePosition = {
        m_bone.m[0][3],
        m_bone.m[1][3],
        m_bone.m[2][3]
    };
    
    return bonePosition;
}

uint64_t cEntityManager::GetGlowObjectsManager() {
    if(glowObjectsManager == 0xF) {
        glowObjectsManager = memoryManager->read<uint64_t>(offsetManager->client.m_dwGlowManager);
    }
    
    return glowObjectsManager;
}

uint64_t cEntityManager::GetActiveWeaponEntity() {
    uint64_t dwBaseCombatWeaponIndex = memoryManager->read<uint32_t>(entityPointer + offsetManager->client.m_hActiveWeapon) & 0xFFF;

    return memoryManager->read<uint64_t>(
        offsetManager->client.m_dwEntityList +
        ((dwBaseCombatWeaponIndex - 1) * offsetManager->client.m_dwEntityLoopDistance)
    );

}

uint64_t cEntityManager::GetBoneMatrixPointer() {
    if(boneMatrixPointer == 0xF) {
        boneMatrixPointer = memoryManager->read<uint64_t>(entityPointer + offsetManager->client.m_dwBoneMatrix);
    }
    
    return boneMatrixPointer;
}

void cEntityManager::setGlow(float r, float g, float b, float a, bool throughWalls) {
    uint64_t baseGlowObject = GetGlowObjectsManager() + (offsetManager->client.m_dwGlowLoopDistance * GetGlowIndex());
    sGlowEntity tempGlow = memoryManager->read<sGlowEntity>(baseGlowObject);
    tempGlow.r = r;
    tempGlow.g = g;
    tempGlow.b = b;
    tempGlow.a = a;
    tempGlow.RenderWhenOccluded = throughWalls;
    tempGlow.RenderWhenUnoccluded = !throughWalls;
    memoryManager->write<sGlowEntity>(baseGlowObject, tempGlow);
}

void cEntityManager::setGlow(sGlowEntity glow, int index) {
    uint64_t baseGlowObject = GetGlowObjectsManager() + (offsetManager->client.m_dwGlowLoopDistance * index);
    memoryManager->write<sGlowEntity>(baseGlowObject, glow);
}

void cEntityManager::setGlow(sGlowEntity glow) {
    uint64_t baseGlowObject = GetGlowObjectsManager() + (offsetManager->client.m_dwGlowLoopDistance * GetGlowIndex());
    memoryManager->write<sGlowEntity>(baseGlowObject, glow);
}

sGlowEntity cEntityManager::GetGlowObject() {
    uint64_t baseGlowObject = GetGlowObjectsManager() + (offsetManager->client.m_dwGlowLoopDistance * GetGlowIndex());
    return memoryManager->read<sGlowEntity>(baseGlowObject);
}

bool cEntityManager::isValidLivePlayer() {
    int HP = GetHealth();
    eTeam TM = GetTeam();
    if (
        entityPointer != 0x0 &&
        !isDormant() &&
        (HP > 0 && HP <= 100) &&
        (TM == TEAM_CT || TM == TEAM_T)
        ) {
        return true;
    }
    return false;
}

bool cEntityManager::isValidPlayer() {
    eTeam TM = GetTeam();
    if (
        entityPointer != 0x0 &&
        (TM == TEAM_CT || TM == TEAM_T)
    ) {
        return true;
    }
    return false;
}

std::string cEntityManager::GetEntityClass() {
    if(entityClass == "void") {
        uint64_t vtable = memoryManager->read<uint64_t>(entityPointer + 0x8);
        uint64_t fn     = memoryManager->read<uint64_t>(vtable - 0x8);
        uint64_t cls    = memoryManager->read<uint64_t>(fn + 0x8);
        std::string cn  = memoryManager->readstring(cls);
        std::vector<std::string> clsName = split<std::string>(cn, "_");
        
        entityClass = clsName[1];
    }
    
    return entityClass;
}

int cEntityManager::GetEntityClassID() {
    uint64_t vtable = memoryManager->read<uint64_t>(entityPointer + 0x8);
    uint64_t fn     = memoryManager->read<uint64_t>(vtable + (0x8 * 2));
    uint64_t cls    = memoryManager->read<uint64_t>(fn + 0x1);
    
    int ClassID = memoryManager->read<int>(cls + 0x14);
    
    return ClassID;
}

bool cEntityManager::isWeapon() {
    return GetEntityClass().substr(0, 6) == "Weapon" && !isBomb();
}

bool cEntityManager::isChicken() {
    return GetEntityClass() == "CChicken";
}

bool cEntityManager::isPlayer() {
    return GetEntityClass() == "CSPlayer";
}

bool cEntityManager::isBomb() {
    size_t classNameLength = GetEntityClass().length();
    if(classNameLength == 0) {
        return false;
    }
    return GetEntityClass().substr(classNameLength - 2, classNameLength) == "C4";
}

bool cEntityManager::isValidGlowEntity() {
    return entityPointer != 0x0 && (isWeapon() || isBomb() || isPlayer());
}

float cEntityManager::GetFlashAlpha() {
    return memoryManager->read<float>(entityPointer + offsetManager->client.m_iFlashAlpha);
}

void cEntityManager::setFlashAlpha(float alpha) {
    memoryManager->write<float>(entityPointer + offsetManager->client.m_iFlashAlpha, alpha);
}

WeaponEntity cEntityManager::GetActiveWeaponData() {
    return memoryManager->read<WeaponEntity>(GetActiveWeaponEntity() + offsetManager->client.m_iClip1);
}
