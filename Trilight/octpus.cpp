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
    
    top_left.x = bot_left.x = x;
    top_left.y = top_right.y = y;
    top_right.x = bot_right.x = x + w;
    bot_left.y = bot_right.y = y + h;
    
    anchor.x = (bot_left.x + bot_right.x)/2;
    anchor.y = (bot_left.y + bot_right.y)/2;
    
    angel = 0;
    stretch = false;
}

Octpus::~Octpus(){
    delete torch;
}

void Octpus::set_clip(){
    clips[NORMAL].x = 0.0f;
    clips[NORMAL].y = 0.0f;
    clips[NORMAL].w = 0.25f;
    clips[NORMAL].h = 0.5f;
    
    clips[STRETCH].x = 0.25f;
    clips[STRETCH].y = 0.0f;
    clips[STRETCH].w = 0.25f;
    clips[STRETCH].h = 0.875f;
    
}

void Octpus::render(){
    glPushMatrix();
    
    GLuint texture_ID = Texture::Instance().get_texture(Texture::NPC);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    //notice that texture coordinate is not following th order
    glLoadIdentity();
    //rotate around center, maybe used to implement a utility latter
    glTranslatef(anchor.x, anchor.y, 0);
    glRotatef(angel,0, 0, 1);
    glTranslatef(-anchor.x, -anchor.y, 0);
    
    glBegin(GL_QUADS);
    glTexCoord2f(clips[frame].x, clips[frame].y); glVertex2f(top_left.x, top_left.y);
    glTexCoord2f(clips[frame].x, clips[frame].y + clips[frame].h); glVertex2f(bot_left.x, bot_left.y);
    glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y+ clips[frame].h); glVertex2f(bot_right.x, bot_right.y);
    glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y); glVertex2f(top_right.x,top_right.y);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    
//    std::vector<Rect> hid_rect = Scene::Instance().get_hidden();
//    
    torch->render();
//    torch->render_clip(hid_rect[0]);
    
}

void Octpus::update(SDL_Event event){
    
    if (event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_w) pressed[0] = true;
        if(event.key.keysym.sym == SDLK_a) pressed[1] = true;
        if(event.key.keysym.sym == SDLK_s) pressed[2] = true;
        if(event.key.keysym.sym == SDLK_d) pressed[3] = true;
        if(event.key.keysym.sym == SDLK_SPACE) pressed[4] = true;
    }else if(event.type == SDL_KEYUP){
        if (event.key.keysym.sym == SDLK_w) pressed[0] = false;
        if (event.key.keysym.sym == SDLK_a) pressed[1] = false;
        if (event.key.keysym.sym == SDLK_s) pressed[2] = false;
        if (event.key.keysym.sym == SDLK_d) pressed[3] = false;
    }
    
    //on allow to move when no stretching
    //if stretch, change a hitbox
    if (pressed[4]) { //if press stretch
        stretch = !stretch;
        if (stretch) {
            frame = STRETCH;
            top_right.y -= 48;
            top_left.y -= 48;
        }else{
            frame = NORMAL;
            top_right.y += 48;
            top_left.y += 48;
        }
    }
    
    if (!stretch) {
        
        Vector cur_dir;
        int speed = 8;
        
        if (pressed[0]) cur_dir.y = -1;
        if (pressed[1]) cur_dir.x = -1;
        if (pressed[2]) cur_dir.y = 1;
        if (pressed[3]) cur_dir.x = 1;
        
        cur_dir = cur_dir.normalize();
        cur_dir = cur_dir * speed;
        
        //given direction, we can give a general moving direction
        
        //so it is worth calculating
        if (cur_dir != Vector(0, 0)) {
            Vector next_dir = Scene::Instance().get_next_direction(cur_dir, anchor);
            anchor = anchor + next_dir;
            top_left = top_left + next_dir;
            top_right = top_right + next_dir;
            bot_left = bot_left + next_dir;
            bot_right = bot_right + next_dir;
            angel = Scene::Instance().get_current_angel();
            
            //calculate position of light ball in the head
            Point head = anchor;
            head.y -= 48.0f;
            Vector rotate_dir = (head - anchor).rotate(angel);
            torch->position = anchor + rotate_dir;
            
//            debug(next_dir);
        }
    }
        //reset key press
    for (int i = 0; i < 5; i++) pressed[i] = false;
    
    int x = 0, y = 0;
    SDL_GetMouseState( &x, &y );
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    
    torch->update(event);
    torch->rotate(x, y);
    
}


