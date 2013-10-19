//
//  tilePath.cpp
//  Trilight
//
//  Created by Yue on 10/15/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"


Path::Path(Point s, Point e):start(s),end(e){
    prev = next = NULL;
    vec = end - start;
    vec = vec.normalize();
    to_next = get_orientation(vec);
    to_prev = get_orientation(start-end);
    set_angel();
}

Path::~Path(){
    prev = next = NULL;
}

Edge Path::get_edge(){
    return Edge(start, end);
}

void Path::set_angel(){
    if (to_next == EAST) angel = 0.0f;
    else if(to_next == NORTH) angel = 270.0f;
    else if(to_next == WEST) angel = 180.0f;
    else if(to_next == SOUTH) angel = 90.0f;
    else{
        //ask vector to give you an angel
        angel = vec.get_angel();
    }
}

float Path::get_angel(){
    return angel;
}

void Path::render(){
    glBegin(GL_LINES);
    glColor3f(255, 0, 0);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
    glEnd();
}

ORIENTATION Path::get_orientation(Vector vec){
    if (vec == Vector()) {
       return ORIGIN;
    }else if (vec.x == 0) {
        if (vec.y > 0) return SOUTH;
        else return NORTH;
    }else if(vec.y == 0){
        if (vec.x > 0) return EAST;
        else return WEST;
    }else{
        if (vec.x > 0 && vec.y > 0) return SOUTH_EAST;
        else if (vec.x > 0 && vec.y < 0) return NORTH_EAST;
        else if (vec.x < 0 && vec.y > 0) return SOUTH_WEST;
        else return NORTH_WEST;
    }
}

bool Path::is_orentation_within(ORIENTATION A, ORIENTATION B){ //ask if A is within B
    if (B== NORTH || B == WEST || B == EAST || B == SOUTH) return A==B;
    else{
        if (B== NORTH_EAST) return A==B || A==NORTH || A == EAST;
        else if(B == NORTH_WEST) return A==B || A==NORTH || A==WEST;
        else if(B == SOUTH_EAST) return A==B || A==SOUTH || A==EAST;
        else if(B == SOUTH_WEST) return A==B || A==SOUTH || A==WEST; //B == SOUTHWEST
    }
    return false;
}

Vector get_vector_based_on_orientation(ORIENTATION orien){ //return normalized
    Vector vec;
    
    switch (orien) {
        case NORTH: vec.y = -1; break;
        case NORTH_EAST: vec.x = SQRT2; vec.y = -SQRT2; break;
        case EAST: vec.x = 1; break;
        case SOUTH_EAST: vec.x = SQRT2; vec.y = SQRT2; break;
        case SOUTH: vec.y = 1; break;
        case SOUTH_WEST: vec.x = -SQRT2; vec.y = SQRT2; break;
        case WEST: vec.x = -1; break;
        case NORTH_WEST: vec.x = -SQRT2; vec.y = -SQRT2; break;
        default:break;
    }
    return vec;
}

Vector adjust_vector(ORIENTATION orien, Vector vec){
    //if vec
    float n = vec.get_norm();
    Vector nex = n * get_vector_based_on_orientation(orien);
    return nex;
}

bool Path::is_point_within_path(Point p ){
//do not check for colinearity, but just within range
    if (p == start || p == end) {
        return true;
    }else{
        if ((start.x <= p.x && p.x <= end.x) || (end.x <= p.x && p.x <= start.x)) {
            if ((start.y <= p.y && p.y <= end.y) || (end.y <= p.y && p.y <= start.y)) {
                return true;
            }
        }
    }
    return false;
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

