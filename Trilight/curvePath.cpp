//
//  curvePath.cpp
//  Trilight
//
//  Created by Yue on 10/19/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "curvePath.h"

//Reference:Beizier Curve and Surface by Jesper Tveit

CurvePath::CurvePath(Point start, Point end, Point control):Path(start,end){
   
    //define strip based on distance, larger line segment needs more strip
    strip = 5;
    
    float a = 1.0f;
    float b = 0.0f;
    
    //calculate beizier curve by ourselves and store it
    for (int i = 0; i <= strip; i++){
        float a_sq = a * a;
        float b_sq = b * b;
        float px = start.x * a_sq + control.x * 2 * a * b + end.x * b_sq;
        float py = start.x * a_sq + control.x * 2 * a * b + end.x * b_sq;
        
        curve_point.push_back(Point (px, py));
        //Z(a) = Az·a² + Bz·2·a·b + Cz·b²
        //we do not need to calculate z since we are guaranteed on 2 dimesnsion
        
        a -= 1/(float)strip;
        b = 1.0 - a;
    }

    //TODO:need to redefine orientation based on control point
    
}

CurvePath::~CurvePath(){
    
}

//render a curve based on angel?
void CurvePath::render(){
    
    glBegin(GL_LINE_STRIP);
    glColor3f(255, 255, 0);
    for (int i = 0; i < curve_point.size(); i++) glVertex2f(curve_point[i].x, curve_point[i].y);
    glEnd();
}

bool CurvePath::is_point_within_path(Point p ){
    //check for every line segment, that is easier
    
    return false;
}