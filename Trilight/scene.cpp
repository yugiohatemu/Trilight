//
//  scene.cpp
//  Trilight
//
//  Created by Yue on 10/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "scene.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "sprite.h"
#include <iostream>



Scene::Scene(){
    Rect background(0,80,640,320);
    background.color.setRGBA(0x00990066);
    rectangles.push_back(background);
    light = new Light(45);
    light->position.x = 320;
    light->position.y = 240;
    light->specular.setRGBA(0xFFFFFF66);
    light->size = 300.0f;
    
    eyeball = new Sprite(304,224);
    
}

Scene::~Scene(){
    delete eyeball;
    delete light;
}

void Scene::render(){
    
    for(int i = 0; i < rectangles.size(); i++) {
        //Render rect
        rectangles[i].render();
    }
    light->render(rectangles);
    eyeball->render();
}

void Scene::update(SDL_Event event){
    eyeball->update(event);
}
