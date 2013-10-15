//
//  tileFactory.h
//  Trilight
//
//  Created by Yue on 10/14/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__tileFactory__
#define __Trilight__tileFactory__

#include "tile.h"
#include <vector>

//factory method for creating tiles

class TileMap{
    std::vector<Tile **> tileMap;
    Tile* createTile(int tileType);
    int width, height;

public:
    enum{
        EMPTY,
        FLAT_T, FLAT_R,FLAT_B,FLAT_L,
        CO_WN,CO_EN,CO_ES,CO_WE,
        CI_WN,CI_EN,CI_ES,CI_WE,
        SLOPE_WN,SLOPE_EN,SLOPE_ES,SLOPE_WE,
        TOTL_TYPE
    } TileType;
    
    TileMap();
    ~TileMap();
    void render();
    void update();
//    std::vector<Tile*> getTilesOn(int x, int y);
};

#endif /* defined(__Trilight__tileFactory__) */
