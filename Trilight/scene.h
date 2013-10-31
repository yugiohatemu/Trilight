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
    
    std::vector<Light *> scene_light;
    
    Sprite * eyeball;
    Sprite * text;
    TileMap * tiles;
    Path * path;
    
public:
    static Scene& Instance();
   
    void render();
    void update(SDL_Event event);
    void create_scene();
    void clear_scene();
    
    //dynamic
    std::vector<Edge>get_edge_list();
    
    //movement
    Vector get_next_direction(Vector dir, Point anchor);
    float get_current_angel();
    
    //clipping
    std::vector<Point>get_clip_point(Rect rect);
    
    //light control
    const std::vector<Light *>get_scene_light();
    void add_light_to_scene(Light * l);
    void remove_light_from_scene(Light * l);
    
    
};

#endif /* defined(__Trilight__scene__) */
