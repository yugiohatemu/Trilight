//
//  texture.h
//  Trilight
//
//  Created by Yue on 10/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__texture__
#define __Trilight__texture__

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include <string>

class Texture{
    unsigned int height;
    unsigned int width;
    GLuint textureID;
    bool load_file(const char * fileName);
public:
    Texture(std::string fileName,int height, int width);
    ~Texture();
    void render();
};

GLuint load_texture(const char * imagepath);

#endif /* defined(__Trilight__texture__) */
