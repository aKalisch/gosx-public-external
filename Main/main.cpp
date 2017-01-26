#include "main.h"

cEngine* engineFactory = new cEngine("csgo_osx64");

#include "init.h"
#include "feature.h"

bool redrawInterface = true;

int main() {
    std::thread TINIT(cInitManager::InitHack, engineFactory);
    TINIT.join();
    
    redrawInterface = true;
    
    if (redrawInterface) {
        std::system("clear");
        printf("CS:GO Hack started...\n");
        redrawInterface = false;
    }
    
    std::thread TBHOP(cFeatureManager::GetBunnyHopThread, engineFactory);
    TBHOP.detach();
    std::thread TTRIG(cFeatureManager::GetTriggerBotThread, engineFactory);
    TTRIG.detach();
    std::thread TAIMH(cFeatureManager::GetAimHelperThread, engineFactory);
    TAIMH.detach();
    std::thread TEXTR(cFeatureManager::GetExtrasThread, engineFactory);
    TEXTR.detach();
    std::thread TGLOW(cFeatureManager::GetGlowEspThread, engineFactory);
    TGLOW.join();
    
    if (redrawInterface) {
        std::system("clear");
        printf("CS:GO closed. Hack closed, too.\n");
        redrawInterface = false;
    }
    
	return 0;
}
