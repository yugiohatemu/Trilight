//
//  light.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "light.h"
#include "SDL/SDL_opengl.h"
#include <math.h>
#include <iostream>
#include "algebra.h"

Light::Light(int range){
    this->range = range;
    rotate_angle = 0;
}

void Light::rotate(int x, int y){
    float dx = x - position.x;
    float dy = y - position.y;
    rotate_angle = atan2f(dy,dx) * 180 / 3.14159;
    
}


void Light::render(std::vector<Rect>& objects){
    //use triangle fan
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(specular.r, specular.g, specular.b, specular.a);
    glVertex2f(position.x, position.y);
    
    fan.clear_point();
    fan.add_point(position);
    
    for(int i = - range/2; i < range/2 ; i++) {
        float angle = (i + rotate_angle) * 3.14159 / 180;
        float t = 1.0f; //use this to derive alpha
        
        Vector ray(size * cos(angle), size * sin(angle));
        fan.add_point(position + ray);
        for(int j = 0; j < objects.size(); j++) {
            
            std::vector<Point> points = objects[j].getPoints();
            points.push_back(points[0]); //for recursive
            
            for (int p = 0; p < points.size()-1; p+=1) { //need -1
                Vector edge = points[p+1] - points[p];
                
                //not parallel, so must intersect
                if (!is_vector_parallel(edge, ray)) {
                    //t && u should both between 0 and 1, and do not replace unless new_t is smaller
                    //http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
                    
                    float t_up = (points[p] - position).cross(edge);
                    float u_up = (points[p] - position).cross(ray);
                    
                    float div_down = ray.cross(edge);
                    
                    float new_t = t_up / div_down;
                    float u =  u_up / div_down;
                    
                    //within line segment, and less than the previous one, replace it
                    if (new_t >= 0 &&  new_t < t && u >= 0 && u <= 1) {
                        t = new_t;
                    }
                }
            }
        }
        
        glColor4f(specular.r, specular.g, specular.b, 1.0f - t);
        glVertex2f(position.x + ray.x * t, position.y + ray.y * t);
    }
   
    glEnd();
 
}

//sutherland - holander algorithm, check wikipedia page for pusedo implementation
//reference CS488 course note

void Light::render_clip(Rect object){
    
    //get the fan, reuse it from render
    std::vector<Edge> clip_edges = fan.getEdges();
    std::vector<Edge> rect_edges = object.getEdges();
    std::vector<Vector> noraml_inside = object.getNormals();
    
    for (int i = 0; i < rect_edges.size(); i++) {
         //calculate clipping area
         for (std::vector<Edge>::iterator it = clip_edges.begin(); it != clip_edges.end(); ) {
        
            float wec_s = ((*it).get_start() - rect_edges[i].get_start()).dot(noraml_inside[i]);
            float wec_e = ((*it).get_end() - rect_edges[i].get_start()).dot(noraml_inside[i]);
            
            if (wec_s < 0 && wec_e < 0) {
                it = clip_edges.erase(it);
            }else if(wec_s >= 0 && wec_e >= 0){
                ++it;
            }else{
            
                float t = wec_s / (wec_s - wec_e);
                Point intersect = (*it).get_start() + t * (*it).get_vector();
                
                if (wec_s < 0) (*it).set_start(intersect);
                else (*it).set_end(intersect);
                
                ++it;
            }
        }
         
         if (clip_edges.size() == 0) {
             break ; //or just return, since not drawing anything
         }
         
         std::vector<Point> output;
         //connect the missing edge and make it a complete polygon for latter calculation
         for (std::vector<Edge>::iterator it = clip_edges.begin(); it != clip_edges.end(); it++){
             output.push_back((*it).get_start());
             output.push_back((*it).get_end());
         }
         
         for (std::vector<Point>::iterator it = output.begin(); it != output.end(); ) {
             if (it == output.end()-1) {
                 if (*it == output[0]) {
                     output.erase(output.begin());
                 }
                 break ;
             }else if ((*it) == (*(it+1))) {
                 it=output.erase(it);
             }else{
                 ++it;
             }
         }
         
         clip_edges.clear();
         for(std::vector<Point>::iterator it = output.begin(); it != output.end();it++){
             if (it == output.end()-1) {
                 clip_edges.push_back(Edge(*it, output[0]));
             }else{
                 clip_edges.push_back(Edge(*it,*(it+1)));
             }
         }
         
    }
    

    if (clip_edges.size() == 0) {
        return ;
    }
    
    glBegin(GL_TRIANGLE_FAN);
    
    glColor4f(specular.r, specular.g, specular.b, specular.a);
    for (int i = 0; i < clip_edges.size(); i++) {
        glVertex2f(clip_edges[i].get_start().x, clip_edges[i].get_start().y);
        glColor4f(1.0f, 0.0f, 1.0f, 0.5f);
    }
    glEnd();
}

void Light::update(SDL_Event event){
    if (event.type == SDL_KEYDOWN){
        if (event.key.keysym.sym == SDLK_w) pressed[0] = true;
        else if(event.key.keysym.sym == SDLK_a) pressed[1] = true;
        else if(event.key.keysym.sym == SDLK_s) pressed[2] = true;
        else if(event.key.keysym.sym == SDLK_d) pressed[3] = true;
    }else if(event.type == SDL_KEYUP){
        if (event.key.keysym.sym == SDLK_w) pressed[0] = false;
        else if(event.key.keysym.sym == SDLK_a) pressed[1] = false;
        else if(event.key.keysym.sym == SDLK_s) pressed[2] = false;
        else if(event.key.keysym.sym == SDLK_d) pressed[3] = false;
    }
    
    if (pressed[1]) position.x -= 2;
    if (pressed[3]) position.x += 2;
}