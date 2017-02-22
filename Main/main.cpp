#include "main.h"

cEngine* engineFactory = new cEngine("csgo_osx64");

#include "init.h"
#include "feature.h"

bool redrawInterface = true;

int main() {
    std::thread TINIT(cInitManager::InitHack, engineFactory);
    TINIT.join();
    
    redrawInterface = true;
    
    int maxTries = 10;
    int currTries = 0;
    bool isTheaterMode = true;
    cEntityManager* lp = engineFactory->GetLocalEntity();
    while(!lp->isValidLivePlayer()) {
        if(currTries < maxTries) {
            std::string dots = "";
            system("clear");
            
            for(int i = 0; i < currTries; i++) {
                dots += ".";
            }
            printf("Checking Player Mode%s\n", dots.c_str());
            currTries++;
            usleep(500000);
            if(lp->isValidLivePlayer()) {
                isTheaterMode = false;
                break;
            }
            continue;
        }
        
        break;
    }
    
    if(lp->isValidLivePlayer()) {
        isTheaterMode = false;
    }
    
    if (redrawInterface) {
        std::system("clear");
        printf("== CS:GO:SX V3 ==\n");
        redrawInterface = false;
    }
    
    if(!isTheaterMode) {
        printf("- Mode: Player Mode\n");
    
        std::thread TBHOP(cFeatureManager::GetBunnyHopThread, engineFactory);
        TBHOP.detach();
        std::thread TTRIG(cFeatureManager::GetTriggerBotThread, engineFactory);
        TTRIG.detach();
        std::thread TAIMH(cFeatureManager::GetAimHelperThread, engineFactory);
        TAIMH.detach();
        std::thread TEXTR(cFeatureManager::GetExtrasThread, engineFactory);
        TEXTR.detach();
    } else {
        printf("- Mode: Theater Mode\n");
    }
    std::thread TRANK(cFeatureManager::GetRankRevealThread, engineFactory);
    TRANK.join();
    std::thread TGLOW(cFeatureManager::GetGlowEspThread, engineFactory);
    TGLOW.join();
    
    if (redrawInterface) {
        std::system("clear");
        printf("CS:GO closed. Hack closed, too.\n");
        redrawInterface = false;
    }
    
	return 0;
}
