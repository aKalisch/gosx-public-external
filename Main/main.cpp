#include "main.h"

cEngine* engineFactory = new cEngine("csgo_osx64");

#include "feature.h"

bool noPid = false;
bool noTask = false;
bool notInGame = false;
bool redrawInterface = true;
int main() {
    while (engineFactory->GetPid() == -1)
    {
        if (redrawInterface) {
            noPid = true;
            std::system("clear");
            printf("CS:GO not running!\n");
            redrawInterface = false;
        }
        usleep(3000000);
        engineFactory->Refresh("csgo_osx64");
    }
    noPid = false;
    redrawInterface = true;
    
    while (engineFactory->GetTask() == 0 && engineFactory->GetPid() != -1) {
        if (redrawInterface) {
            noTask = true;
            std::system("clear");
            printf("No CS:GO task found!\n");
            redrawInterface = false;
        }
        usleep(3000000);
        engineFactory->Refresh("csgo_osx64");
    }
    
    noTask = false;
    redrawInterface = true;
    bool isIngame = engineFactory->GetEngineClient()->isInGame();
    while (
           !isIngame &&
           engineFactory->GetTask() != 0 &&
           engineFactory->GetPid() != -1
    ) {
        if (redrawInterface) {
            notInGame = true;
            std::system("clear");
            printf("Not in CS:GO Match!\n");
            redrawInterface = false;
        }
        usleep(3000000);
        isIngame = engineFactory->GetEngineClient()->isInGame();
    }
    notInGame = false;
    redrawInterface = true;
    
    if (redrawInterface) {
        notInGame = true;
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
