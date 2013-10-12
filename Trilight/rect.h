//
//  Rect.h
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__Rect__
#define __Trilight__Rect__


#include <vector>
#include "color.h"
#include "algebra.h"
#include "edge.h"

class Rect {

	Point position; //left top corner
    Point center;
	Point size;
    bool block;
public:
    
	Rect() ;
	Rect(int dx, int dy, int dwidth, int dheight);
	void render() ;
    std::vector<Edge> getEdges();
    std::vector<Point> getPoints();
    std::vector<Vector> getNormals();
    bool is_inside(Point p);
    bool is_block();
    void set_block(bool b);
    void set_center(Point pos);
    void set_center(int x, int y);
    Color color;
};

#endif /* defined(__Trilight__Rect__) */
