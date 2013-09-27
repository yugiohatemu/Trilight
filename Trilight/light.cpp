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
    
    //recreat fan polygon for clipping surface usage
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
    fan.add_point(position);
    glEnd();
}

//sutherland - holander algorithm

void Light::render_clip(Rect object){
    //get the fan, reuse it from render
    std::vector<Edge> clip_edges = fan.getEdges();
    std::vector<Edge> rect_edges = object.getEdges();
    //std::vector<Point> output;
    
    for (int i = 0; i < rect_edges.size(); i++) {
        //erase(iter++)
        for (std::vector<Edge>::iterator it = clip_edges.begin(); it != clip_edges.end(); it++) {
            //test cross product (V_(i+1) - V_i) x (P - V_i)
            
            //test for intersection directly, then find the point that is inside
            
            //dirty inside test
            bool s_in =  object.is_inside((*it).get_start());
            bool e_in = object.is_inside((*it).get_end());
            //replace it
            if (!s_in && !e_in) {
                clip_edges.erase(it++);
//                std::cout<<"1"<<std::endl;
            }else if(!s_in || !e_in){
                float t_up = (rect_edges[i].get_start() - (*it).get_start()).cross(rect_edges[i].get_vector());
                float div_down = rect_edges[i].get_vector().cross((*it).get_vector());
                if (div_down == 0) div_down = 1;
                
                float t = t_up / div_down;
                Point p = (*it).get_start() + t* (*it).get_vector();
                
                if (s_in) (*it).set_end(p);
                else (*it).set_start(p);
            }
            
            
            
        }
    }
    
    
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 0.0f, 0.0f, specular.a);
    
    for (int i = 0; i < clip_edges.size(); i++) {
        glVertex2f(clip_edges[i].get_start().x, clip_edges[i].get_start().y);
        glVertex2f(clip_edges[i].get_end().x, clip_edges[i].get_end().y);
    }
    
    glEnd();
}