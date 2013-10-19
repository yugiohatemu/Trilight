//
//  curvePath.h
//  Trilight
//
//  Created by Yue on 10/19/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__curvePath__
#define __Trilight__curvePath__

#include "path.h"

class CurvePath:public Path{
    float start_angel;
    float end_angel;
    Point control;
    unsigned int strip;
    std::vector<Point> curve_point;
public:
    CurvePath(Point start, Point end, Point control);
    ~CurvePath();
    void render();
    bool is_point_within_path(Point p );
};

#endif /* defined(__Trilight__curvePath__) */
