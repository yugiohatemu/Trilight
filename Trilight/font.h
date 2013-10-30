//
//  font.h
//  Trilight
//
//  Created by Yue on 10/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__font__
#define __Trilight__font__

#include "sprite.h"
#include <vector>
#include <string>


struct Character{
    char ch;
    SDL_Rect box;
    T_Rect clip;
    //T_Polygon? clipeed
    //Polygon box?
    bool hidden;
};
//make a rect and ask it returns necessaries

class Font:public Sprite{
    void set_clip();
    enum {
        A,B,C,D,E,F,G,
        H,I,J,K,L,M,N,
        O,P,Q,R,S,T,U,
        V,W,X,Y,Z,SPACE,
        TOTAL_CLIPS,
    }CLIPS;
    std::vector<int> texts;
   
    T_Rect clips[TOTAL_CLIPS];
public:
    Font(std::string s);
    ~Font();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Trilight__font__) */