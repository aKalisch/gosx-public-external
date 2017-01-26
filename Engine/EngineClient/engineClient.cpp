//
//  engineClient.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "engineClient.h"

cEngineClient::cEngineClient(cMemoryManager* memMngr, cOffsetManager* offMngr) {
    memoryManager = memMngr;
    offsetManager = offMngr;
    engineClientPointer = memoryManager->read<uint64_t>(offsetManager->engine.m_dwCEngineClient);
    gameDirectory = memoryManager->readstring(offsetManager->engine.m_szGameDirectory);
}

int cEngineClient::getMaxPlayers() {
    if(maxPlayers == -1) {
        maxPlayers = memoryManager->read<int>(engineClientPointer + offsetManager->engine.m_dwGetMaxClients);
    }
    
    return maxPlayers;
}

std::string cEngineClient::GetMapFile() {
    return memoryManager->readstring(engineClientPointer + offsetManager->engine.m_szMapFile);
}

std::string cEngineClient::GetMapName() {
    return memoryManager->readstring(engineClientPointer + offsetManager->engine.m_szMapName);
}

std::string cEngineClient::GetGameDirectory() {
    if(gameDirectory == "") {
        gameDirectory = memoryManager->readstring(offsetManager->engine.m_szGameDirectory);
    }
    
    return gameDirectory;
}

bool cEngineClient::isConnected() {
    connectState = memoryManager->read<int>(engineClientPointer + offsetManager->engine.m_dwIsInGame);
    if(connectState > 0) {
        return true;
    }
    
    return false;
}

bool cEngineClient::isInGame() {
    if(isConnected()) {
        if(connectState == 6) {
            return true;
        }
    }
    
    return false;
}

QAngle cEngineClient::getViewAngles() {
    return memoryManager->read<QAngle>(engineClientPointer + offsetManager->engine.m_setViewAngle);
}

void cEngineClient::setViewAngles(QAngle viewAngle) {
    if(!viewAngle.IsZero()) {
        memoryManager->write<QAngle>(engineClientPointer + offsetManager->engine.m_setViewAngle, viewAngle);
    }
}

void cEngineClient::fullUpdate() {
    memoryManager->write<int>(engineClientPointer + offsetManager->engine.m_dwFullUpdate, -1);
}
