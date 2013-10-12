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
#include "octpus.h"
#include <iostream>


Scene::Scene(){
   
}

Scene::Scene(Scene const &){
    
}

Scene& Scene::operator= (Scene const &){
    return *this;
}

Scene& Scene::Instance(){
    static Scene m_Instance;
    return m_Instance;
}

////////////////////////////////////////////////////////////

void Scene::create_scene(){
    Rect background(0,80,640,320);
    background.color.setRGBA(0x006666FF);
    rectangles.push_back(background);
    light = new Light(45);
    light->position.x = 320;
    light->position.y = 240;
    light->specular.setRGBA(0xFFFF0066);
    light->size = 300.0f;
    
    eyeball = new Octpus(304,224,32,64);
}

void Scene::clear_scene(){
    if (eyeball) delete eyeball;
    if (light) delete light;
}

void Scene::render(){
    
    for(int i = 0; i < rectangles.size(); i++) {
        //Render rect
        rectangles[i].render();
    }
    if (light) light->render(rectangles);
    if (eyeball) eyeball->render();
}

void Scene::update(SDL_Event event){
    eyeball->update(event);
}
