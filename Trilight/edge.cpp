//
//  edge.cpp
//  Trilight
//
//  Created by Yue on 9/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "edge.h"

Edge::Edge(){
    
}

Edge::Edge(Point start, Point end): start(start), end(end){
    vec = end - start;
}

Edge::Edge(float sx, float sy, float ex, float ey): start(sx, sy), end(ex, ey){
    vec = end - start;
}

Edge::Edge(Edge const & e){
    start = e.start;
    end = e.end;
    vec = end - start;
}

void Edge::set_start(Point s){
    start = s;
    vec = end - start;
}

void Edge::set_end(Point e){
    end = e;
    vec = end - start;
}

Point Edge::get_start(){
    return start;
}

Point Edge::get_end(){
    return end;
}

Vector Edge::get_vector(){
    return vec;
}