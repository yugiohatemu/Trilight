//
//  light.h
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__light__
#define __Trilight__light__


#include "color.h"
#include <vector>
#include "rect.h"
#include "vector.h"
#include "polygon.h"
#include "SDL/SDL.h"

class Light {
    
protected:
    int range;
    float rotate_angle;
    Polygon fan;
  
public:
    Light(int range);
	Point position;
	Color specular;
	float size;
    SDL_Rect box;
    
    std::vector<Point> render_clip(Rect rect);
    void rotate(int x, int y);
    void set_rotate_angel(float r);
    
    virtual void render();
    virtual void update(SDL_Event event);
    
};

#endif /* defined(__Trilight__light__) */
