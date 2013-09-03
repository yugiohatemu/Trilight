//
//  Rect.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "rect.h"
#include "SDL/SDL_opengl.h"

Rect::Rect() {
    
}

Rect::Rect(int dx, int dy, int dwidth, int dheight) {
    position.x = dx;
    position.y = dy;
    size.x = dwidth;
    size.y = dheight;
    block = true;
}

bool Rect::is_block(){
    return block;
}

void Rect::set_block(bool b){
    block = b;
}

void Rect::render() {
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x, position.y + size.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x + size.x, position.y);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor4f(1.0f,1.0f,0,0.5f);
    glVertex2f(position.x, position.y);
    glVertex2f(position.x, position.y + size.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x + size.x, position.y);
    
    glEnd();
}

std::vector<Line> Rect::getEdges() {
    //Define edges
    Line top(position.x, position.y, position.x + size.x, position.y);
    Line bottom(position.x, position.y + size.y, position.x + size.x, position.y + size.y);
    Line right(position.x + size.x, position.y, position.x + size.x, position.y + size.y);
    Line left(position.x, position.y, position.x, position.y + size.y);
    
    //Push all elements into a vector
    std::vector<Line> vec;
    vec.push_back(bottom);
    vec.push_back(left);
    vec.push_back(right);
    vec.push_back(top);
    return vec;
}


std::vector<Point> Rect::getPoints(){
    //counter clock wise order
    std::vector<Point> vec;
    vec.push_back(Point(position.x, position.y));
    vec.push_back(Point(position.x, position.y + size.y));
    vec.push_back(Point(position.x + size.x, position.y + size.y));
    vec.push_back(Point(position.x + size.x, position.y ));
    return vec;
}

//std::vector<Vector> Rect::getVectorEdges(){
//    Vector top(position.x, position.y, position.x + size.x, position.y);
//    Vector bottom(position.x, position.y + size.y, position.x + size.x, position.y + size.y);
//    Vector right(position.x + size.x, position.y, position.x + size.x, position.y + size.y);
//    Vector left(position.x, position.y, position.x, position.y + size.y);
//    
//    std::vector<Vector> vec;
//    vec.push_back(bottom);
//    vec.push_back(left);
//    vec.push_back(right);
//    vec.push_back(top);
//    return vec;
//}

