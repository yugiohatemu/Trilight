//
//  vector.h
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__vector__
#define __Trilight__vector__

//used for lighting calculation
#include "point.h"

//need to change vector definition
//this one is wrong
struct Vector{
    //origin + t * dir
    Point origin;
    Point dir;
    
    Vector();
    Vector(Point d);
    Vector(Point o, Point d);
    Vector(float ax, float ay, float bx, float by);
    
    float operator*(Vector vec);
    Point get_point();
};

Vector operator+ (const Point &a, const Point &b);
Vector operator- (const Point &a, const Point &b);
bool is_vector_parallel(Vector a, Vector b);

#endif /* defined(__Trilight__vector__) */
