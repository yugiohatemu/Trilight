//
//  autoLight.h
//  Trilight
//
//  Created by Yue on 10/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__autoLight__
#define __Trilight__autoLight__

#include "light.h"

class AutoLight:public Light{
    bool dir;
    float speed;
    float start_angel,end_angel, current_angel;
public:
    AutoLight(float start_angel, float end_angel,float speed);
    ~AutoLight();
    //use rotate_angel differently
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Trilight__autoLight__) */
