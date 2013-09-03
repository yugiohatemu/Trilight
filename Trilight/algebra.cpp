//
//  algebra.cpp
//  Trilight
//
//  Created by Yue on 9/3/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "algebra.h"

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