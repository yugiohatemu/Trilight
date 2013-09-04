//
//  polygon.h
//  Trilight
//
//  Created by Yue on 9/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__polygon__
#define __Trilight__polygon__

#include <vector>
#include "point.h"
#include "color.h"

class Polygon{
    std::vector<Point> points;
public:
    Polygon();
    Polygon(std::vector<Point> points);
    void add_point(Point point);
    Color color;
};

#endif /* defined(__Trilight__polygon__) */
