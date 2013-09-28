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
    fan.clear_point();
    fan.add_point(position);
    fan.add_point(position + Vector(size * cos((- range/2 + rotate_angle) * 3.14159 / 180), size * sin((- range/2 + rotate_angle) * 3.14159 / 180)));
    fan.add_point(position + Vector(size * cos((range/2 + rotate_angle) * 3.14159 / 180), size * sin((range/2 + rotate_angle) * 3.14159 / 180)));
    fan.add_point(position);
}

//sutherland - holander algorithm, check wikipedia page for pusedo implementation

void Light::render_clip(Rect object){
    //get the fan, reuse it from render
    std::vector<Edge> clip_edges = fan.getEdges();
    std::vector<Edge> rect_edges = object.getEdges();
    std::vector<Vector> noraml_inside = object.getNormals();
    
    for (int i = 0; i < rect_edges.size(); i++) {
        
        for (int j = 0; j < clip_edges.size(); j++) {
            float wec_s = (clip_edges[j].get_start() - rect_edges[i].get_start()).cross(noraml_inside[i]);
            float wec_e = (clip_edges[j].get_end() - rect_edges[i].get_start()).cross(noraml_inside[i]);
            if (wec_s < 0 && wec_s < 0) {
                std::vector<Edge>::iterator it = clip_edges.begin() + j;
                clip_edges.erase(it);
            }else if(wec_s >= 0 && wec_e >= 0){
                float t = wec_s / (wec_s - wec_e);
                Point intersect = clip_edges[i].get_start() + t * clip_edges[i].get_vector();
                if (wec_s < 0) clip_edges[i].set_start(intersect);
                else clip_edges[i].set_end(intersect);
            }
        }
    }
    
    //now we need to recreat a new polygon, summarize the list
    std::vector<Point> clip_points;
    for (int i = 0; i < clip_edges.size(); i++) {
        clip_points.push_back(clip_edges[i].get_start());
        clip_points.push_back(clip_edges[i].get_end());
    }
    
    glBegin(GL_LINE_LOOP);
    glColor4f(1.0f, 0.0f, 0.0f, specular.a);
    
    for (int i = 0; i < clip_points.size(); i++) {
        glVertex2f(clip_points[i].x, clip_points[i].y);
    }
    
    glEnd();
}