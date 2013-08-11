//
//  Rect.h
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__Rect__
#define __Trilight__Rect__

#include "utility.h"
#include <vector>

class Rect {

	Point position;
	Point size;

public:
	Rect() ;
	Rect(int dx, int dy, int dwidth, int dheight);
	void render() ;
    std::vector<Line> getEdges();
};

#endif /* defined(__Trilight__Rect__) */
