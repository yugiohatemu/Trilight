//
//  point.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "point.h"
#include <math.h>

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(float xx, float yy){
    x = xx;
    y = yy;
}

Point::Point (Point const &p){
    x = p.x;
    y = p.y;
}

////////////////////////////////////////////////////
Point Point::operator*(float s){
    return Point(x*s,y*s);
}

Point Point::operator/(float s){
    if ( s == 0) return *this;
    else return Point(x/s,y/s);
}

Point& Point::operator= (const Point &p){
    if (this == &p) {
        return *this;
    }
    x = p.x;
    y = p.y;
    return *this;
}

bool Point::operator== (const Point &p){
    return x == p.x && y == p.y;
}

bool Point::operator!= (const Point &p){
    return x != p.x || y != p.y;
}

std::ostream& operator<< (std::ostream& stream, const Point& p){
    stream<<"[POT] ("<<p.x<<","<<p.y<<")";
    return stream;
}

////////////////////////////////////////////////////
//dot multiply
float Point::dot(Point p){
    return x*p.x + y*p.y;
}

float Point::cross(Point p){
    return x*p.y - y * p.x;
}

void Point::normalize(){
    float n = sqrt(x*x + y*y);
    if (n != 0 ){
        x = x/n;
        y = y/n;
    }
}

