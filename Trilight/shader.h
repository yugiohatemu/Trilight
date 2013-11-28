//
//  shader.h
//  Trilight
//
//  Created by Yue on 11/1/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__shader__
#define __Trilight__shader__

//a singelton named shaders~~
#include "SDL/SDL_opengl.h"

class Shader{
    Shader();
    Shader(Shader const &);
    Shader& operator= (Shader const &);
    GLuint program;
    
public:
    static Shader& Instance();
    void init();
    void use_shader();
    void clear();
};


#endif /* defined(__Trilight__shader__) */
