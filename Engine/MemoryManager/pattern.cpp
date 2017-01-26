//
//  pattern.cpp
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#include "pattern.h"

cPatternScanner::cPatternScanner(cMemoryManager * memMngr, sModule module) {
    mem = memMngr;
    readBuffer(module.base, module.size);
}

cPatternScanner::~cPatternScanner() {
    unload();
}

void cPatternScanner::readBuffer(uint64_t dwStart, size_t dwSize)
{
    pRemote = new Byte[dwSize];
    bufferSize = dwSize;
    moduleStart = dwStart;
    
    pRemote = mem->readData(moduleStart, bufferSize);
}

void cPatternScanner::unload()
{
    delete[] pRemote;
}

bool cPatternScanner::maskCheck(int nOffset, Byte* btPattern, const char * strMask, int sigLength)
{
    for (int x = 0; x < sigLength; x++)
    {
        if (strMask[x] == '?') {
            continue;
        }
        
        if ((strMask[x] == 'x') && (btPattern[x] != pRemote[nOffset + x])) {
            return false;
        }
    }
    
    return true;
}

uint64_t cPatternScanner::scan(Byte* pSignature, const char * pMask, int sigLength)
{
    if(!pRemote) {
        delete[] pRemote;
        return NULL;
    }
    
    for(int dwIndex = 0; dwIndex < bufferSize; dwIndex++) {
        if(maskCheck(dwIndex, pSignature, pMask, sigLength)) {
            return moduleStart + dwIndex;
        }
    }
    
    return NULL;
}

uint32_t cPatternScanner::getOffset(Byte* pSignature, const char * pMask, uint64_t start)
{
    uint64_t signatureAddress = scan(pSignature, pMask, (int)strlen(pMask)) + start;
    uint32_t foundOffset = mem->read<uint32_t>(signatureAddress);
    
    return foundOffset;
}

uint32_t cPatternScanner::getPointer(Byte* pSignature, const char * pMask, uint32_t start)
{
    uint64_t signatureAddress = scan(pSignature, pMask, (int)strlen(pMask)) + start;
    uint64_t fileOffset = signatureAddress - moduleStart;
    uint32_t foundOffset = mem->read<uint32_t>(signatureAddress) + (uint32_t)fileOffset;
    
    return foundOffset;
}
