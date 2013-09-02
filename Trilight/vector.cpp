//
//  vector.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "vector.h"

Vector::Vector(){
    
}

Vector::Vector(Point d){
    dir = d;
}

Vector::Vector(Point o, Point d){
    origin = o;
    dir = d;
    //Point(d.x - o.x , d.y - o.y);
}

Vector::Vector(float ax, float ay, float bx, float by):origin(ax,ay), dir(bx - ax,by - ay){
    
}

Point Vector::get_point(){
    return Point(origin.x+dir.x, origin.y + dir.y);
}

float Vector::operator*(Vector vec){
    return get_point().dot(vec.get_point());
}

////////////////////////////////////////////////////////////////////////

Vector operator+ (const Point &a, const Point &b){
    return Vector(a,b);
}

Vector operator- (const Point &a, const Point &b){
    Point c(-b.x,-b.y);
    return Vector(a,c);
}

//get normalize direction
bool is_vector_parallel(Vector a, Vector b){
//    Point an = a.dir;
//    Point bn = b.dir;
//    an.normalize();
//    bn.normalize();
    
    return (a.dir.cross(b.dir) == 0);
}


