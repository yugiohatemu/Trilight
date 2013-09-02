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

struct Vector{
    //origin + t * dir
    Point origin;
    Point dir;
    
    Vector();
    Vector(Point o);
    Vector(Point o, Point d);
    
};


#endif /* defined(__Trilight__vector__) */
