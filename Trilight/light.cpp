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
    
    for(int i = - range/2; i < range/2 ; i++) {
        float angle = (i + rotate_angle) * 3.14159 / 180;
        float t = 1.0f; //use this to derive alpha
        
        Vector ray(size * cos(angle), size * sin(angle));
        
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

void Light::render_clip(Rect object){
    //get the fan, maybe reuse it from render
    std::vector<Point> clip_points;
    clip_points.push_back(position);
    for(int i = - range/2; i < range/2 ; i++) {
        float angle = (i + rotate_angle) * 3.14159 / 180;
        Point p = position + Vector(cos(angle),sin(angle)) * size;
        clip_points.push_back(p);
    }
    clip_points.push_back(position);
    
//    std::vector<Point> output;
    
    
    std::vector<Point> points = object.getPoints();
    points.push_back(points[0]); //for recursive
    
    for (int i = 0; i < points.size() - 1; i += 1) { //-1 for recursive
        Vector edge = points[i + 1] - points[i];
        
        for (int j = 0; j < clip_points.size()-1; j += 1) { //-1 for recursive
            
            Vector clip_edge = clip_points[j + 1] - clip_points[j];
            if (!is_vector_parallel(edge, clip_edge)) {
                float t_up = (clip_points[i] - points[j]).cross(clip_edge);
                float u_up = (clip_points[i] - points[j]).cross(edge);
                
                float div_down = -edge.cross(clip_edge);
                
                float t = t_up / div_down;
                float u = u_up / div_down;
                //need to consider inside case
                if (u >= 0 && u <= 1) {
                    //need to replace one of the point
                    //need a new class
                }
                
            }
        }
    }
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 0.0f, 0.0f, specular.a);
    for (int j = 0; j < clip_points.size()-1; j += 1){
        glVertex2f(clip_points[j].x, clip_points[j].y);
    }
    glEnd();
}