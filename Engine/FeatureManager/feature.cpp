//
//  feature.cpp
//  GOSXV3
//
//  Created by Andre Kalisch on 26.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "feature.h"

void cFeatureManager::GetGlowEspThread(cEngine* engine) {
    cSettingsManager* settings = engine->GetSettingsManager();
    cGlowEsp* g_cGlow = new cGlowEsp(engine);
    while (true) {
        if(
           settings->GetHackenabled() &&
           settings->GetGlowenabled()
           ) {
            if(engine->GetEngineClient()->isInGame()) {
                g_cGlow->applyGlow();
            }
        }
        usleep(17000);
    }
    return;
}

void cFeatureManager::GetBunnyHopThread(cEngine* engine) {
    cSettingsManager* settings = engine->GetSettingsManager();
    cBunnyHop* g_cBhop = new cBunnyHop(engine);
    while (true) {
        if(
           settings->GetHackenabled() &&
           settings->GetHopenabled()
           ) {
            if(engine->GetEngineClient()->isInGame()) {
                g_cBhop->apply();
            }
        }
        
        usleep(250);
    }
    return;
}

void cFeatureManager::GetAimHelperThread(cEngine* engine) {
    cSettingsManager* settings = engine->GetSettingsManager();
    cAimHelper* g_cAimHelper = new cAimHelper(engine);
    while (true) {
        if(
           settings->GetHackenabled() &&
           settings->GetAimbot()
           ) {
            if(engine->GetEngineClient()->isInGame()) {
                g_cAimHelper->apply();
            }
        }
        
        usleep(1000);
    }
    return;
}

void cFeatureManager::GetExtrasThread(cEngine* engine) {
    cSettingsManager* settings = engine->GetSettingsManager();
    cExtraManager* g_cExtras = new cExtraManager(engine);
    while (true) {
        if(settings->GetHackenabled()) {
            if(engine->GetEngineClient()->isInGame()) {
                if(settings->GetNoFlashEnabled()) { g_cExtras->FlashReducer(); }
                if(settings->GetKnifeBot()) { g_cExtras->KnifeBot(); }
                if(settings->GetAutoCrouch()) { g_cExtras->AutoDuck(); }
                if(settings->GetAutoPistol()) { g_cExtras->AutoPistolSwitch(); }
                if(settings->GetAutoKnife()) { g_cExtras->AutoPistolToKnifeSwitch(); }
            }
        }
        usleep(20000);
    }
    return;
}

void cFeatureManager::GetTriggerBotThread(cEngine* engine) {
    cSettingsManager* settings = engine->GetSettingsManager();
    cTriggerBot* g_cTriggerBot = new cTriggerBot(engine);
    while (true) {
        if(
           settings->GetHackenabled() &&
           settings->GetTriggerenabled()
           ) {
            if(engine->GetEngineClient()->isInGame()) {
                g_cTriggerBot->apply();
            }
        }
        
        usleep(100);
    }
    return;
}
