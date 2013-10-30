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
    Sprite * text;
    TileMap * tiles;
    Path * path;
    Light * test_light;
public:
    static Scene& Instance();
   
    void render();
    void update(SDL_Event event);
    void create_scene();
    void clear_scene();
    
    std::vector<Edge>get_edge_list();
    std::vector<Point>get_clip_point(Rect rect);
    
    Vector get_next_direction(Vector dir, Point anchor);
    float get_current_angel();
};

#endif /* defined(__Trilight__scene__) */
