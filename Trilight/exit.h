//
//  exit.h
//  Trilight
//
//  Created by Yue on 11/6/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__exit__
#define __Trilight__exit__

#include "sprite.h"

class Exit:public Sprite{
    void set_clip();
public:
    Exit();
    ~Exit();
    void render();
    void update(SDL_Event event);
};

#endif /* defined(__Trilight__exit__) */
