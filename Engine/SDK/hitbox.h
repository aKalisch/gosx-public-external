//
//  hitbox.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef hitbox_hpp
#define hitbox_hpp

#include "sdk.h"
#include "hitboxDefs.h"

class cHitboxManager {
public:
    cHitboxManager();
    Hitbox_t getHitbox(int iHitbox);
    Hitbox_t getHitboxByBone(int iBone);
    void GetHitBoxVectors(Hitbox_t* hitBox, Vector* hitBoxVectors, Matrix3x4 boneMatrix);
private:
    Hitbox_t Hitbox[10];
};

#endif /* hitbox_hpp */
