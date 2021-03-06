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
#include "texture.h"
#include "scene.h"

Light::Light(int range){
    this->range = range;
    rotate_angle = 0;
}

void Light::rotate(int x, int y){
    float dx = x - position.x;
    float dy = y - position.y;
    rotate_angle = atan2f(dy,dx) * 180 / 3.14159;
    
}

void Light::set_rotate_angel(float r){
    rotate_angle = r;
}


void Light::render(){
    glPushMatrix();
    glLoadIdentity();
    
    fan.clear_point();
    
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(specular.r, specular.g, specular.b, specular.a);
    glVertex2f(position.x, position.y);
    
    fan.add_point(position);
    //get edge list, do colllision detection
    
    std::vector<Edge> edge_list = Scene::Instance().get_edge_list();
    
    for(int i = - range/2; i < range/2 ; i++){
        float angle = (i + rotate_angle) * 3.14159 / 180;
        float t = 1.0f; //use this to derive alpha
        
        Vector ray(size * cos(angle), size * sin(angle));
        fan.add_point(position + ray);
        
        //for every thing obstacle need to detect, do a test get the closest hit on the scene
        for (int j = 0; j < edge_list.size(); j++) {
            Vector edge_vec = edge_list[j].get_vector();
            if (!is_vector_parallel(edge_vec, ray)) {
                
                float t_up = (edge_list[j].get_start() - position).cross(edge_vec);
                float u_up = (edge_list[j].get_start() - position).cross(ray);
                
                float div_down = ray.cross(edge_vec);
                
                float new_t = t_up / div_down;
                float u =  u_up / div_down;
                
                //within line segment, and less than the previous one, replace it
                if (new_t >= 0 &&  new_t < t && u >= 0 && u <= 1) {
                    t = new_t;
                }
            }
        }
        
        glColor4f(specular.r, specular.g, specular.b, 1.0f - t);
        glVertex2f(position.x + ray.x * t, position.y + ray.y * t);
    }
    
    glEnd();
    glPopMatrix();

}


//sutherland - holander algorithm, check wikipedia page for pusedo implementation
//reference: CS488 course note, clip

std::vector<Point> Light::render_clip(Rect rect){
    //TODO: finish this using edge instead of rect
    //get the fan, reuse it from render
    std::vector<Edge> clip_edges = fan.getEdges();
    std::vector<Edge> rect_edges = rect.getEdges();
    std::vector<Vector> noraml_inside = rect.getNormals();
    
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
    
    //now we have all the points ready
    std::vector<Point> final;
    for ( std::vector<Edge> ::iterator it  = clip_edges.begin(); it != clip_edges.end(); it++) {
        final.push_back((*it).get_start());
    }
    return final;
}

void Light::update(SDL_Event event){
 
    
}