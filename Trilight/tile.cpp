//
//  tile.cpp
//  Trilight
//
//  Created by Yue on 10/14/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "tile.h"
#include "texture.h"

Tile::Tile(T_Rect clip):Sprite(){
//    up = down = right = left = NULL;
    box.w = 48;
    box.h = 48;
    angel = 0;
    this->clip = clip;
}

Tile::~Tile(){
    
}

void Tile::set_gravity(Vector g){
    gravity = g;
}

void Tile::set_angel(float a){
    angel = a;
}

float Tile::get_angel(){
    return angel;
}


Vector Tile::get_gravity(){
    return gravity;
}

void Tile::render(){
    glPushMatrix();
    
    GLuint texture_ID = Texture::Instance().get_texture(Texture::TILE);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glBegin(GL_QUADS);
    glTexCoord2f(clip.x, clip.y); glVertex2f(box.x, box.y);
    glTexCoord2f(clip.x, clip.y + clip.h); glVertex2f(box.x, box.y+ box.h);
    glTexCoord2f(clip.x + clip.w, clip.y + clip.h);glVertex2f(box.x + box.w, box.y + box.h);
    glTexCoord2f(clip.x + clip.w, clip.y);glVertex2f(box.x + box.w, box.y);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

void Tile::update(SDL_Event event){
    
}

void Tile::set_clip(){
    
}