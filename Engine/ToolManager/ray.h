#ifndef ray_hpp
#define ray_hpp

#include "sdk.h"

class cViewRay {
public:
    Vector origin, direction, directionInverse;
    cViewRay(Vector _origin, Vector _direction);
    bool Trace(Vector leftBottom, Vector rightTop, float &distance);
};

#endif
