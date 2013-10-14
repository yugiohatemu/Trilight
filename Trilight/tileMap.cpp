//
//  tileFactory.cpp
//  Trilight
//
//  Created by Yue on 10/14/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "TileMap.h"
#include "SDL/SDL_opengl.h"
#include "utility.h"

TileMap::TileMap(){
    int width = 20;
    int height = 10;
   
    for (int i = 0;i < height ;i++) {
        Tile ** line = new Tile * [width];
        for (int j = 0; j < width; j++) {
            line[j] = createTile(rand() % CO_WE);
            line[j]->box.x = j * 32;
            line[j]->box.y = 80 + i * 32;
        }
        tileMap.push_back(line);
    }
    
}

TileMap::~TileMap(){
    int width = 20;
    for (int i = 0; i < tileMap.size(); i++) {
        for (int j = 0; j < width; j++){
            delete tileMap[i][j];
        }
        delete [] tileMap[i];
    }
}


Tile* TileMap::createTile(int tileType){
    float tile_base = .25f;
    
    T_Rect clip;
    clip.w = tile_base;
    clip.h = tile_base;
    
    switch (tileType) {
        case EMPTY:
            clip.x = 2.5 * tile_base; clip.y = 0.5 * tile_base; break;
        case FLAT_T:
            clip.x = 0; clip.y = 0; break;
        case FLAT_R:
            clip.x = tile_base; clip.y = 0; break;
        case FLAT_B:
            clip.x = tile_base; clip.y = tile_base; break;
        case FLAT_L:
            clip.x = 0; clip.y = tile_base; break;
        case CO_WN:
            clip.x = tile_base * 2; clip.y = 0; break;
        case CO_EN:
            clip.x = tile_base * 3; clip.y = 0; break;
        case CO_ES:
            clip.x = tile_base * 3; clip.y = tile_base; break;
        case CO_WE:
            clip.x = tile_base * 2; clip.y = tile_base; break;
            
        default:
            break;
    }
    
    Tile * aTile = new Tile(clip);
    return aTile;
}


void TileMap::render(){
    //TODO: find out the tiles on the viewport range
    //and ask them to render their selves
    int width = 20;
    int height = 10;
    
    glPushMatrix();
    glLoadIdentity();
    
    for (int i = 0;i < height ;i++) {
        for (int j = 0; j < width; j++) {
            tileMap[i][j]->render();
        }
    }
    glPopMatrix();
}

void TileMap::update(){
    
}