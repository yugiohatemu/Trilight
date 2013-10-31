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
#include "pathBuilder.h"
#include "font.h"
#include "autoLight.h"

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
    
    eyeball = new Octpus(74,336,32,64); //100-32,400-64
    Octpus * temp = dynamic_cast<Octpus *>(eyeball);
    temp->set_anchor(Point(150,400));
    
    tiles = new TileMap();
    
    path = read_path("/Users/wei/Desktop/Trilight/Trilight/level1.path");
    
    test_light = new AutoLight(60.0f, 150.0f, 3.0f);
    test_light->position = Point(320,220);
    test_light->specular.setRGBA(0xFF000066);
    test_light->size = 150.0f;
//    test_light->set_rotate_angel(90);
    
    text = new Font();
    Font * t_text = dynamic_cast<Font *> (text);
    SDL_Rect t_box;
    t_box.x = 300;
    t_box.y = 300;
    t_box.w = 32;
    t_box.h = 48;
    t_text->make_sentence("H", t_box);

}

void Scene::clear_scene(){
    if (eyeball) delete eyeball;
    if (tiles) delete tiles;
    
    if (path) delete_path(path);
    
    if (test_light) delete test_light;
    
    if (text) delete text;
    
    eyeball = NULL;
    tiles = NULL;
    path = NULL;
    test_light = NULL;
    text = NULL;
    
    if (!rectangles.empty()) rectangles.clear();
    if (!hidden.empty()) hidden.clear();
    
}

void Scene::render(){
    

    if (eyeball) eyeball->render();
    if (path) render_path(path);
    
    if (test_light)  test_light->render();
    
    if (text) text->render();
}

void Scene::update(SDL_Event event){
    eyeball->update(event);
    test_light->update(event);
}

//do a boundary test when the scene get large~~
std::vector<Edge> Scene::get_edge_list(){
    return get_edge_from_path(path);
}

std::vector<Point> Scene::get_clip_point(Rect rect){
    //just use test_light for now
    return test_light->render_clip(rect);
}


float Scene::get_current_angel(){
    return path->get_angel();
}


Vector Scene::get_next_direction(Vector dir, Point anchor){
    
    Point next_anchor = anchor + dir;
    Point start = path->get_start();
    Point end = path->get_end();
    Vector vec = path->get_vec();
    
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
                dir = vec * t;
                return (end-anchor) + get_next_direction(dir, end);
            }else{
                return end-anchor;
            }
        }
        
    }else if (path->is_orentation_within(orien, path->to_prev)){ //we are going to previous
        path_orien = path->to_prev;

        //we are going backward from next to prev, so vec has different direction
        vec = vec * -1;
        if (!path->is_point_within_path(next_anchor)) {
            if (path->prev != NULL) {
                path = path->prev;
                Vector left = next_anchor - start;
                float t = left.get_norm();
                dir = vec * t;
                return (start - anchor) + get_next_direction(dir, start);
            }else{
                return start - anchor;
            }
        }
    }else{ //do not allow moving unless using the right action
        return Vector();
    }
    
    //need to adjust orientation based on that
    dir = adjust_vector(orien, dir, vec);
    return dir;
}


