//
//  Keys.h
//  GO:SX v3
//
//  Created by Andre Kalisch on 24.01.17.
//  Copyright © 2017 Andre Kalisch. All rights reserved.
//

#ifndef Keys_h
#define Keys_h

class cKeyManager {
public:
    bool isPressed(unsigned short inKeyCode)
    {
        unsigned char keyMap[16];
        GetKeys((BigEndianUInt32*) &keyMap);
        return (0 != ((keyMap[ inKeyCode >> 3] >> (inKeyCode & 7)) & 1));
    }
    
    void sendKey(CGKeyCode keyCode, int delay)
    {
        CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);
        
        CGEventRef spaceKeyUp;
        CGEventRef spaceKeyDown;
        
        spaceKeyUp = CGEventCreateKeyboardEvent(source, keyCode, false);
        spaceKeyDown = CGEventCreateKeyboardEvent(source, keyCode, true);
        
        CGEventPost(kCGHIDEventTap, spaceKeyDown);
        usleep(delay);
        CGEventPost(kCGHIDEventTap, spaceKeyUp);
        
        CFRelease(spaceKeyUp);
        CFRelease(spaceKeyDown);
        CFRelease(source);
    }
};

#endif /* Keys_h */
