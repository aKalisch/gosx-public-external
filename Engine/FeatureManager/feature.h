//
//  feature.hpp
//  GOSXV3
//
//  Created by Andre Kalisch on 26.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef feature_hpp
#define feature_hpp

#include "engine.h"

#include "GlowEsp.h"
#include "BunnyHop.h"
#include "AimHelper.h"
#include "Extras.h"
#include "TriggerBot.h"
#include "RankReveal.h"

class cFeatureManager {
public:
    static void GetGlowEspThread(cEngine* engine);
    static void GetBunnyHopThread(cEngine* engine);
    static void GetAimHelperThread(cEngine* engine);
    static void GetExtrasThread(cEngine* engine);
    static void GetTriggerBotThread(cEngine* engine);
    static void GetRankRevealThread(cEngine* engine);
};

#endif /* feature_hpp */
