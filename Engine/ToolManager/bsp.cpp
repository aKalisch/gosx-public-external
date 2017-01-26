//
//  bsp.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "bsp.h"

cBspParser::cBspParser(std::string gameDirectory, std::string mapFile) {
    m_map = mapFile;
    m_directory = gameDirectory;
}

void cBspParser::Unload()
{
    m_header   = {};
    m_plane    = {};
    m_node     = {};
    m_leaf     = {};
}

void cBspParser::SetMapFile(std::string mapFile) {
    m_map = mapFile;
}

std::string cBspParser::GetMapFile() {
    return m_map;
}

void cBspParser::readBSP(bool debug)
{
    std::string filePath = m_directory + "/" + m_map;
    std::ifstream file (filePath, std::ios::binary);
    
    if(!file.is_open())
    {
        return;
    }
    
    file.seekg(0);
    file.read((char*)&m_header, sizeof(dheader));
    
    ReadLump(file, m_node, LUMP_NODES);
    ReadLump(file, m_plane, LUMP_PLANES);
    ReadLump(file, m_leaf, LUMP_LEAVES);
    
    if(debug) {
        printInfo();
    }
    
    file.close();
}

void cBspParser::printInfo()
{
    printf("Ident    : %i\n", m_header.ident);
    printf("Map      : %s\n", m_map.c_str());
    printf("Version  : %i\n", m_header.version);
    printf("Revision : %i\n", m_header.mapRevision);
}

dleaf* cBspParser::GetLeafFromPoint(const Vector point)
{
    int nodenum = 0;
    dnode_t * node;
    dplane_t * plane;
    
    float d = 0.0f;
    
    while (nodenum >= 0)
    {
        node = &m_node[nodenum];
        plane = &m_plane[node->planenum];
        d = cMath::Dot(point, plane->normal) - plane->dist;
        if (d > 0)
        {
            nodenum = node->children[0];
        }
        else
        {
            nodenum = node->children[1];
        }
    }
    
    return &m_leaf[-nodenum - 1];
}


bool cBspParser::isVisible(const Vector &vStart, const Vector &vEnd)
{
    Vector direction = vEnd - vStart;
    Vector point = vStart;
    
    int steps = (int)cMath::VecLength(direction);
    
    if (steps > 4000)
    {
        return false;
    }
    
    direction /= (float)steps;
    
    dleaf* leaf = nullptr;
    
    while (steps)
    {
        point += direction;
        leaf = GetLeafFromPoint(point);
        if (
            leaf->contents & CONTENTS_SOLID ||
            leaf->contents & CONTENTS_DETAIL
        )
        {
            return false;
        }
        
        --steps;
    }
    return true;
}
