//
//  vector.cpp
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "vector.h"

Vector::Vector(){
    x = 0.f;
    y = 0.f;
}

Vector::Vector(float xx, float yy){
    x = xx;
    y = yy;
}

Vector::Vector(Vector const & vec){
    x = vec.x;
    y = vec.y;
}

Vector Vector::operator*(float t){
    return Vector(t*x,t*y);
}

Vector Vector::operator+(const Vector &vec){
    return Vector(x + vec.x, y + vec.y);
}

Vector Vector::operator=(const Vector & vec){
    x = vec.x;
    y = vec.y;
    return *this;
}

float Vector::dot(Vector vec){
    return x * vec.x + y * vec.y;
}

float Vector::cross(Vector vec){
    return x * vec.y - y * vec.x;
}

//////////////////////////////////////////
bool is_vector_parallel(Vector a, Vector b){
    return a.cross(b) == 0;
}


