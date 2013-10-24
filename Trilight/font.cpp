//
//  font.cpp
//  Trilight
//
//  Created by Yue on 10/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "font.h"
#include "texture.h"

Font::Font(std::string s):Sprite(){
    set_clip();
    
    for (int i = 0; i < s.size(); i++) {
        texts.push_back(s[i] - 'A');
    }
    
}

Font::~Font(){
   
}

void Font::set_clip(){
    float w = (float)64.0f/512.f;
    float h = (float)96.0f/512.f;
    for (int i = 0; i < TOTAL_CLIPS; i++) {
        clips[i].x = (i%8) * w;
        clips[i].y = (i/8) * h;
        clips[i].w = w;
        clips[i].h = h;
    }
}

void Font::render(){
    glPushMatrix();
    
    //get texture
    GLuint texture_ID = Texture::Instance().get_texture(Texture::FONT);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //start drawing
    glLoadIdentity();
    
    glBegin(GL_QUADS);
    for (int i = 0; i < texts.size(); i++) {
        int frame = texts[i];
        
        glTexCoord2f(clips[frame].x, clips[frame].y); glVertex2f(box.x + i * 32, box.y);
        glTexCoord2f(clips[frame].x, clips[frame].y + clips[frame].h); glVertex2f(box.x+i * 32, box.y + box.h);
        glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y+ clips[frame].h); glVertex2f(box.x + box.w +i * 32, box.y + box.h);
        glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y); glVertex2f(box.x + box.w +i * 32, box.y);
    }
    
    glEnd();
    glPopMatrix();
}

void Font::update(SDL_Event event){
    
}