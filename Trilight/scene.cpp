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
#include "utility.h"

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
    
    Path * p3 = new Path(Point(6* mult,2* mult+ yoff), Point(8* mult, yoff));
    p2->next = p3;
    p3->prev = p2;
    
    Path * p4 = new Path(Point(8* mult, yoff), Point(8* mult, yoff - 3*mult));
    p3->next = p4;
    p4->prev = p3;
    
    Path * p5 = new Path( Point(8* mult, yoff - 3*mult), Point(4* mult, yoff - 3*mult));
    p4->next = p5;
    p5->prev = p4;
    
    //test new light
    test_light = new Light(60.0f);
    test_light->position = Point(320,220);
    test_light->specular.setRGBA(0xFF000066);
    test_light->size = 100.0f;
    test_light->set_rotate_angel(90);

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
    
    if (test_light) delete test_light;
    
    eyeball = NULL;
    tiles = NULL;
    path = NULL;
    test_light = NULL;
    
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
//        glBegin(GL_LINES);
        
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

//        glEnd();
    }
    if (test_light)  test_light->render();
}

void Scene::update(SDL_Event event){
    eyeball->update(event);
}

std::vector<Edge> Scene::get_edge_list(){
    //do a boundary test when the scene get large~~
    
    std::vector<Edge> edge_list;
    Path * prev = path->prev;
    Path * next = path;
    
    while (prev != NULL) {
        Path * temp = prev->prev;
        edge_list.push_back(prev->get_edge());
        prev = temp;
    }
    while (next != NULL) {
        Path * temp = next->next;
        edge_list.push_back(next->get_edge());
        next = temp;
    }
    
    return edge_list;
}


float Scene::get_current_angel(){
    return path->get_angel();
}


Vector Scene::get_next_direction(Vector dir, Point anchor){
    
    Point next_anchor = anchor + dir;
    Point start = path->get_start();
    Point end = path->get_end();
    
    ORIENTATION orien = path->get_orientation(dir);
    ORIENTATION path_orien;
    //need to modify dir?
    if (path->is_orentation_within(orien, path->to_next)) {
        path_orien = path->to_next;
        if (!path->is_point_within_path(next_anchor)){
            
            if (path->next != NULL ) {
                path = path->next;
                Vector left = next_anchor - end;
                float t = left.get_norm();
                dir = path->get_vec() * t;
                return (end-anchor) + get_next_direction(dir, end);
            }else{
                return end-anchor;
            }
        }
        
    }else if (path->is_orentation_within(orien, path->to_prev)){ //we are going to previous
        path_orien = path->to_prev;

        if (!path->is_point_within_path(next_anchor)) {
            if (path->prev != NULL) {
                path = path->prev;
                Vector left = next_anchor - start;
                float t = left.get_norm();
                dir = path->get_vec() * -t;
                return (start - anchor) + get_next_direction(dir, start);
            }else{
                return start - anchor;
            }
        }
    }else{ //do not allow moving unless using the right action
        return Vector();
    }
    //need to adjust orientation based on that
    dir = adjust_vector(path_orien, dir);
//    debug(path_orien);
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
