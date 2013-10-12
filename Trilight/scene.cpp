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
    background.color.setRGBA(0xFFFFFFFF);
    rectangles.push_back(background);
    
    Rect test(150,250,150,150);
    test.color.setRGBA(0xFF0000FF);
    hidden.push_back(test);
    
    eyeball = new Octpus(304,336,32,64);
}

void Scene::clear_scene(){
    if (eyeball) delete eyeball;
    if (!rectangles.empty()) rectangles.clear();
    if (!hidden.empty()) hidden.clear();
}

void Scene::render(){
    
    for(int i = 0; i < rectangles.size(); i++) {
        //Render rect
        rectangles[i].render();
    }
    
    if (eyeball) eyeball->render();
}

void Scene::update(SDL_Event event){
    eyeball->update(event);
}

std::vector<Rect>Scene::get_hidden(){
    return hidden;
}
std::vector<Rect>Scene::get_rect(){
    return rectangles;
}
