//
//  main.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <GLUT/GLUT.h>
#include <OpenGL/glext.h>
#include <string>

#include "texture.h"
#include "stopWatch.h"
#include "utility.h"
#include "scene.h"
#include "shader.h"
//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

bool initGL(){
    //Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40, 1.0, 1.0, 10.0);
    
    //glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,1,-1);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 10.0,0.0, 0.0, 0.0, 0.0, 1.0, 0.);
    
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR ){
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
    
    //Clear color buffer
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //clear color and depth
    glEnable(GL_COLOR_MATERIAL);
    //enable texture
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_DEPTH_TEST);
    //
    glShadeModel(GL_SMOOTH);
    //
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* Red diffuse light. */
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    
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

void render(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor( 0.f, 0.f, 0.f, 1.f );
}

void clean_up(){
    Texture::Instance().clean_texture();
    SDL_Quit();
}

int main( int argc, char *argv[] ){
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false ) return 1;
    //shaders~
    Shader::Instance().init();
    //
    glUseProgram(0);
    Scene &scene = Scene::Instance();
    scene.create_scene();
    //test texture
    if(Texture::Instance().load_file("/Users/wei/Desktop/Trilight/Trilight/white.png",128,128) < 0){
        return 1;
    }
    
    if(Texture::Instance().load_file("/Users/wei/Desktop/Trilight/Trilight/tiles.png",128,128) < 0){
        return 1;
    }
    
    if(Texture::Instance().load_file("/Users/wei/Desktop/Trilight/Trilight/fontTile.png",512,512) < 0){
        return 1;
    }
    //fps
    StopWatch fps(0.1);
    fps.start();

    //base
    bool pause = false;
    //Event handler
    SDL_Event event;

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
//            scene.render();
//            
//            scene.update(event);
            glPushMatrix();
            glColor3d(1.0, 0, 0);
            glRotated(45, 1, 0, 0);
            glutSolidCube(1.0);
            glPopMatrix();
            
            SDL_GL_SwapBuffers();
            fps.start();
        }
	}
    
    //do all the cleaning, singelton and ect
	clean_up();
    scene.clear_scene();
    Shader::Instance().clear();
    
	return 0;
}
