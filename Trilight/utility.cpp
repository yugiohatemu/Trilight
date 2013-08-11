//
//  utility.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "utility.h"
#include <math.h>
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