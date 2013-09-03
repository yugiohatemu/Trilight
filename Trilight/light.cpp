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

void Light::test_render(std::vector<Rect>& objects) {
    //Shoot rays and determine objects
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(specular.r, specular.g, specular.b, specular.a);
    
    glVertex2f(position.x, position.y);
    //divide the light into 361 rays, for each ray, check intersection of rects
    //feels like ray lighting
    

    for(int i = - range/2; i < range/2 ; i++) {
        float angle = (i + rotate_angle) * 3.14159 / 180;
        
        //Some variables for direction and time, 1 unit per second
        float dx = cos(angle);
        float dy = sin(angle);
        float t = size;
        //Check intersection on objects
        for(int j = 0; j < objects.size(); j++) {
            if (objects[j].is_block() == false) {
                continue ;
            }
            //Get all lines which make up the objects structure
            std::vector<Line> lines = objects[j].getEdges();
            for(int edges = 0; edges < lines.size(); edges++) {
                //Check the ray intersects with this line
                Line edge = lines[edges];
                float tempt = size;
                //A * B = c
                //A = [slope 1]
                //B = [x y]
                float ax, ay;
                
                float rise = (edge.ey - edge.y);
                float run = (edge.ex - edge.x);
                //float slope = 0;
                if(rise <= 0.0f) {//Vertical line
                    ay = 1;
                    ax = 0;
                } else if(run <= 0.0f) {//Horozontal line
                    ay = 0;
                    ax = 1;
                } else {  //Slope
                    ax = rise / run;
                    ay = 1;
                }
                
                //Find Y intersect
                //float c = slope * edge.x + 1 * edge.y;
                
                //Find Y intersect
                float yintersect = edge.y * ay  + ax * edge.x;
                
                //Ray(t) = Rorg + tD
                //
                //Intersection on the ray given by
                //t = c - (A * Rorg) / (A * D)
                float adotd = (ax * dx + ay * dy);
                if( fabs( adotd ) <= 0.0f)	//Paralell or never meet
                    continue;
                tempt = (yintersect - (ax * position.x + position.y * ay)) / adotd;
                
                //Now we need to check if this point is within the line
                float pointx = position.x + dx * tempt;
                float pointy = position.y + dy * tempt;
                
                //Do a bounding box check on the points
                Point bmin(edge.x, edge.y);
                Point bmax(edge.ex, edge.ey);
                Point point(pointx, pointy);
                if(hitTestBoundf(bmin, bmax, point)) {
                    if(tempt <= t && tempt > 0.0f) {
                        t = tempt;
                    }
                }
            }
        }
        
        float alphascale = t / size;
        glColor4f(specular.r, specular.g, specular.b, 1.0f-alphascale);	
        glVertex2f(position.x + dx * t, position.y + dy * t);
    }
    glEnd();
    
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
                    float u_up = (position - points[p]).cross(ray);
                    
                    float div_down = ray.cross(edge);
                    
                    float new_t = t_up / div_down;
                    float u = - u_up / div_down;
                    
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
    
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, specular.a);
    std::vector<Point> points = object.getPoints();
    points.push_back(points[0]); //for recursive
    for (int i = 0; i < points.size() - 1; i += 1) {
        Vector edge = points[i + 1] - points[i];
        //we are already given light?
        for (int j = 0; j < clip_points.size()-1; j += 1) {
            Vector clip_edge = clip_points[j + 1] - clip_points[j];
            if (!is_vector_parallel(edge, clip_edge)) {
                float t_up = (points[i] - clip_points[j]).cross(clip_edge);
                float u_up = (clip_points[j] - points[i]).cross(edge);
                
                float div_down = edge.cross(clip_edge);
                
                float t = t_up / div_down;
                float u = - u_up / div_down;
                
                if (0 <= t && t <= 1 && 0 <= u && u <= 1) {
                    Point p = edge * t + points[i];
                    glVertex2f(p.x, p.y);
                }
            }
        }
    }
    
    glEnd();
}