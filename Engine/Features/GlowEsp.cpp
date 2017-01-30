//
//  GlowEsp.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "GlowEsp.h"

cGlowEsp::cGlowEsp(cEngine* engineFactory)  {
    engine = engineFactory;
    bsp = engine->GetBspParser();
}

void cGlowEsp::applyGlow() {
    cEntityManager* LocalPlayer = engine->GetLocalEntity();
    cSettingsManager* settings = engine->GetSettingsManager();
    cGlowManager* glowManager = engine->GetGlowManager();
    
    bool isGotvMode = true;
    eTeam lTeam = TEAM_Unk;
    Vector posOffset = {0, 0, 0};
    if(LocalPlayer->isValidLivePlayer()) {
        isGotvMode = false;
        lTeam = LocalPlayer->GetTeam();
        posOffset = LocalPlayer->GetPositionOffset();
    }
    
    if(isGotvMode) {
        cEngineClient* engineClient = engine->GetEngineClient();
        for (int i = 1; i < engineClient->getMaxPlayers(); i++) {
            cEntityManager* entity = engine->GetEntity(i);
            if (entity->isValidLivePlayer()) {
                eTeam eTeam = entity->GetTeam();
                if(!settings->GetTeamglow() && lTeam == eTeam) {
                    continue;
                }
                
                sGlowEntity glow = entity->GetGlowObject();
                if(!glow.isValidGlowEntity()) {
                    continue;
                }
                
                float alpha = settings->GetGlowalpha();
                std::string colorBase;
                
                if(!entity->isValidLivePlayer()) {
                    continue;
                }
                
                if(!settings->GetTeamglow() && lTeam == eTeam) {
                    continue;
                }
                
                if(!isGotvMode) {
                    bool entityIsVisible = bsp->isVisible(posOffset, entity->GetPositionOffset());
                    if(eTeam == TEAM_T) {
                        colorBase = settings->GetColorTvisible();
                        if (entityIsVisible) {
                            colorBase = settings->GetColorT();
                        }
                    } else {
                        colorBase = settings->GetColorCTvisible();
                        if(entityIsVisible) {
                            colorBase = settings->GetColorCT();
                        }
                    }
                } else {
                    if(glow.RenderWhenOccluded) {
                        delete entity;
                        continue;
                    }
                    alpha = 0.65f;
                    if (eTeam == TEAM_CT) {
                        colorBase = "114,154,221";
                    } else {
                        colorBase = "231,190,90";
                    }
                }
                
                std::vector<std::string> colors = settings->split<std::string>(colorBase, ",");
                float red = atof(colors[0].c_str()) / 255;
                float green = atof(colors[1].c_str()) / 255;
                float blue = atof(colors[2].c_str()) / 255;
                
                glow.r = red;
                glow.g = green;
                glow.b = blue;
                glow.a = alpha;
                glow.RenderWhenOccluded = true;
                glow.RenderWhenUnoccluded = false;
                
                entity->setGlow(glow);
            }
            delete entity;
        }
    } else {
        for(int i = 0; i < glowManager->GetGlowCount(); i++) {
            sGlowEntity gEntity = glowManager->GetGlowEntity(i);
            if(gEntity.isValidGlowEntity()) {
                cEntityManager* entity = engine->DefineGlowEntity(gEntity.entityPointer);
                if(entity->isValidGlowEntity()) {
                    printf("01\n");
                    
                    bool isWeapon = entity->isWeapon();
                    bool isBomb = entity->isBomb();
                    bool isPlayer = entity->isPlayer();
                    
                    float alpha = settings->GetGlowalpha();
                    std::string colorBase;
                    
                    if(isPlayer) {
                        if(!entity->isValidLivePlayer()) {
                            continue;
                        }
                        printf("2\n");
                        
                        eTeam eTeam = entity->GetTeam();
                        if(!settings->GetTeamglow() && lTeam == eTeam) {
                            continue;
                        }
                        printf("3\n");
                        
                        if(!isGotvMode) {
                            bool entityIsVisible = bsp->isVisible(posOffset, entity->GetPositionOffset());
                            if(eTeam == TEAM_T) {
                                colorBase = settings->GetColorTvisible();
                                if (entityIsVisible) {
                                    colorBase = settings->GetColorT();
                                }
                            } else {
                                colorBase = settings->GetColorCTvisible();
                                if(entityIsVisible) {
                                    colorBase = settings->GetColorCT();
                                }
                            }
                            printf("4\n");
                        } else {
                            if(gEntity.RenderWhenOccluded) {
                                delete entity;
                                continue;
                            }
                            alpha = 0.65f;
                            if (eTeam == TEAM_CT) {
                                colorBase = "114,154,221";
                            } else {
                                colorBase = "231,190,90";
                            }
                            printf("5\n");
                        }
                    } else {
                        if(!isGotvMode) {
                            if((isWeapon || isBomb) && gEntity.RenderWhenOccluded) {
                                continue;
                            }
                            
                            if (isWeapon) {
                                colorBase = "255,0,0";
                            } else if (isBomb) {
                                colorBase = "0,255,0";
                            } else {
                                delete entity;
                                continue;
                            }
                        }
                    }
                    
                    printf("6\n");
                    std::vector<std::string> colors = settings->split<std::string>(colorBase, ",");
                    float red = atof(colors[0].c_str()) / 255;
                    float green = atof(colors[1].c_str()) / 255;
                    float blue = atof(colors[2].c_str()) / 255;
                    
                    gEntity.r = red;
                    gEntity.g = green;
                    gEntity.b = blue;
                    gEntity.a = alpha;
                    gEntity.RenderWhenOccluded = true;
                    gEntity.RenderWhenUnoccluded = false;
                    
                    entity->setGlow(gEntity, i);
                    printf("10\n");
                }
                delete entity;
            }
        }

    }
}
