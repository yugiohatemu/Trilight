//
//  sprite.h
//  Trilight
//
//  Created by Yue on 10/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__sprite__
#define __Trilight__sprite__

#include "SDL/SDL.h"

class Sprite{
    struct T_Rect{
        float x, y,w,h;
        T_Rect(){ x = y = w = h = 0.0f; }
        T_Rect& operator=(T_Rect t){
            x = t.x;
            y = t.y;
            w = t.w;
            h = t.h;
            return *this;
        }
        ~T_Rect(){}
    };
protected:
    int frame;
    void set_clip();
    enum {
        HEAD_0, HEAD_1,HEAD_2,HEAD_3,
        TOTAL_CLIPS,
    }CLIPS;
    T_Rect clips[TOTAL_CLIPS];
public:
    SDL_Rect box;
    Sprite(int x = 0, int y = 0);
    ~Sprite();
    void set_pos();
    void render();
    void update();
};

#endif /* defined(__Trilight__sprite__) */
