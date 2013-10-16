//
//  scene.h
//  Trilight
//
//  Created by Yue on 10/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__scene__
#define __Trilight__scene__

#include "light.h"
#include <vector>
#include "sprite.h"
#include "SDL/SDL.h"
#include "tileMap.h"
#include "path.h"
//Singelton for easy acess globally
//Since there can be only one level on a screen at a time

class Scene{
     
    Scene();
    Scene(Scene const &);
    Scene& operator= (Scene const &);
    
    std::vector<Rect> rectangles;
    std::vector<Rect> hidden;
    
    Sprite * eyeball;
    TileMap * tiles;
    Path * path;
public:
    static Scene& Instance();
   
    void render();
    void update(SDL_Event event);
    void create_scene();
    void clear_scene();
    
    std::vector<Rect>get_hidden();
    std::vector<Rect>get_rect();
    Vector get_next_direction(Vector dir,float angel,SDL_Rect box);
};

#endif /* defined(__Trilight__scene__) */
