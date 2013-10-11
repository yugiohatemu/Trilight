//
//  main.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "stopWatch.h"
#include "rect.h"
#include "light.h"
#include "texture.h"
#include "sprite.h"
#include <vector>
#include <iostream>
#include <fstream>


//#include "texture.h"
//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

//Event handler
SDL_Event event;

bool initGL(){
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR ){
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
    
    return true;
}

bool init(){
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) return false;
    
    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL ) return false;
    
    //Enable unicode
    SDL_EnableUNICODE( SDL_TRUE );
    
    //Initialize OpenGL
    if( initGL() == false ) return false;
    
    //Set caption
    SDL_WM_SetCaption( "Trilight", NULL );
    
    return true;
}

void handleKeys( unsigned char key, int x, int y ){
    
}

void update(){
    
}

void render(){
    //Clear color buffer
    
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //clear color and depth
    glEnable(GL_COLOR_MATERIAL);
    //enable texture
    glEnable( GL_TEXTURE_2D );
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    //orthogonal mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();
    
}

void clean_up(){
    Texture::Instance()->clean_texture();
    SDL_Quit();
}



int main( int argc, char *argv[] ){
    //Quit flag
    bool quit = false;
    srand(time(0));
    //Initialize
    if( init() == false ) return 1;
    
    std::vector<Rect> rectangles;
    
    for(int i = 2; i > 0; i--) {
		Rect rectangle((int) (rand() % 350)+75,  (int) (rand() % 300)+75, 25 + (int) (rand() % 80), 25 + int(rand() % 80));
		rectangles.push_back(rectangle);
	}
    
	//Create light
	Light l1(91);
	l1.position.x = 150;
	l1.position.y = 260;
	l1.specular.setRGBA(0xFFFFFF66);
	l1.size = 300.0f;
    
    //test texture
    if(Texture::Instance()->load_file("/Users/wei/Desktop/Trilight/Trilight/white.png",64,64) < 0){
        return 1;
    }
    
    //fps
    StopWatch fps(0.2);
    fps.start();
	//Wait for user exit

    //sprite list
    Sprite * eyeball = new Sprite(320,240);
    
    bool press[4] = {false,false,false,false};
    bool pause = false;
	while( quit == false ){
        
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT )quit = true;
            if (event.type == SDL_KEYDOWN) {
                
                if (event.key.keysym.sym == SDLK_w) press[0] = true;
                else if(event.key.keysym.sym == SDLK_a) press[1] = true;
                else if(event.key.keysym.sym == SDLK_s) press[2] = true;
                else if(event.key.keysym.sym == SDLK_d) press[3] = true;
                else if(event.key.keysym.sym == SDLK_p) pause = !pause;
                else if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
            }else if(event.type == SDL_KEYUP){
                
                if (event.key.keysym.sym == SDLK_w) press[0] = false;
                else if(event.key.keysym.sym == SDLK_a) press[1] = false;
                else if(event.key.keysym.sym == SDLK_s) press[2] = false;
                else if(event.key.keysym.sym == SDLK_d) press[3] = false;

            }
		}
        if (fps.is_timeup() && !pause) {
            int x = 0, y = 0;
            SDL_GetMouseState( &x, &y );
            if (x < 0) x = 0;
            if (y < 0) y = 0;
            
            render();
            
            for(int i = 0; i < rectangles.size(); i++) {
                //Render rect
                rectangles[i].render();
            }

            
            l1.render(rectangles);
            l1.render_clip(rectangles[0]);
            l1.rotate(x, y);
            
            eyeball->render();
            
            //update
           
            if(press[0]) l1.position.y -=2;
            if(press[1]) l1.position.x -= 2;
            if(press[2]) l1.position.y += 2;
            if(press[3]) l1.position.x += 2;
            
            eyeball->update();
            
            
            SDL_GL_SwapBuffers();
        }
	}
    //do all the cleaning, singelton and ect
	clean_up();
    delete eyeball;
    
	return 0;
}
