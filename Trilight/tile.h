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
    Vector gravity; //for curve, needs a list of vector to abbreviate the info
//    Tile * up;
//    Tile * down;
//    Tile * left;
//    Tile * right;
    void set_clip();
public:
    Tile(T_Rect clip);
    ~Tile();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Trilight__tile__) */
