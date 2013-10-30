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
#include "rect.h"

//make a rect and ask it returns necessaries

class Font:public Sprite{
    struct Char{
        int frame;
        Rect box;
        bool hidden;
        Char &operator = (Char & c){
            box = c.box;
            frame = c.frame;
            hidden = c.hidden;
            return  *this;
        }
    };
    
    void set_clip();
    enum {
        A,B,C,D,E,F,G,
        H,I,J,K,L,M,N,
        O,P,Q,R,S,T,U,
        V,W,X,Y,Z,SPACE,
        TOTAL_CLIPS,
    }CLIPS;
    std::vector<Char> texts;
   
    T_Rect clips[TOTAL_CLIPS];
public:
    Font();
    ~Font();
    void render();
    void make_sentence(std::string s, SDL_Rect box);
    void update(SDL_Event event);
};

#endif /* defined(__Trilight__font__) */
