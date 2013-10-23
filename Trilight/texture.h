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
#include <vector>
//singelton texture for controlling all the texture loading


class Texture{
private:
    Texture();  // Private so that it can  not be called
    Texture(Texture const&);             // copy constructor is private
    Texture& operator=(Texture const&);  // assignment operator is private

    unsigned int height;
    unsigned int width;
    
public:
    enum{
        NPC,
        TILE,
        FONT,
        TOTAL_TEXTURE,
    }TEXTURE_TYPE;
    
    std::vector<GLuint> textureList;
    
    static Texture& Instance();
    int load_file(const char * fileName,unsigned int width,unsigned int height);
    void clean_texture();
//    void use_texture();
    GLuint get_texture(GLuint type);
    //static void unbind_texture();
};

#endif /* defined(__Trilight__texture__) */
