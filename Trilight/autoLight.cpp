//
//  autoLight.cpp
//  Trilight
//
//  Created by Yue on 10/30/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "autoLight.h"
#include "shader.h"

AutoLight::AutoLight( float start_angel, float end_angel, float speed):Light(start_angel){
    this->start_angel = std::min(start_angel, end_angel);
    this->end_angel = std::max(start_angel, end_angel);
    this->speed = speed;
    
    current_angel = (start_angel + end_angel) /2;
    range = end_angel - start_angel;
    rotate_angle = current_angel - start_angel;
    
    dir = true;
}

AutoLight::~AutoLight(){
    
}

void AutoLight::render(){
    Shader::Instance().use_shader();
    Light::render();
    glUseProgram(0);
}

void AutoLight::update(SDL_Event event){
    if (dir) current_angel += speed;
    else current_angel -= speed;
    
    if (current_angel > end_angel) {
        current_angel = end_angel;
        dir = !dir;
    }else if(current_angel < start_angel){
        current_angel = start_angel;
        dir = !dir;
    }
    
    rotate_angle = current_angel - start_angel;
}