//
//  algebra.h
//  Trilight
//
//  Created by Yue on 9/3/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__algebra__
#define __Trilight__algebra__

#include "point.h"
#include "vector.h"

Vector operator* (float t, const Vector & a);
Vector operator+ (const Point &a, const Point &b);
Vector operator- (const Point &a, const Point &b);
Point operator+ (const Vector &a, const Point &b);
Point operator+ (const Point &b, const Vector &a);

#endif /* defined(__Trilight__algebra__) */
