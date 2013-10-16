//
//  tilePath.cpp
//  Trilight
//
//  Created by Yue on 10/15/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"
#include "SDL/SDL_opengl.h"

Path::Path(Point s, Point e):start(s),end(e){
    prev = next = NULL;
    vec = end - start;
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
    return vec;
}

Point Path::get_start(){
    return start;
}

Point Path::get_end(){
    return end;
}

Vector Path::get_direction_on(Point p, Vector dir){
    Path * currentPath = this;
    //then cant use recursive?
    //....fine
    Point anchor = p + dir;
    if (!is_point_on_path(anchor)) {
        Vector v1 = anchor - start;
        
        if (vec.cross(v1) == 0) { //using the next
            if (next != NULL ) {
                Vector left = anchor - end;
                
                float t = left.get_norm();
                dir = next->get_vec() * t;
                return left + next->get_direction_on(end, dir);
            }else{
                return end-p;
            }
        }else{
            if (prev != NULL) {
                Vector left = anchor - start;
                float t = left.get_norm();
                dir = prev->get_vec() * t;
                return left + prev->get_direction_on(start, dir);
            }else{
                return start - p;
            }
        }
    }
    
    return dir;
}