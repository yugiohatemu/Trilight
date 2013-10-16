//
//  tilePath.cpp
//  Trilight
//
//  Created by Yue on 10/15/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"
#include "SDL/SDL_opengl.h"
#include <math.h>

Path::Path(Point s, Point e, Vector g):start(s),end(e),gravity(g){
    prev = next = NULL;
}

Path::~Path(){
    prev = next = NULL;
}

void Path::render(){
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
}

bool Path::is_point_on_path(Point p ){

    if (p == start || p == end) {
        return true;
    }else{
        Vector v1 = p-start;
        Vector v2 = end - p;
        if (v1.cross(v2) == 0) {
            return true;
        }else{
            return false;
        }
    }
}

Vector Path::get_vec(){
    return end - start;
}

Vector Path::get_point_on(Point p, Vector dir){
    //return start or end
    Point anchor = p + dir;
    
    Vector vec = end - start;
    if (!is_point_on_path(anchor)) {
        Vector v1 = anchor - start;
        
        if (vec.cross(v1) == 0) { //using the next
            if (next != NULL ) {
                Vector left = anchor - end;
                //getting the normal of the next one
                //get the distance, so we know how many normal we need to move
                float t = sqrtf(left.x * left.x + left.y * left.y);
                dir = next->get_vec() * t;
                return next->get_point_on(end, dir);
            }else{
                return end-p;
            }
        }else{
            if (prev != NULL) {
                Vector left = anchor - start;
                float t = sqrtf(left.x * left.x + left.y * left.y);
                dir = prev->get_vec() * t;
                return prev->get_point_on(start, dir);
            }else{
                return start - p;
            }
        }
    }
    
    return dir;
}