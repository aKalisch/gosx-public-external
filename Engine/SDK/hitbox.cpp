//
//  hitbox.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "hitbox.h"

cHitboxManager::cHitboxManager() {
    Hitbox[0].Setup(BONE_PELVIS, Vector(-6.42f, -5.7459f, -6.8587f), Vector(4.5796f, 4.5796f, 6.8373f));
    // Hitbox[  1 ].Setup(	BONE_L_THIGH,	  Vector3( 1.819f,  -3.959f,  -2.14f  ), Vector3(22.149002f, 3.424f,    4.5796f));
    // Hitbox[  2 ].Setup(	BONE_L_CALF,	  Vector3( 2.0758f, -3.21f,   -2.1507f), Vector3(19.26f,     2.675f,    3.0495f));
    // Hitbox[  3 ].Setup(	BONE_R_THIGH,	  Vector3( 1.819f,  -3.7557f, -4.5796f), Vector3(22.149002f, 3.424f,    2.14f  ));
    // Hitbox[  4 ].Setup(	BONE_R_CALF,	  Vector3( 2.0758f, -3.21f,   -2.8462f), Vector3(19.26f,     2.675f,    2.247f ));
    Hitbox[1].Setup(BONE_SPINE0, Vector(-4.28f, -4.5796f, -6.3879f), Vector(3.21f, 5.885f, 6.2809f));
    Hitbox[2].Setup(BONE_SPINE1, Vector(-4.28f, -4.5796f, -6.3879f), Vector(3.21f, 5.885f, 6.2809f));
    Hitbox[3].Setup(BONE_SPINE2, Vector(-4.28f, -4.5796f, -6.3879f), Vector(3.21f, 5.885f, 6.2809f));
    Hitbox[4].Setup(BONE_SPINE3, Vector(-4.28f, -5.029f, -6.0883f), Vector(3.21f, 5.885f, 5.9813f));
    Hitbox[5].Setup(BONE_NECK, Vector( 0.3317f, -3.0174f, -2.4503f), Vector(3.4026f,    2.4182f,   2.354f ));
    Hitbox[6].Setup(BONE_HEAD, Vector(-2.7713f, -2.8783f, -3.103f ), Vector(6.955f,     3.5203f,   3.0067f));
    // Hitbox[ 11 ].Setup( BONE_L_UPPER_ARM, Vector3(-2.675f,  -3.21f,   -2.14f  ), Vector3(12.84f,     3.21f,     2.14f  ));
    // Hitbox[ 12 ].Setup( BONE_L_FOREARM,	  Vector3(-0.f,     -2.14f,   -2.14f  ), Vector3(9.63f,      2.14f,     2.14f  ));
    // Hitbox[ 13 ].Setup( BONE_R_UPPER_ARM, Vector3(-2.675f,  -3.21f,   -2.14f  ), Vector3(12.84f,     3.21f,     2.14f  ));
    // Hitbox[ 14 ].Setup( BONE_R_FOREARM,	  Vector3(-0.f,	    -2.14f,   -2.14f  ), Vector3(9.63f,      2.14f,     2.14f  ));
}

Hitbox_t cHitboxManager::getHitbox(int iHitbox) {
    return Hitbox[iHitbox];
}

Hitbox_t cHitboxManager::getHitboxByBone(int iBone) {
    for(int i = 0; i < HITBOX_MAX; i++)
    {
        if(iBone == Hitbox[i].iBone)
        {
            return Hitbox[i];
        }
    }
    
    return Hitbox[5];
}

void cHitboxManager::GetHitBoxVectors( Hitbox_t* hitBox, Vector* hitBoxVectors, Matrix3x4 boneMatrix )
{
    Vector points[8] = {
        Vector(hitBox->vMin.x, hitBox->vMin.y, hitBox->vMin.z),
        Vector(hitBox->vMin.x, hitBox->vMax.y, hitBox->vMin.z),
        Vector(hitBox->vMax.x, hitBox->vMax.y, hitBox->vMin.z),
        Vector(hitBox->vMax.x, hitBox->vMin.y, hitBox->vMin.z),
        Vector(hitBox->vMax.x, hitBox->vMax.y, hitBox->vMax.z),
        Vector(hitBox->vMin.x, hitBox->vMax.y, hitBox->vMax.z),
        Vector(hitBox->vMin.x, hitBox->vMin.y, hitBox->vMax.z),
        Vector(hitBox->vMax.x, hitBox->vMin.y, hitBox->vMax.z)
    };
    
    for( int index = 0; index < 8; ++index )
    {
        // scale down the hitbox size a tiny bit (default is a little too big)
        points[index].x *= 0.9f;
        points[index].y *= 0.9f;
        points[index].z *= 0.9f;
        
        // transform the vector
        cMath::VectorTransform(points[index], boneMatrix, hitBoxVectors[index]);
    }
}
