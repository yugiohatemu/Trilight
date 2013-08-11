//
//  utility.h
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__utility__
#define __Trilight__utility__

struct Point {
	float x;
	float y;
	Point() {
		x = y = 0;
	}
	Point(float xx, float yy) {
		x = xx;
		y = yy;
	}
};


struct Line {
	float x;
	float y;
	float ex;
	float ey;
	Line() {
		x = y = ex = ey = 0;
	}
	Line(float startx, float starty, float endx, float endy) {
		x = startx;
		y = starty;
		ex = endx;
		ey = endy;
	}
};

bool hitTestBoundf(Point min, Point max, Point point);
float disOfPoints(Point A, Point B);

#endif /* defined(__Trilight__utility__) */
