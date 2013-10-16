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
    
    eyeball = new Octpus(304,336,32,64);
    
    tiles = new TileMap();
    
    int mult = 60;
    int yoff = 100;
    path = new Path(Point(1* mult, 0+ yoff), Point(3* mult, 0+ yoff), Vector(0, 1));
    Path * p1 = new Path(Point(3* mult,0+ yoff), Point(5* mult,2* mult+ yoff), Vector(1,1));
    path->next = p1;
    p1->prev = path;
    
    Path * p2 = new Path(Point(5* mult,2*mult+ yoff), Point(6* mult,2* mult+ yoff), Vector(1,1));
    p1->next = p2;
    p2->prev = p1;
    
}

void Scene::clear_scene(){
    if (eyeball) delete eyeball;
    if (tiles) delete tiles;
    while (path != NULL) {
        Path * temp = path->next;
        delete path;
        path = temp;
    }
    eyeball = NULL;
    tiles = NULL;
    path = NULL;
    
    if (!rectangles.empty()) rectangles.clear();
    if (!hidden.empty()) hidden.clear();
    
}

void Scene::render(){
    
//    for(int i = 0; i < rectangles.size(); i++) {
//        //Render rect
//        rectangles[i].render();
//    }
    if (tiles) tiles->render();
    if (eyeball) eyeball->render();
    if (path){
        glBegin(GL_LINES);
        glColor3f(255, 0, 0);
        Path * temp = path;
        while (temp != NULL) {
            temp->render();
            temp = temp->next;
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

Vector Scene::get_next_direction(Vector dir,float angel,SDL_Rect box){
    //we know the current gravity angel of octupus
    //getting the direction on box, we can get the next gravity angel
    //if changed, using matrix multiplication, we can get the next one
    
    SDL_Rect next_box = box;
    next_box.x += dir.x;
    next_box.y += dir.y;
    //be careful about overflow, since SDL use unsigned short
    
    //TODO: need to add a direction, or gravity angel

    float next_angel =  tiles->get_current_angel(box);
    Vector next = dir;
    
    if (next_angel != angel) {
        next.rotate(next_angel - angel);
    }
    return next;
    
    //given current anchor point,
    Point anchor(1,0);
    Path * currentPath;
    anchor = anchor + dir;
    if (currentPath->is_point_on_path(anchor)) { //anchor point is on current path, then jsut return it
        return dir;
    }else{
        //completely let the path handle that
        //get point on current path
    }
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
