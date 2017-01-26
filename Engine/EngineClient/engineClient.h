//
//  engineClient.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef engineClient_hpp
#define engineClient_hpp

#include "Common.h"

#include "memory.h"
#include "offsetMGR.h"

#include "QAngle.h"

class cEngineClient {
public:
    cEngineClient(cMemoryManager* memMngr, cOffsetManager* offMngr);
    int getMaxPlayers();
    std::string GetMapFile();
    std::string GetMapName();
    std::string GetGameDirectory();
    QAngle getViewAngles();
    void setViewAngles(QAngle viewAngle);
    bool isConnected();
    bool isInGame();
    void fullUpdate();
private:
    cMemoryManager* memoryManager;
    cOffsetManager* offsetManager;
    uint64_t engineClientPointer = 0xF;
    int maxPlayers = -1;
    int connectState = 0;
    std::string gameDirectory = "";
};

#endif /* engineClient_hpp */
