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
#include "light.h"
#include "texture.h"
#include "sprite.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "scene.h"

//#include "texture.h"
//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 30;

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
    glClearColor(255, 255, 255, 0);
    //orthogonal mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();
    
}

void clean_up(){
    Texture::Instance().clean_texture();
    SDL_Quit();
}



int main( int argc, char *argv[] ){
    //Quit flag
    bool quit = false;
    srand(time(0));
    //Initialize
    if( init() == false ) return 1;
    
    Scene &scene = Scene::Instance();
    scene.create_scene();
    //test texture
    if(Texture::Instance().load_file("/Users/wei/Desktop/Trilight/Trilight/white.png",64,64) < 0){
        return 1;
    }
    
    if(Texture::Instance().load_file("/Users/wei/Desktop/Trilight/Trilight/tiles.png",128,128) < 0){
        return 1;
    }
    //fps
    StopWatch fps(0.1);
    fps.start();

    //base
    bool pause = false;
	while( quit == false ){
        
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT )quit = true;
            if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_p) pause = !pause;
                else if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
            }

		}
        if (fps.is_timeup() && !pause) {
            
            render();
            scene.render();
            
            scene.update(event);
            
            SDL_GL_SwapBuffers();
            fps.start();
        }
	}
    
    //do all the cleaning, singelton and ect
	clean_up();
    scene.clear_scene();
    
	return 0;
}
