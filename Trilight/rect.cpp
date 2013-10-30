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
    x = dx;
    y = dy;
    w = dwidth;
    h = dheight;
}

Rect::Rect(SDL_Rect rect){
    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;
}

void Rect::render() {
    glPushMatrix();
    
    glBegin(GL_QUADS);
    glColor4f(color.r,color.g,color.b,color.a );
    glVertex2f(x, y);
    glVertex2f(x, y + h);
    glVertex2f(x + w, y + h);
    glVertex2f(x + w, y);
    
    glEnd();
    
    glPopMatrix();
}

std::vector<Edge> Rect::getEdges() {
    //Define edges
    Edge top(x, y , x + w, y);
    Edge bottom(x, y + h, x + w, y + h);
    Edge right(x + w, y, x + w, y + h);
    Edge left(x, y, x, y + h);
    
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
    vec.push_back(Point(x, y));
    vec.push_back(Point(x, y + h));
    vec.push_back(Point(x + w, y + h));
    vec.push_back(Point(x + w, y));
    return vec;
}



//dirty, if on edge or point, still consdiered as inside
bool Rect::is_inside(Point p){
    return p.x >= x && p.x <= x + w && p.y >= y && p.y <= y + h;
}
