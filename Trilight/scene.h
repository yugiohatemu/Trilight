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

//Singelton for easy acess globally
//Since there can be only one level on a screen at a time

class Scene{
     
    Scene();
    Scene(Scene const &);
    Scene& operator= (Scene const &);
    
    std::vector<Rect> rectangles;
    Sprite * eyeball;
    Light * light;
public:
    static Scene& Instance();
   
    void render();
    void update(SDL_Event event);
    void create_scene();
    void clear_scene();
};

#endif /* defined(__Trilight__scene__) */
