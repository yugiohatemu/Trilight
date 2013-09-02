//
//  point.h
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__point__
#define __Trilight__point__

struct Point{
    float x;
	float y;
	Point();
	Point(float xx, float yy);
    Point (Point const &p);
    //overwrite operator for convenience
    
//    Point operator+(Point p);
//    Point operator-(Point p);
    Point operator*(float s);
    Point operator/(float s);
    Point& operator= (const Point &p);
    
    void normalize();
    float dot(Point p);
    float cross(Point p);
};

#endif /* defined(__Trilight__point__) */
