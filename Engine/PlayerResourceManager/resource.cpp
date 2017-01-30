//
//  resource.cpp
//  GOSXV3
//
//  Created by Andre Kalisch on 29.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "resource.h"


cPlayerResource::cPlayerResource(cMemoryManager* memMngr, cOffsetManager* offMngr) {
    mem = memMngr;
    offset = offMngr;
    PlayerResource = mem->read<uint64_t>(offset->client.m_dwPlayerResource);
}

int cPlayerResource::GetKills(int index) {
    return mem->read<int>(PlayerResource + offset->client.m_iKills + (0x4 * index));
}

int cPlayerResource::GetAssists(int index) {
    return mem->read<int>(PlayerResource + offset->client.m_iAssists + (0x4 * index));
}

int cPlayerResource::GetDeaths(int index) {
    return mem->read<int>(PlayerResource + offset->client.m_iDeaths + (0x4 * index));
}

int cPlayerResource::GetArmor(int index) {
    return mem->read<int>(PlayerResource + offset->client.m_iArmor + (0x4 * index));
}

const char* cPlayerResource::GetCompetitiveRank(int index) {
    return Ranks[mem->read<int>(PlayerResource + offset->client.m_iCompetitiveRanking + (0x4 * index))];
}

int cPlayerResource::GetCompetitiveWins(int index) {
    return mem->read<int>(PlayerResource + offset->client.m_iCompetitiveWins + (0x4 * index));
}


bool cPlayerResource::hasHelmet(int index) {
    return mem->read<bool>(PlayerResource + offset->client.m_bHasHelmet + (0x1 * index));
}

bool cPlayerResource::hasDefuser(int index) {
    return mem->read<bool>(PlayerResource + offset->client.m_bHasDefuser + (0x1 * index));
}

bool cPlayerResource::isConnected(int index) {
    return mem->read<bool>(PlayerResource + offset->client.m_bConnected + (0x1 * index));
}
