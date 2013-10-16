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

class Path{
    
    Point start;
    Point end;
    Vector gravity; //or float angel
    
public:
    Path();
    Path(Path * prev, Path * next);
    Path * prev;
    Path * next;
    ~Path();
    void render(); //use bfs or dfs to render the path
};


#endif /* defined(__Trilight__tilePath__) */
