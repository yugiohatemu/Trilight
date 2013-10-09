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
#include "loadPNG.h"
#include "texture.h"
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
    //Quit SDL
    SDL_Quit();
}

unsigned int textureID = 0;

void load_file(const char * fileName){
    unsigned int width = 32;
    unsigned int height = 32;
    
    // Load file and decode image.
    std::vector<unsigned char> image;
    unsigned error = lodepng::decode(image, width, height, fileName);
    if(error != 0){
        std::cout << "error " << error << ": " << lodepng_error_text(error) << std::endl;
        return ;
    }
    //use image 2, if not being power of two
    // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
//    size_t u2 = 1; while(u2 < width) u2 *= 2;
//    size_t v2 = 1; while(v2 < height) v2 *= 2;
//    // Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
//    
//    // Make power of two version of the image.
//    std::vector<unsigned char> image2(u2 * v2 * 4);
//    for(size_t y = 0; y < height; y++)
//        for(size_t x = 0; x < width; x++)
//            for(size_t c = 0; c < 4; c++)
//            {
//                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
//            }
    
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    // Nice trilinear filtering.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    GLenum e = glGetError();
    if( e != GL_NO_ERROR ) std::cout<<gluErrorString(e)<<std::endl;
    std::cout<<textureID<<std::endl;
    
    
    //unbind texture
    //glBindTexture( GL_TEXTURE_2D, NULL );
    
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
//    Texture *text = new Texture("/Users/wei/Desktop/Trilight/Trilight/white.png",32,32);
    load_file("/Users/wei/Desktop/Trilight/Trilight/white.png");
    
    StopWatch fps(0.2);
    fps.start();
	//Wait for user exit

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
            
            glEnable( GL_TEXTURE_2D );
            glDisable(GL_BLEND);
            glPushMatrix();
            
//            text->render();
            glBindTexture( GL_TEXTURE_2D, textureID );
            
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(50.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(50.0f, 50.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 50.0f);
            glEnd();

            glPopMatrix();
            glBindTexture( GL_TEXTURE_2D,0);
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            if(press[0]) l1.position.y -=2;
            if(press[1]) l1.position.x -= 2;
            if(press[2]) l1.position.y += 2;
            if(press[3]) l1.position.x += 2;
            
            //Update screen
            SDL_GL_SwapBuffers();
        }
	}
    
	clean_up();
    
//    delete text;
    
	return 0;
}
