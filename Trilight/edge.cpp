//
//  edge.cpp
//  Trilight
//
//  Created by Yue on 9/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "edge.h"
#include <iostream>
Edge::Edge(){
    
}

Edge::Edge(Point s, Point e){
    start = s;
    end = e;
    vec = end - start;
}

Edge::Edge(float sx, float sy, float ex, float ey){
    start.x = sx;
    start.y = sy;
    end.x = ex;
    end.y = ey;
    vec = end - start;
}

Edge::Edge(Edge const & e){
    start = e.start;
    end = e.end;
    vec = end - start;
}

Edge& Edge::operator= (const Edge &e){
    if (this == &e) {
        return *this;
    }
    //override for array erase
    this->start= e.start;
    this->end = e.end;
    this->vec = e.vec;
    
    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////

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
///////////////////////////////////////////////////////////////////////////////////////////

bool is_edge_connect(Edge p, Edge q){
    if (p.get_start() == q.get_start() || p.get_start() == q.get_end()) return true;
    else if(p.get_end() == q.get_start() || p.get_end() == q.get_start()) return true;
    else return false;
}

bool get_line_intersect(Edge clip, Edge intersect, Point &r){
    float p_t, q_t;
    if (get_vector_intersect(clip, intersect, p_t, q_t)) {
        if (0 <= p_t && p_t <= 1) {
            r = clip.get_start() + p_t * clip.get_vector();
            return true;
        }
    }
    return false;
}

//below are correct
bool get_vector_intersect(Edge p, Edge q, float &p_t, float &q_t){
    //check if parallel
    if (is_vector_parallel(p.get_vector(), q.get_vector())) return false;
    
    //now cross it, return t & s maybe better than r, gives more information?
    float p_up = (q.get_start() - p.get_start()).cross(q.get_vector());
    float q_up = (q.get_start() - p.get_start()).cross(p.get_vector());
    float div_down = p.get_vector().cross(q.get_vector());
    
    p_t = p_up / div_down;
    q_t = q_up / div_down;
    
    return true;
}
