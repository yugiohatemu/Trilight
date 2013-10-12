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

class Scene{
     //a list of light
    std::vector<Rect> rectangles;
    Sprite * eyeball;
    Light * light;
public:
    Scene();
    ~Scene();
    void render();
    void update(SDL_Event event);
    
};

#endif /* defined(__Trilight__scene__) */
