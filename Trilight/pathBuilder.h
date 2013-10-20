//
//  pathBuilder.h
//  Trilight
//
//  Created by Yue on 10/19/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__pathBuilder__
#define __Trilight__pathBuilder__

#include "path.h"
#include <string>
class PathBuilder{
public:
    PathBuilder();
    ~PathBuilder();
    Path* read_path(std::string filename);
    void render_path(Path * p);
    void delete_path(Path * p);
    //singelton?, not necessary
};

#endif /* defined(__Trilight__pathBuilder__) */
