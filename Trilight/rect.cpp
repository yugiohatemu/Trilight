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
    center.x = (dx + dwidth) / 2;
    center.y = (dy + dheight) / 2;
}

bool Rect::is_block(){
    return block;
}

void Rect::set_block(bool b){
    block = b;
}

void Rect::set_center(Point pos){
    set_center(pos.x,pos.y);
}

void Rect::set_center(int x, int y){
    center.x = x;
    center.y = y;
    position.x = center.x - size.x/2;
    position.y = center.y - size.y/2;
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
    glColor4f(color.r,color.g,color.b,color.a );
    glVertex2f(position.x, position.y);
    glVertex2f(position.x, position.y + size.y);
    glVertex2f(position.x + size.x, position.y + size.y);
    glVertex2f(position.x + size.x, position.y);
    
    glEnd();
}

std::vector<Edge> Rect::getEdges() {
    //Define edges
    Edge top(position.x, position.y, position.x + size.x, position.y);
    Edge bottom(position.x, position.y + size.y, position.x + size.x, position.y + size.y);
    Edge right(position.x + size.x, position.y, position.x + size.x, position.y + size.y);
    Edge left(position.x, position.y, position.x, position.y + size.y);
    
    //Push all elements into a vector
    std::vector<Edge> vec;
    vec.push_back(bottom);
    vec.push_back(left);
    vec.push_back(right);
    vec.push_back(top);
    return vec;
}
//normal facing inside responds to get_edges
std::vector<Vector> Rect::getNormals(){
    std::vector<Vector> vec;
    vec.push_back(Vector(0, -1)); //bottom
    vec.push_back(Vector(1, 0)); //left
    vec.push_back(Vector(-1, 0)); //right
    vec.push_back(Vector(0, 1)); //top
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



//dirty, if on edge or point, still consdiered as inside
bool Rect::is_inside(Point p){
    return p.x >= position.x && p.x <= position.x + size.x && p.y >= position.y && p.y <= position.y + size.y;
}
