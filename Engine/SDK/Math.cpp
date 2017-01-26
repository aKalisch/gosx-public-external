//
//  Math.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "Math.h"

 void inline cMath::SinCos( float radians, float *sine, float *cosine )
{
    *sine = sin( radians );
    *cosine = cos( radians );
}

void cMath::AngleVectors( const Vector &angles, Vector *forward )
{
    
    float sr, sp, sy, cr, cp, cy;
    
    SinCos( DEG2RAD( angles[ 0 ] ), &sy, &cy );
    SinCos( DEG2RAD( angles[ 1 ] ), &sp, &cp );
    SinCos( DEG2RAD( angles[ 2 ] ), &sr, &cr );
    
    if( forward )
    {
        forward->x = cp*cy;
        forward->y = cp*sy;
        forward->z = -sp;
    }
}

void cMath::AngleVectors( const Vector &angles, Vector *forward, Vector *right, Vector *up )
{
    
    float sr, sp, sy, cr, cp, cy;
    
    SinCos( DEG2RAD( angles[ 0 ] ), &sy, &cy );
    SinCos( DEG2RAD( angles[ 1 ] ), &sp, &cp );
    SinCos( DEG2RAD( angles[ 2 ] ), &sr, &cr );
    
    if( forward )
    {
        forward->x = cp*cy;
        forward->y = cp*sy;
        forward->z = -sp;
    }
    
    if( right )
    {
        right->x = ( -1 * sr*sp*cy + -1 * cr*-sy );
        right->y = ( -1 * sr*sp*sy + -1 * cr*cy );
        right->z = -1 * sr*cp;
    }
    
    if( up )
    {
        up->x = ( cr*sp*cy + -sr*-sy );
        up->y = ( cr*sp*sy + -sr*cy );
        up->z = cr*cp;
    }
}

float cMath::DotProduct( Vector &v1, float* v2 )
{
    return v1.x*v2[ 0 ] + v1.y*v2[ 1 ] + v1.z*v2[ 2 ];
}

float cMath::Dot( const Vector &v1, Vector &v2 )
{
    return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}

void cMath::VectorTransform( Vector &in1, Matrix3x4& in2, Vector &out )
{
    out.x = cMath::DotProduct( in1, in2.m[ 0 ] ) + in2.m[ 0 ][ 3 ];
    out.y = cMath::DotProduct( in1, in2.m[ 1 ] ) + in2.m[ 1 ][ 3 ];
    out.z = cMath::DotProduct( in1, in2.m[ 2 ] ) + in2.m[ 2 ][ 3 ];
}

float cMath::VecLength( Vector& vec )
{
    return sqrt( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) );
}

float cMath::VecDist(const Vector& fVec1, Vector& fVec2)
{
    return sqrt( pow( fVec1.x - fVec2.x, 2 ) + pow( fVec1.y - fVec2.y, 2 ) + pow( fVec1.z - fVec2.z, 2 ) );
}

float cMath::GetFov(QAngle eyePosition, Vector playerHeadPosition, Vector entityHeadPosition)
{
    QAngle newAngles = CalcAngle(playerHeadPosition, entityHeadPosition);
    
    float yaw = ((float) sin(fabsf(eyePosition.y - newAngles.y) * M_PI / 180)) * VecDist(playerHeadPosition, entityHeadPosition);
    float pitch = ((float) sin(fabsf(eyePosition.x - newAngles.x) * M_PI / 180)) * VecDist(playerHeadPosition, entityHeadPosition);
    
    return sqrt((yaw * yaw) + (pitch * pitch));
}

QAngle cMath::CalcAngle( Vector PlayerPos, Vector EnemyPos )
{
    QAngle AimAngles;
    Vector delta = PlayerPos - EnemyPos;
    float hyp = sqrt( ( delta.x * delta.x ) + ( delta.y * delta.y ) );
    AimAngles.x = atanf( delta.z / hyp ) * M_RADPI;
    AimAngles.y = atanf( delta.y / delta.x ) * M_RADPI;
    if( delta.x >= 0.0 )
        AimAngles.y += 180.0f;
    
    return AimAngles;
}

