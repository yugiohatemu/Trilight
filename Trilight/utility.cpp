//
//  utility.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "utility.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////////////////////////

Line::Line(float startx, float starty, float endx, float endy) {
    x = startx;
    y = starty;
    ex = endx;
    ey = endy;
    //
    //        if (startx == endx){
    //            a = startx;
    //            b = 0;
    //        }else if(starty == endy){
    //            a = 0;
    //            b = starty;
    //        }else {
    //            float slope =  (endy - starty) / (endx - startx);
    //            float m = starty - startx * slope;
    //
    //            b = 1 / m;
    //            a = - slope * b;
    //        }
}

Line::Line() {
    x = y = ex = ey = 0;
    a = b = 0;
}

bool hitTestBoundf(Point min, Point max, Point point) {
	if(point.x >= min.x) {
		if(point.y >= min.y) {
			if(point.x <= max.x) {
				if(point.y <= max.y) {
					return true;
				}
			}
		}
	}
	return false;
}

float disOfPoints(Point A, Point B){
    float dx = A.x - B.x;
    float dy = A.y - B.y;
    return sqrtf(dx * dx + dy * dy);
}

float get_scale(Point s, Point e, Point vec){
    if (vec.x != 0) {
        return (e.x - s.x)/vec.x;
    }else if(vec.y != 0){
        return (e.y - s.y)/vec.y;
    }else{
        return 0;
    }
}

//should use vectors calculation
//if true, then p will be modified
bool getIntersetPoint(Point & p, Line A , Line B){
    //x + t* vectore
    Point a_base(A.x, A.y);
    Point b_base(B.x, B.y);
    Point a_vect(A.ex - A.x, A.ey - A.y);
    Point b_vect(B.ex - B.x, B.ey - B.y);
    
    float n = a_vect.dot(b_vect);
    if (n != 0) {
        Point dif = a_base - b_base;
        float t = dif.dot(a_vect)/n;
        float s = dif.dot(b_vect)/n;
        if (t <= 1 && s <= 1 && t >= 0 && s >=0) { //if not within range 1 then must not in line segment
            p.x = t;
            p.y = s;
            return true;
        }
    }
    
    return false;
}