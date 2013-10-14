//
//  texture.cpp
//  Trilight
//
//  Created by Yue on 10/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//
#include <iostream>
#include "texture.h"
#include <fstream>
#include "utility.h"
#include "loadPNG.h"


Texture::Texture(){
}

Texture::Texture(Texture const&){
    
}
// copy constructor is private
Texture& Texture::operator=(Texture const&){
    return *this;
}

Texture& Texture::Instance(){
    static Texture m_Instance;
    return m_Instance;
}

////////////////////////////////////////////////////////////////////////


int Texture::load_file(const char * fileName,unsigned int width, unsigned int height){
 
    std::vector<unsigned char> image;
    unsigned  error = lodepng::decode(image, width, height, fileName);
    if(error != 0){
        debug(lodepng_error_text(error));
        return -1;
    }
    
    GLuint textureID = 0;
    
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    GLenum e = glGetError();
    if( e != GL_NO_ERROR ) std::cout<<gluErrorString(e)<<std::endl;
    
    textureList.push_back(textureID);
    
    //unbind
    glBindTexture( GL_TEXTURE_2D, NULL );
    return 1;
}


void Texture::clean_texture(){
    for (int i = 0; i < textureList.size(); i++) {
        glDeleteTextures(1, &textureList[i]);
    }
    textureList.clear();
}


GLuint Texture::get_texture(GLuint type){
    if (type < textureList.size()) {
        return textureList[type];
    }else{
        return 0;
    }
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

