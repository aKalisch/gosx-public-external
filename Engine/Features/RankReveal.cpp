//
//  RankReveal.cpp
//  GOSXV3
//
//  Created by Andre Kalisch on 27.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "RankReveal.h"

cRankReveal::cRankReveal(cEngine* engine) {
    engineFactory = engine;
    settingsManager = engineFactory->GetSettingsManager();
}

void cRankReveal::run() {
    cRadarManager* radar = engineFactory->GetRadarManager();
    cPlayerResource* res = engineFactory->GetPlayerResource();
    for(int i = 1; i < engineFactory->GetEngineClient()->getMaxPlayers(); i++) {
        cEntityManager* entity = engineFactory->GetEntity(i);
        if(!entity->isValidPlayer()) {
            continue;
        }
        
        if(!res->isConnected(i)) {
            // continue;
        }
        
        printf("#%i : ", i);
        printf("0x%llx -> ", entity->GetPointer());
        printf("%ls -> ", radar->GetEntityName(i).name);
        printf("%s -> ", res->GetCompetitiveRank(i));
        printf("%i\n", res->GetCompetitiveWins(i));
    }
}
