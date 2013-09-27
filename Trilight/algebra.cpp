//
//  algebra.cpp
//  Trilight
//
//  Created by Yue on 9/3/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "algebra.h"

Vector operator* (float t, const Vector & a){
    return t*a;
}

Vector operator+ (const Point &a, const Point &b){
    return Vector(a.x + b.x, a.y + b.y);
}

Vector operator- (const Point &a, const Point &b){
    return Vector(a.x - b.x, a.y - b.y);
}

Point operator+ (const Vector &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y);
}

Point operator+ (const Point &b, const Vector &a){
    return Point(a.x + b.x, a.y + b.y);
}

bool get_line_intersect(Edge p, Edge q, Point &r){
    float p_t, q_t;
    if (get_vector_intersect(p, q, p_t, q_t)) {
        if (0 <= p_t && p_t <= 1 && 0 <=q_t && q_t <= 1) {
            r = p.get_start() + q_t * p.get_vector();
            return true;
        }
    }
    return false;
}

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


