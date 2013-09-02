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

Vector::Vector(Point o){
    origin = o;
}

Vector::Vector(Point o, Point d){
    origin = o;
    dir = d;
}

