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
#include <fstream>


TileMap::TileMap(){
    std::ifstream file("/Users/wei/Desktop/Trilight/Trilight/level.txt");
    
    file >> width;
    file >> height;
    //if valid
    int type = 0;
    for (int i = 0;i < height ;i++) {
        Tile ** line = new Tile * [width];
        for (int j = 0; j < width; j++) {
            file >> type;
            line[j] = createTile(type);
            line[j]->box.x = j * 48;
            line[j]->box.y = 40 + i * 48;
        }
        tileMap.push_back(line);
    }
    
    file.close();
}

TileMap::~TileMap(){
    
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
    
    Vector gravity;
    float angel = 0.0f;
    switch (tileType) {
        case EMPTY:
            clip.x = 0.5 * tile_base; clip.y = 2.5 * tile_base;
            break;
        case FLAT_T:
            clip.x = 0; clip.y = 0;
            gravity.x = 0; gravity.y = -1;
            angel = 90;
            break;
        case FLAT_R:
            clip.x = tile_base; clip.y = 0;
            gravity.x = 1; gravity.y = 0;
             angel = 0;
            break;
        case FLAT_B:
            clip.x = tile_base; clip.y = tile_base;
            gravity.x = 0; gravity.y = 1;
            angel = 270;
            break;
        case FLAT_L:
            clip.x = 0; clip.y = tile_base;
            gravity.x = -1; gravity.y = 0;
            angel = 180;
            break;
        case CO_WN:
            clip.x = tile_base * 2; clip.y = 0;
            gravity.x = -1; gravity.y = -1;
            angel = 135;
            break;
        case CO_EN:
            clip.x = tile_base * 3; clip.y = 0;
            gravity.x = 1; gravity.y = -1;
            angel = 45;
            break;
        case CO_ES:
            clip.x = tile_base * 3; clip.y = tile_base;
            gravity.x = 1; gravity.y = 1;
            angel = 315;
            break;
        case CO_WE:
            clip.x = tile_base * 2; clip.y = tile_base;
            gravity.x = -1; gravity.y = 1;
            angel = 225;
            break;
        case CI_WN:
            clip.x = 0; clip.y = tile_base * 2;
            gravity.x = 1; gravity.y = 1;
            angel = 315;
            break;
        case CI_EN:
            clip.x = tile_base; clip.y = tile_base * 2;
            gravity.x = -1; gravity.y = 1;
            angel = 225;
            break;
        case CI_ES:
            clip.x = tile_base; clip.y = tile_base * 3;
            gravity.x = -1; gravity.y = -1;
            angel = 135;
            break;
        case CI_WE:
            clip.x = 0; clip.y = tile_base * 3;
            gravity.x = 1; gravity.y = -1;
            angel = 45;
            break;
        case SLOPE_WN:
            clip.x = tile_base * 2; clip.y = tile_base * 2; break;
        case SLOPE_EN:
            clip.x = tile_base * 3; clip.y = tile_base * 2; break;
        case SLOPE_ES:
            clip.x = tile_base * 3; clip.y = tile_base * 3; break;
        case SLOPE_WE:
            clip.x = tile_base * 2; clip.y = tile_base * 3; break;
        default:
            break;
    }
    
    Tile * aTile = new Tile(clip);
    aTile->set_gravity(gravity);
    aTile->set_angel(angel);
    return aTile;
}

float TileMap::get_current_angel(SDL_Rect box){
    //get center of the box on the bottom?
    int x = box.x + box.w/2;
    int y = box.y + box.h/2;
    int xpos = x /48; // x - offset
    int ypos = (y - 40)/48; //y - offset
    //x offset and y offset can be calculated
    
    //but based on orienctation, we need to use different bot center?
    //if x pos and y pos being valid
    return tileMap[ypos][xpos]->get_angel();
}

void TileMap::render(){
    //TODO: find out the tiles on the viewport range
    //and ask them to render their selves
    
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