void cMath::VectorAngles( const Vector& dir, QAngle &angles )
{
    float hyp = sqrt( ( dir.x * dir.x ) + ( dir.y * dir.y ) );
    angles.x = atanf( dir.z / hyp ) * M_RADPI;
    angles.y = atanf( dir.y / dir.x ) * M_RADPI;
    if( dir.x >= 0.0 )
        angles.y += 180.0f;
}

void cMath::ClampAngle( QAngle& angles )
{
    if( angles.x < -89.0f )
        angles.x = 89.0f;
    if( angles.x >  89.0f )
        angles.x = 89.0f;
    if( angles.y < -180.0f )
        angles.y += 360.0f;
    if( angles.y >  180.0f )
        angles.y -= 360.0f;
}

void cMath::VectorNormalize( Vector& v )
{
    float l = VecLength( v );
    if( l != 0.0f )
    {
        v /= l;
    }
    else
    {
        v.x = v.y = 0.0f; v.z = 1.0f;
    }
}

void cMath::SmoothAngle( const QAngle& ViewAngle, QAngle& DestAngles, float smooth)
{
    QAngle vecDelta = ViewAngle - DestAngles;
    ClampAngle( vecDelta );
    DestAngles = ViewAngle - vecDelta / 100.0f * smooth; // 50.0f is ur smooth value
}

void cMath::MakeVector( Vector angle, Vector& vector )
{
    float pitch = float( angle[ 0 ] * M_PI / 180 );
    float yaw = float( angle[ 1 ] * M_PI / 180 );
    float tmp = float( cos( pitch ) );
    vector[ 0 ] = float( -tmp * -cos( yaw ) );
    vector[ 1 ] = float( sin( yaw )*tmp );
    vector[ 2 ] = float( -sin( pitch ) );
}

Vector cMath::AngleToDirection( QAngle angle )
{
    // Convert angle to radians
    angle.x = ( float )DEG2RAD( angle.x );
    angle.y = ( float )DEG2RAD( angle.y );
    
    float sinYaw = sin( angle.y );
    float cosYaw = cos( angle.y );
    
    float sinPitch = sin( angle.x );
    float cosPitch = cos( angle.x );
    
    Vector direction;
    direction.x = cosPitch * cosYaw;
    direction.y = cosPitch * sinYaw;
    direction.z = -sinPitch;
    
    return direction;
}

void cMath::VectorITransform( Vector& in1, const Matrix3x4& in2, Vector& out )
{
    float in1t[ 3 ];
    
    in1t[ 0 ] = in1.x - in2.m[ 0 ][ 3 ];
    in1t[ 1 ] = in1.y - in2.m[ 1 ][ 3 ];
    in1t[ 2 ] = in1.z - in2.m[ 2 ][ 3 ];
    
    out.x = in1t[ 0 ] * in2.m[ 0 ][ 0 ] + in1t[ 1 ] * in2.m[ 1 ][ 0 ] + in1t[ 2 ] * in2.m[ 2 ][ 0 ];
    out.y = in1t[ 0 ] * in2.m[ 0 ][ 1 ] + in1t[ 1 ] * in2.m[ 1 ][ 1 ] + in1t[ 2 ] * in2.m[ 2 ][ 1 ];
    out.z = in1t[ 0 ] * in2.m[ 0 ][ 2 ] + in1t[ 1 ] * in2.m[ 1 ][ 2 ] + in1t[ 2 ] * in2.m[ 2 ][ 2 ];
}

void cMath::VectorIRotate( Vector& in1, const Matrix3x4& in2, Vector& out )
{
    out.x = in1.x*in2.m[ 0 ][ 0 ] + in1.y*in2.m[ 1 ][ 0 ] + in1.z*in2.m[ 2 ][ 0 ];
    out.y = in1.x*in2.m[ 0 ][ 1 ] + in1.y*in2.m[ 1 ][ 1 ] + in1.z*in2.m[ 2 ][ 1 ];
    out.z = in1.x*in2.m[ 0 ][ 2 ] + in1.y*in2.m[ 1 ][ 2 ] + in1.z*in2.m[ 2 ][ 2 ];
}
