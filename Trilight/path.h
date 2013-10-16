//
//  tilePath.h
//  Trilight
//
//  Created by Yue on 10/15/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__tilePath__
#define __Trilight__tilePath__


#include <vector>
#include "algebra.h"

//double linked list
class Path{
    
    Point start;
    Point end;
    Vector vec; //or float angel
    
public:
    Path(Point start, Point end);
    Path * prev;
    Path * next;
    ~Path();
    void render(); //use bfs or dfs to render the path
    bool is_point_on_path(Point p );
    Vector get_direction_on(Point p, Vector dir);
    Vector get_vec();
    Point get_start();
    Point get_end();
};


#endif /* defined(__Trilight__tilePath__) */
