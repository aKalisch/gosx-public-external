//
//  BunnyHop.h
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef BunnyHop_h
#define BunnyHop_h

#include "engine.h"

class cBunnyHop
{
public:
    cBunnyHop(cEngine* engine);
    void apply();
private:
    cEngine* EngineFactory;
};

#endif /* BunnyHop_h */
