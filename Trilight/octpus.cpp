//
//  octpus.cpp
//  Trilight
//
//  Created by Yue on 10/12/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "octpus.h"
#include "SDL/SDL_opengl.h"
#include "texture.h"
#include "utility.h"
#include "scene.h"

Octpus::Octpus(int x , int y , int w , int h ):Sprite(x,y,w,h){
    set_clip();
    torch = new Light(45);
    torch->position.x = x + w/2;
    torch->position.y = y + w/2;
    torch->specular.setRGBA(0xFFFF0066);
    torch->size = 300.0f;
    
//    dir.x = 8;
//    dir.y = 0;
//    
//    angel = 270;
    
    top_left.x = bot_left.x = x;
    top_left.y = top_right.y = y;
    top_right.x = bot_right.x = x + w;
    bot_left.y = bot_right.y = y + h;
    
    anchor.x = 60;
    anchor.y = 300;
    //defined as bot mid
}

Octpus::~Octpus(){
    delete torch;
}

void Octpus::set_clip(){
    clips[HEAD_0].x = 0.0f;
    clips[HEAD_0].y = 0.0f;
    clips[HEAD_0].w = 0.5f;
    clips[HEAD_0].h = 1.0f;
    
    clips[HEAD_1].x = 0.5f;
    clips[HEAD_1].y = 0.0f;
    clips[HEAD_1].w = 0.5f;
    clips[HEAD_1].h = 0.5f;
    
    clips[HEAD_2].x = 0.5f;
    clips[HEAD_2].y = 0.5f;
    clips[HEAD_2].w = 0.5f;
    clips[HEAD_2].h = 0.5f;

}

void Octpus::render(){
    glPushMatrix();
    
    GLuint texture_ID = Texture::Instance().get_texture(Texture::NPC);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //notice that texture coordinate is not following th order
    glLoadIdentity();
    //rotate around center, maybe used to implement a utility latter
//    glTranslatef(+(box.x+box.w/2),+(box.y+box.h/4) , 0);
//    glRotatef(angel-270,0, 0, 1);
//    glTranslatef(-(box.x+box.w/2),-(box.y+box.h/4) , 0);
    
    glBegin(GL_QUADS);
    glTexCoord2f(clips[frame].x, clips[frame].y); glVertex2f(top_left.x, top_left.y);
    glTexCoord2f(clips[frame].x, clips[frame].y + clips[frame].h); glVertex2f(bot_left.x, bot_left.y);
    glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y+ clips[frame].h); glVertex2f(bot_right.x, bot_right.y);
    glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y); glVertex2f(top_right.x,top_right.y);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
//    std::vector<Rect> rects = Scene::Instance().get_rect();
//    std::vector<Rect> hid_rect = Scene::Instance().get_hidden();
//    
//    torch->render(rects);
//    torch->render_clip(hid_rect[0]);
    
}

void Octpus::update(SDL_Event event){
    
    if (event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_w) pressed[0] = true;
        if(event.key.keysym.sym == SDLK_a) pressed[1] = true;
        if(event.key.keysym.sym == SDLK_s) pressed[2] = true;
        if(event.key.keysym.sym == SDLK_d) pressed[3] = true;
      
    }else if(event.type == SDL_KEYUP){
        if (event.key.keysym.sym == SDLK_w) pressed[0] = false;
        if (event.key.keysym.sym == SDLK_a) pressed[1] = false;
        if (event.key.keysym.sym == SDLK_s) pressed[2] = false;
        if (event.key.keysym.sym == SDLK_d) pressed[3] = false;
        
    }
    Vector cur_dir;
    int speed = 8;
    if (pressed[0]) cur_dir.y = -speed;
    if (pressed[1]) cur_dir.x = -speed;
    if (pressed[2]) cur_dir.y = speed;
    if (pressed[3]) cur_dir.x = speed;
    
    //so it is worth calculating
    if (cur_dir != Vector(0, 0)) {
        Vector next_dir = Scene::Instance().get_next_direction(cur_dir, anchor);
        //update all the points
        anchor = anchor + next_dir;
        top_left = top_left + next_dir;
        top_right = top_right + next_dir;
        bot_left = bot_left + next_dir;
        bot_right = bot_right + next_dir;
    }
    
    
    
    //now, we just need to define anchor
    //anchor must be on the point
    
    if (box.x < 0) box.x = 0;
    if (box.x > 640) box.x = 640;
    
    
//    int x = 0, y = 0;
//    SDL_GetMouseState( &x, &y );
//    if (x < 0) x = 0;
//    if (y < 0) y = 0;
    
//    torch->update(event);
//    torch->rotate(x, y);
    
}


