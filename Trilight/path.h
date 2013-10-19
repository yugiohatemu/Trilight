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
#include "constant.h"
//double linked list
#include "edge.h"
#include "SDL/SDL_opengl.h"

class Path{
protected:
    Point start;
    Point end;
    Vector vec; //or float angel
    float angel;
    void set_angel();
public:
    Path(Point start, Point end);
    Path * prev;
    Path * next;
    ~Path();
    virtual void render(); //use bfs or dfs to render the path
    virtual bool is_point_within_path(Point p );
    bool is_orentation_within(ORIENTATION A, ORIENTATION B);
    Vector get_vec();
    Point get_start();
    Point get_end();
    float get_angel();
    ORIENTATION to_next;
    ORIENTATION to_prev;
    ORIENTATION get_orientation(Vector vec);
    Edge get_edge();
};

Vector adjust_vector(ORIENTATION orien, Vector vec);

#endif /* defined(__Trilight__tilePath__) */
