//
//  utility.h
//  Trilight
//
//  Created by Yue on 10/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__utility__
#define __Trilight__utility__

#include <string>
#include "SDL/SDL.h"
#include <iostream>
#include "SDL/SDL_opengl.h"

template<class PRINT>

void debug(PRINT s){
    std::cout<<"DEBUG: "<<s<<std::endl;
}

template<class A_Rect, class B_Rect>

bool check_collision( A_Rect A, B_Rect B ){
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
        return false;
    
    //If none of the sides from A are outside B
    return true;
}

std::string readFile(std::string filename);
int printOglError(char *file, int line);
void printShaderInfoLog(GLuint obj);
void printProgramInfoLog(GLuint obj);
#endif /* defined(__Trilight__utility__) */
