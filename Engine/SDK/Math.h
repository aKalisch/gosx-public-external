//
//  Math.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Math_h
#define Math_h

#include "Common.h"

#include "Vector.h"
#include "QAngle.h"
#include "Matrix3x4.h"

#define M_RADPI 57.295779513082f
#define M_PI_F  ((float)(M_PI))

#define SQUARE( a ) a*a
#define DEG2RAD( x  )  ( (float)(x) * (float)( M_PI_F / 180.f ) )
#define RAD2DEG( x  )  ( (float)(x) * (float)( 180.f/M_PI_F ) )

class cMath
{
public:
    
    cMath();
    
    static void inline SinCos(float radians, float *sine, float *cosine);
    static void AngleVectors(const Vector &angles, Vector *forward);
    static void AngleVectors(const Vector &angles, Vector *forward, Vector *right, Vector *up);
    static float DotProduct(Vector &v1, float* v2);
    static float Dot(const Vector &v1, Vector &v2);
    static void VectorTransform(Vector &in1, Matrix3x4& in2, Vector &out);
    static float VecLength(Vector& vec);
    static float VecDist(const Vector& fVec1, Vector& fVec2);
    static float GetFov(QAngle eyePosition, Vector playerHeadPosition, Vector entityHeadPosition);
    static QAngle CalcAngle(Vector PlayerPos, Vector EnemyPos);
    static void VectorAngles( const Vector& dir, QAngle &angles );
    static void ClampAngle( QAngle& angles);
    static void VectorNormalize( Vector& v);
    static void SmoothAngle(const QAngle& ViewAngle, QAngle& DestAngles, float smooth);
    static void MakeVector(Vector angle, Vector& vector);
    static Vector AngleToDirection( QAngle angle);
    static void VectorITransform( Vector& in1, const Matrix3x4& in2, Vector& out);
    static void VectorIRotate( Vector& in1, const Matrix3x4& in2, Vector& out);
};

#endif /* Math_h */
