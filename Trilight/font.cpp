//
//  font.cpp
//  Trilight
//
//  Created by Yue on 10/22/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "font.h"
#include "texture.h"
#include "scene.h"
#include "rect.h"
#include "utility.h"
Font::Font():Sprite(){
    set_clip();
}

Font::~Font(){
    texts.clear();
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

void Font::make_sentence(std::string s, SDL_Rect box){
    for (int i = 0; i < s.size(); i++){
        
        Char ch;
        Rect text_box(box);
        text_box.x = box.x + i * box.w;
        
        ch.box = text_box;
        ch.frame = toupper(s[i]) - 'A';
        
        texts.push_back(ch);

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
    
    for (int i = 0; i < texts.size(); i++) {
        
        Rect rec = texts[i].box;
        T_Rect text_clip = clips[texts[i].frame];
        
        std::vector<Point> clip_point = Scene::Instance().get_clip_point(rec);
        std::vector<Point> texture_clip;
        
        if (!clip_point.empty()) {
            Point top_left(texts[i].box.x, texts[i].box.y);
            
            float ratio_w = rec.w / text_clip.w;
            float ratio_h = rec.h / text_clip.h;
            
            //map the clip_point to texture point
            for (Point & p  : clip_point) {
                Point cp(p);
                cp.x = (p.x - top_left.x)/ratio_w + text_clip.x;
                cp.y = (p.y - top_left.y)/ratio_h + text_clip.y;
                texture_clip.push_back(cp);
            }
            
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1, 1, 0);
            for (int j = 0; j < clip_point.size();j++) {
                glTexCoord2f(texture_clip[j].x, texture_clip[j].y);
                glVertex2f(clip_point[j].x, clip_point[j].y);
            }
            glEnd();
        }
        
    }
    
    //unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
}

void Font::update(SDL_Event event){
    
}