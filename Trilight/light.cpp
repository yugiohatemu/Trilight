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

Light::Light(int range){
    this->range = range;
    rotate_angle = 0;
}

void Light::rotate(int x, int y){
    float dx = x - position.x;
    float dy = y - position.y;
    rotate_angle = atan2f(dy,dx) * 180 / 3.14159;
    
//    std::cout<<rotate_angle<<std::endl;
    //now makes it the center
}

void Light::render(std::vector<Rect>& objects) {
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


void Light::reflect_render(std::vector<Rect> & objects){
    glBegin(GL_POLYGON);
    //wait, let just do two rays
    Line ray1;
    Line ray2;
    for(int j = 0; j < objects.size(); j++) {
        std::vector<Line> lines = objects[j].getEdges();
        std::vector<Point> points1;
        std::vector<Point> points2;
        for(int edges = 0; edges < lines.size(); edges++) {
            //Check the ray intersects with this line
            Line edge = lines[edges];
            Point inter1;
            if(getIntersetPoint(inter1, edge, ray1)){
                points1.push_back(inter1);
                glVertex2f(inter1.x, inter1.y);
            }
            Point inter2;
            if (getIntersetPoint(inter2, edge, ray2)) {
                points2.push_back(inter2);
                glVertex2f(inter2.x, inter2.y);
            }
        }
        //we can tell based on edge
        //how to allocate the points now?
        
    }
    glEnd();
}