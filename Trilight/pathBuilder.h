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

Path* read_path(std::string filename);
void render_path(Path * p);
void delete_path(Path * p);
std::vector<Edge> get_edge_from_path(Path * p);

#endif /* defined(__Trilight__pathBuilder__) */
