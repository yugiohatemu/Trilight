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
    to_next = get_orientation(vec);
    to_prev = get_orientation(start-end);
}

Path::~Path(){
    prev = next = NULL;
}

void Path::render(){
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
}

ORIENTATION Path::get_orientation(Vector vec){
    if (vec == Vector()) {
       return ORIGIN;
    }else if (vec.x == 0) {
        if (vec.y > 0) return NORTH;
        else return SOUTH;
    }else if(vec.y == 0){
        if (vec.x > 0) return EAST;
        else return WEST;
    }else{
        if (vec.x > 0 && vec.y > 0) return NORTH_EAST;
        else if (vec.x > 0 && vec.y < 0) return NORTH_WEST;
        else if (vec.x < 0 && vec.y > 0) return SOUTH_EAST;
        else return SOUTH_WEST;
    }
}

bool Path::is_orentation_within(ORIENTATION A, ORIENTATION B){ //ask if A is within B
    if (B== NORTH || B == WEST || B == EAST || B == SOUTH) return A==B;
    else{
        if (B== NORTH_EAST) return A==B || A==NORTH || A == EAST;
        else if(B == NORTH_WEST) return A==B || A==NORTH || A == WEST;
        else if(B == SOUTH_EAST) return A==B || A==SOUTH||A== EAST;
        else return A==B || A==SOUTH||A== WEST; //B == SOUTHWEST
    }
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
    ORIENTATION orien = get_orientation(dir);
    Point anchor = p + dir;
    
    if (is_orentation_within(orien, to_next)) {
        if (!is_point_on_path(anchor)){
            if (next != NULL ) {
                Vector left = anchor - end;
                
                float t = left.get_norm();
                dir = next->get_vec() * t;
                return left + next->get_direction_on(end, dir);
            }else{
                return end-p;
            }
        }
        
    }else if (is_orentation_within(orien, to_prev)){ //we are going to previous
        if (prev != NULL) {
            Vector left = anchor - start;
            float t = left.get_norm();
            dir = prev->get_vec() * t;
            return left + prev->get_direction_on(start, dir);
        }else{
            return start - p;
        }
    }else{ //do not allow moving since not using the right action
        return Vector();
    }
    
    return dir;
}