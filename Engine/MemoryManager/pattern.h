//
//  pattern.hpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef pattern_hpp
#define pattern_hpp

#include "../MemoryManager/memory.h"

class cPatternScanner {
public:
    cPatternScanner(cMemoryManager * memMngr, sModule module);

    void readBuffer(uint64_t dwStart, size_t dwSize);
    void unload();
    bool maskCheck(int nOffset, Byte* btPattern, const char * strMask, int sigLength);
    uint64_t scan(Byte* pSignature, const char * pMask, int sigLength);
    uint32_t getOffset(Byte* pSignature, const char * pMask, uint64_t start);
    uint32_t getPointer(Byte* pSignature, const char * pMask, uint32_t start);
    
private:
    ~cPatternScanner();
    cMemoryManager* mem;
    Byte* pRemote;
    size_t bufferSize;
    uint64_t moduleStart;
};

#endif /* pattern_hpp */
