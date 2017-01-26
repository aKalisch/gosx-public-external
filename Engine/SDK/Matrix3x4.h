//
//  Matrix3x4.h
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Matrix3x4_h
#define Matrix3x4_h

#include "Vector.h"

class Matrix3x4
{
public:
    union
    {
        struct
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
        };
        
        float m[3][4];
        float mm[12];
    };
    
    inline Vector& GetAxis(int i)
    {
        return *(Vector*)&m[ i ][ 0 ];
    }
};

#endif /* Matrix3x4_h */
