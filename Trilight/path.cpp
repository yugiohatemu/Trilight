//
//  tilePath.cpp
//  Trilight
//
//  Created by Yue on 10/15/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "path.h"


Path::Path(){
    prev = next = NULL;
}

Path::Path(Path * prev, Path * next){
    this->next = next;
    this->prev = prev;
}

Path::~Path(){
    
}

void Path::render(){
    //use either bfs or dfs to traverse all the tiles
    //normally we start with the tile on left top
    //how to read a tile then?
}