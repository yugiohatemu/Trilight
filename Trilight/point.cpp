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
    x = y = 0;
}

Point::Point(float xx, float yy){
    x = xx;
    y = yy;
}

Point Point::operator+(Point p){
    return Point(x + p.x, y + p.y);
}

Point Point::operator-(Point p){
    return Point(x - p.x, y-p.y);
}

Point Point::operator*(float s){
    return Point(x*s,y*s);
}

Point Point::operator/(float s){
    if ( s == 0) return *this;
    else return Point(x/s,y/s);
}


Point& Point::operator= (const Point &p){
    x = p.x;
    y = p.y;
    return *this;
}

//dot multiply
float Point::dot(Point p){
    return x*p.x + y*p.y;
}

void Point::normalize(){
    float n = sqrt(x*x + y*y);
    if (n != 0 ){
        x = x/n;
        y = y/n;
    }
}

