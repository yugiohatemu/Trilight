//
//  sprite.cpp
//  Trilight
//
//  Created by Yue on 10/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "sprite.h"
#include "SDL/SDL_opengl.h"
#include "texture.h"
#include "utility.h"

Sprite::Sprite(int x , int y ){
    box.x = x;
    box.y = y;
    box.w = 32;
    box.h = 32;
    frame = 0;
    set_clip();
    
}

Sprite::~Sprite(){
    
}

void Sprite::set_clip(){
    clips[HEAD_0].x = 0.0f;
    clips[HEAD_0].y = 0.0f;
    
    clips[HEAD_1].x = 0.5f;
    clips[HEAD_1].y = 0.0f;
    
    clips[HEAD_2].x = 0.5f;
    clips[HEAD_2].y = 0.5f;
    
    clips[HEAD_3].x = 0.0f;
    clips[HEAD_3].y = 0.5f;
    
    for (int i = HEAD_0; i < TOTAL_CLIPS; i++) {
        clips[i].w = 0.5f;
        clips[i].h = 0.5f;
    }
}

void Sprite::update(){
//    frame += 1;
//    if (frame == TOTAL_CLIPS) {
//        frame = 0;
//    }
}

void Sprite::render(){
   
    glPushMatrix();
    
    GLuint texture_ID = Texture::Instance()->get_texture();
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glBegin(GL_QUADS);
    glVertex2f(box.x, box.y); glTexCoord2f(clips[frame].x, clips[frame].y);
    glVertex2f(box.x, box.y+ box.h); glTexCoord2f(clips[frame].x, clips[frame].y + clips[frame].y + clips[frame].h);
    glVertex2f(box.x + box.w, box.y + box.h); glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y + clips[frame].h);
    glVertex2f(box.x + box.w, box.y); glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y);
    glEnd();
    
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}