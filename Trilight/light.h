//
//  light.h
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__light__
#define __Trilight__light__

#include "utility.h"
#include "color.h"
#include <vector>
#include "rect.h"

class Light {
public:
	Point position;
	Color specular;
	float size;
    void render(std::vector<Rect>& objects);
};

#endif /* defined(__Trilight__light__) */
