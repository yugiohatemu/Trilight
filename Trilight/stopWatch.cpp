//
//  stopWatch.cpp
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "stopWatch.h"
#include "SDL/SDL.h"

StopWatch::StopWatch(double count_down){
    this->count_down = count_down * 1000;
    
//    start_tick = SDL_GetTicks();
}

StopWatch::~StopWatch(){
    
}

bool StopWatch::is_timeup(){
    time_left = time_left -( SDL_GetTicks() - start_tick);
    start_tick = SDL_GetTicks();
    return (time_left <=0);
}

void StopWatch::start(){
    time_left = count_down;
    start_tick = SDL_GetTicks();
}

void StopWatch::reset(){
    time_left = count_down;
}