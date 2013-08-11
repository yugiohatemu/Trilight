//
//  utility.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "utility.h"

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