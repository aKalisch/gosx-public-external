//
//  bsp.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 25.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef bsp_hpp
#define bsp_hpp

#include "Common.h"

#include "bspDefs.h"
#include "Math.h"

class cBspParser
{
public:
    cBspParser(std::string gameDirectory, std::string mapFile);
    void SetMapFile(std::string mapFile);
    std::string GetMapFile();
    void readBSP(bool debug = false);
    void Unload();
    template<typename T>
    void ReadLump(std::ifstream& map, std::vector<T>& elements, unsigned int index)
    {
        elements.clear();
        if (m_header.lumps[index].filelen == 0)
        {
            return;
        }
        
        map.seekg(m_header.lumps[index].fileofs);
        
        for (int x = 0; x < m_header.lumps[index].filelen / sizeof(T); x++)
        {
            T element;
            map.read((char*)&element, sizeof(T));
            elements.push_back(element);
        }
    }
    
    void printInfo();
    dleaf* GetLeafFromPoint(const Vector point);
    bool isVisible(const Vector &vStart, const Vector &vEnd);
private:
    std::string m_map;
    std::string m_directory;
    dheader m_header;
    std::vector<dnode> m_node;
    std::vector<dplane> m_plane;
    std::vector<dleaf> m_leaf;
};

#endif /* bsp_hpp */
