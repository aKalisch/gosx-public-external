//
//  BunnyHop.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "BunnyHop.h"

cBunnyHop::cBunnyHop(cEngine* engine) {
    EngineFactory = engine;
}


void cBunnyHop::apply() {
    cEntityManager* localPlayer = EngineFactory->GetLocalEntity();
    if(!localPlayer->isValidLivePlayer()) {
        return;
    }
    
    if(
       localPlayer->GetVelocity().x != 0 &&
       localPlayer->GetVelocity().y != 0 &&
       EngineFactory->GetKeyManager()->isPressed(kVK_Space) &&
       !localPlayer->isInAir()
    )
    {
        
        int randomDelay = ((rand()%(1000-600 + 1) + 600) * 10);
        usleep(randomDelay);
        localPlayer->forceJump();
    }
}
