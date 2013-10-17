//
//  octpus.h
//  Trilight
//
//  Created by Yue on 10/12/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__octpus__
#define __Trilight__octpus__

#include "sprite.h"
#include "light.h"

//octupus prime, short for octpus
class Octpus:public Sprite{
    void set_clip();
    enum {
        HEAD_0, HEAD_1,HEAD_2,
        TOTAL_CLIPS,
    }CLIPS;
    
    T_Rect clips[TOTAL_CLIPS];
    bool pressed[4] = {false};
    Light * torch;

    float angel;
    Point bot_left, bot_right, top_left, top_right;
    Point anchor;
public:
    Octpus(int x = 0, int y = 0, int w = 0, int h = 0);
    ~Octpus();
    void render();
    void update(SDL_Event event);
};


#endif /* defined(__Trilight__octpus__) */
