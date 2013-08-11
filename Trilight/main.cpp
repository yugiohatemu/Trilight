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
#include <vector>

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
    //glEnable(GL_MULTISAMPLE_ARB);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //clear color and depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();
 
    
    
}

void clean_up(){
    //Quit SDL
    SDL_Quit();
}


int main( int argc, char *argv[] ){
    srand(time(0));
    //Quit flag
    bool quit = false;
    
    //Initialize
    if( init() == false ) return 1;
    
    std::vector<Rect> rectangles;
    
	//Randomly create loads of small rectangles
	for(int i = 5; i > 0; i--) {
		Rect rectangle((int) (rand() % 350)+75,  (int) (rand() % 300)+75, 25 + (int) (rand() % 30), 25 + int(rand() % 30));
		rectangles.push_back(rectangle);
	}
    
	//Create light
	Light l1(90);
	l1.position.x = 250;
	l1.position.y = 260;
	l1.specular.setRGBA(0xFFFF0055);
	l1.size = 300.0f;
    
    
    Light l2(90);
    l2.position.x = 100;
    l2.position.y = 260;
    l2.specular.setRGBA(0xFFFFFF60);
    l2.size = 100.0f;
    
    StopWatch fps(0.2);
    fps.start();
	//Wait for user exit
	while( quit == false ){
        render();
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_QUIT )quit = true;
		}
        
        int x = 0, y = 0;
        SDL_GetMouseState( &x, &y );
        if (x < 0) x = 0;
        if (y < 0) y = 0;

        l1.render(rectangles);
        l1.rotate(x, y);
        l2.render(rectangles);
        //Render rectangles
        for(int i = 0; i < rectangles.size(); i++) {
            //Render rect
            rectangles[i].render();
        }
        
        if (fps.is_timeup()) {
            update();
           
            //Update screen
            SDL_GL_SwapBuffers();
            
            
        }
	}
    
	clean_up();
    
	return 0;
}
