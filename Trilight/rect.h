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
#include "SDL/SDL.h"
class Rect {
	
public:
    int x,y,w,h;
	Rect() ;
	Rect(int dx, int dy, int dwidth, int dheight);
    Rect(SDL_Rect rect);
    Rect & operator=(Rect & r);
    
	void render() ;
    std::vector<Edge> getEdges();
    std::vector<Point> getPoints();
    std::vector<Vector> getNormals();
    bool is_inside(Point p);
   
    Color color;
};

#endif /* defined(__Trilight__Rect__) */
