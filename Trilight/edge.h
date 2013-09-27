//
//  edge.h
//  Trilight
//
//  Created by Yue on 9/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__edge__
#define __Trilight__edge__

#include "point.h"
#include "vector.h"

class Edge{
    Point start;
    Point end;
    Vector vec;
public:
    Edge();
    Edge(Point start, Point end);
    Edge(float sx, float sy, float ex, float ey);
    Edge(Edge const & e);
    void set_start(Point s);
    void set_end(Point e);
    Point get_start();
    Point get_end();
    Vector get_vector();
    
    //get intersection point on the line segment
};

#endif /* defined(__Trilight__edge__) */
