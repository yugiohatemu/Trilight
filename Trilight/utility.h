//
//  utility.h
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__utility__
#define __Trilight__utility__

#include "point.h"


struct Line {
	float x;
	float y;
	float ex;
	float ey;
    float a, b; //ax + by = 1
	Line() ;
	Line(float startx, float starty, float endx, float endy) ;
};

bool hitTestBoundf(Point min, Point max, Point point);
float disOfPoints(Point A, Point B);
bool getIntersetPoint(Point & p, Line A, Line B);
#endif /* defined(__Trilight__utility__) */
