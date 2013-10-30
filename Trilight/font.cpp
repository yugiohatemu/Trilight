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
Font::Font(std::string s):Sprite(){
    set_clip();
    SDL_Rect box;
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
    //std::vector<Edge> map = Scene::Instance().get_clip_edge(<#std::vector<Edge> hidden#>, <#std::vector<Vector> normal_inside#>)
    //or we can just make a rect, easy peacy
    return;
    
    Rect r;
    std::vector<Point> clip_point = Scene::Instance().get_clip_edge(r);
    std::vector<Point> texture_clip;
    
    
    if (!clip_point.empty()) {
        Point top_left;
        float ratio_w = r.w / clips[frame].w;
        float ratio_h = r.h / clips[frame].h;
        for (Point & p  : clip_point) {
            p.x = (p.x - top_left.x)/ratio_w + clips[frame].x;
            p.y = (p.y - top_left.y)/ratio_h + clips[frame].y;
            texture_clip.push_back(p);
        }
    }
    
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < clip_point.size();i++) {
        glTexCoord2d(texture_clip[i].x, texture_clip[i].y);
        glVertex2d(clip_point[i].x, clip_point[i].y);
    }
    
    glEnd();
    
    //roughly like this, like need to fix some class hiearchy
    ///////////////////////////////////
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