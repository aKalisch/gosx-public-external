//
//  init.cpp
//  GOSXV3
//
//  Created by Andre Kalisch on 26.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "init.h"

void cInitManager::InitHack(cEngine* engine) {
    bool noPid              = false;
    bool noTask             = false;
    bool notInGame          = false;
    bool redrawInterface    = true;
    
    while (engine->GetPid() == -1)
    {
        if (redrawInterface) {
            noPid = true;
            std::system("clear");
            printf("CS:GO not running!\n");
            redrawInterface = false;
        }
        usleep(3000000);
        engine->Refresh();
    }
    noPid = false;
    redrawInterface = true;
    
    while (engine->GetTask() == 0 && engine->GetPid() != -1) {
        if (redrawInterface) {
            noTask = true;
            std::system("clear");
            printf("No CS:GO task found!\n");
            redrawInterface = false;
        }
        usleep(3000000);
        engine->Refresh();
    }
    
    noTask = false;
    redrawInterface = true;
    bool isIngame = engine->GetEngineClient()->isInGame();
    while (
        !isIngame &&
        engine->GetTask() != 0 &&
        engine->GetPid() != -1
    ) {
        if (redrawInterface) {
            notInGame = true;
            std::system("clear");
            printf("Not in CS:GO Match!\n");
            redrawInterface = false;
        }
        usleep(3000000);
        isIngame = engine->GetEngineClient()->isInGame();
    }
    
    engine->Refresh();
}
