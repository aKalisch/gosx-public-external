//
//  GlowEsp.h
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef GlowEsp_h
#define GlowEsp_h

#include "engine.h"

class cGlowEsp {
public:
    cGlowEsp(cEngine* engineFactory);
    void applyGlow();
private:
    cEngine* engine;
    cBspParser* bsp;
    uint64_t registeredEntitys[256];
};

#endif /* GlowEsp_h */
