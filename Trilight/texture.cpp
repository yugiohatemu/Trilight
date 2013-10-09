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


Texture::Texture(std::string fileName,int height, int width){
    this->width = width;
    this->height = height;
    textureID = 0;
    
    if (!load_file(fileName.c_str())) {
        error("Load Texture Fail");
    }
}

bool Texture::load_file(const char * fileName){
    std::ifstream file(fileName);
    int size =width*height*4;
    GLubyte * data = new GLubyte [size]; //for rgb, what if a is needed? //4 for rgba?
    file>>data;
    
    if (file.fail()) {
        file.close();
        delete [] data;
        return false;
    }
    
//    for (int i = 0 ; i < width * height; i++) {
//        data[4*i] = 0XFF;
//        data[4*i+1] = 0X0;
//        data[4*i+2] = 0X0;
//        data[4*i+3] = 0xFF;
//    }
    
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    // Nice trilinear filtering.
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    GLenum e = glGetError();
    if( e != GL_NO_ERROR ) std::cout<<gluErrorString(e)<<std::endl;
    
    file.close();
    delete [] data;
    //unbind texture
    glBindTexture( GL_TEXTURE_2D, NULL );
    return true;
}

Texture::~Texture(){
    glDeleteTextures(1, &textureID);
}

void Texture::render(){
    
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(50.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 50.0f);
    glEnd();
    
}

