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
    Point operator+(Point p);
    Point operator-(Point p);
    Point operator*(float s);
    Point operator/(float s);
    Point& operator= (const Point &p);
    void normalize();
    float dot(Point p);
    
};


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
