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
    //w 20
    //h 10
    background.color.setRGBA(0xFFFFFFFF);
    rectangles.push_back(background);
    
    Rect test(150,250,100,150);
    test.color.setRGBA(0xFF0000FF);
    hidden.push_back(test);
    
    eyeball = new Octpus(44,236,32,64);
    
    tiles = new TileMap();
    
    int mult = 60;
    int yoff = 300;
    path = new Path(Point(1* mult, 0+ yoff), Point(3* mult, 0+ yoff));
    Path * p1 = new Path(Point(3* mult,0+ yoff), Point(5* mult,2* mult+ yoff));
    path->next = p1;
    p1->prev = path;
    
    Path * p2 = new Path(Point(5* mult,2*mult+ yoff), Point(6* mult,2* mult+ yoff));
    p1->next = p2;
    p2->prev = p1;
    
}

void Scene::clear_scene(){
    if (eyeball) delete eyeball;
    if (tiles) delete tiles;
    
    Path * prev = path->prev;
    Path * next = path;
    
    while (prev != NULL) {
        Path * temp = prev->prev;
        delete prev;
        prev = temp;
    }
    while (next != NULL) {
        Path * temp = next->next;
        delete next;
        next = temp;
    }
    
    eyeball = NULL;
    tiles = NULL;
    path = NULL;
    
    if (!rectangles.empty()) rectangles.clear();
    if (!hidden.empty()) hidden.clear();
    
}

void Scene::render(){
    
//    for(int i = 0; i < rectangles.size(); i++) {
//        rectangles[i].render();
//    }
//    if (tiles) tiles->render();
    if (eyeball) eyeball->render();
    if (path){
        glBegin(GL_LINES);
        glColor3f(255, 0, 0);
        Path * prev = path->prev;
        Path * next = path;
        
        while (prev != NULL) {
            Path * temp = prev->prev;
            prev->render();
            prev = temp;
        }
        while (next != NULL) {
            Path * temp = next->next;
            next->render();
            next = temp;
        }

        glEnd();
    }
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

Vector Scene::get_next_direction(Vector dir, Point anchor){
    
    Point next_anchor = anchor + dir;
    Vector vec = path->get_vec();
    Point start = path->get_start();
    Point end = path->get_end();
    if (!path->is_point_on_path(next_anchor)) {
        Vector v1 = anchor - path->get_start();
        
        if (vec.cross(v1) == 0) { //using the next
            if (path->next != NULL ) {
                path = path->next;
                Vector left = anchor - end;
                
                float t = left.get_norm();
                dir = path->get_vec() * t;
                return left + get_next_direction(dir, end);
            }else{
                return end-anchor;
            }
        }else{
            if (path->prev != NULL) {
                path = path->prev;
                Vector left = anchor - start;
                float t = left.get_norm();
                dir = path->get_vec() * t;
                return left + get_next_direction(dir, start);
            }else{
                return start - anchor;
            }
        }
    }

    
    return dir;
}


/*
 Rect obstac(400,80,150,100);
 obstac.color.setRGBA(0X00FF00FF);
 
 Rect obstac1(100,300,150,100);
 obstac1.color.setRGBA(0X00FF00FF);
 
 Rect obstac2(0,100,150,120);
 obstac2.color.setRGBA(0X00FF00FF);
 
 Rect obstac3(540,200,100,100);
 obstac3.color.setRGBA(0X00FF00FF);
 
 test_rec.push_back(obstac);
 test_rec.push_back(obstac1);
 test_rec.push_back(obstac2);
 test_rec.push_back(obstac3);*/
