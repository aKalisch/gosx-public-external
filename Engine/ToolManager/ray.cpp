#include "ray.h"

cViewRay::cViewRay(Vector _origin, Vector _direction) {
    origin = _origin;
    direction = _direction;
    
    directionInverse.x = 1.0f / direction.x;
    directionInverse.y = 1.0f / direction.y;
    directionInverse.z = 1.0f / direction.z;
}

bool cViewRay::Trace(Vector leftBottom, Vector rightTop, float &distance)
{
    if (direction.x == 0.0f && (origin.x < std::min(leftBottom.x, rightTop.x) || origin.x > std::max(leftBottom.x, rightTop.x)))
    {
        return false;
    }
    
    if (direction.y == 0.0f && (origin.y < std::min(leftBottom.y, rightTop.y) || origin.y > std::max(leftBottom.y, rightTop.y)))
    {
        return false;
    }
    
    if (direction.z == 0.0f && (origin.z < std::min(leftBottom.z, rightTop.z) || origin.z > std::max(leftBottom.z, rightTop.z)))
    {
        return false;
    }
    
    float t1 = (leftBottom.x - origin.x) * directionInverse.x;
    float t2 = (rightTop.x - origin.x) * directionInverse.x;
    float t3 = (leftBottom.y - origin.y) * directionInverse.y;
    float t4 = (rightTop.y - origin.y) * directionInverse.y;
    float t5 = (leftBottom.z - origin.z) * directionInverse.z;
    float t6 = (rightTop.z - origin.z) * directionInverse.z;
    
    float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
    float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
    
    if (tmax < 0)
    {
        distance = tmax;
        return false;
    }
    
    if (tmin > tmax)
    {
        distance = tmax;
        return false;
    }
    
    distance = tmin;
    return true; 
}
