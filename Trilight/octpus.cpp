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
    
    orien = B2T;
    
    dir.x = 8;
    dir.y = 0;
    
    angel = 270;
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
    glTranslatef(+(box.x+box.w/2),+(box.y+box.h/4) , 0);
    glRotatef( orien*90,0, 0, 1);
    glTranslatef(-(box.x+box.w/2),-(box.y+box.h/4) , 0);
    
    glBegin(GL_QUADS);
    glTexCoord2f(clips[frame].x, clips[frame].y); glVertex2f(box.x, box.y);
    glTexCoord2f(clips[frame].x, clips[frame].y + clips[frame].h); glVertex2f(box.x, box.y+ box.h);
    glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y+ clips[frame].h); glVertex2f(box.x + box.w, box.y + box.h);
    glTexCoord2f(clips[frame].x + clips[frame].w, clips[frame].y); glVertex2f(box.x + box.w, box.y);
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
        if(event.key.keysym.sym == SDLK_SPACE) {
            orien += 1;
            if (orien == 4) {
                orien = 0;
            }
        }
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
    
    Vector next_dir = Scene::Instance().get_next_direction(cur_dir, angel, box);
    
    //and apply that to the next dir, or next angel?
    
    if (box.x < 0) box.x = 0;
    if (box.x > 640) box.x = 640;
    
    
    
    
//    int x = 0, y = 0;
//    SDL_GetMouseState( &x, &y );
//    if (x < 0) x = 0;
//    if (y < 0) y = 0;
    
//    torch->update(event);
//    torch->rotate(x, y);
    
    //give direction eg (1, 0) and current direction, box to the scene
    //ask the scene to give back the next speed vector
    //based on different orientation,
    
}


