//
//  tile.h
//  Trilight
//
//  Created by Yue on 10/14/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__tile__
#define __Trilight__tile__

//a single tile, defined by 32*32, contains vectors such as normal
//related clip should be controlled by tile factory


#include "vector.h"
#include "sprite.h"

class Tile:public Sprite{
    T_Rect clip;
    Vector gravity;
    float angel;
    void set_clip();
public:
    Tile(T_Rect clip);
    ~Tile();
    
    void render();
    void update(SDL_Event event);
    void set_gravity(Vector g);
    void set_angel(float a);
    float get_angel();
    Vector get_gravity();
    
};

#endif /* defined(__Trilight__tile__) */
