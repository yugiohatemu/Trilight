//
//  shader.cpp
//  Trilight
//
//  Created by Yue on 11/1/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "shader.h"
#include "utility.h"

Shader::Shader(){
    
}
Shader::Shader(Shader const &){
    
}

Shader& Shader::operator= (Shader const &){
    return *this;
}

Shader& Shader::Instance(){
    static Shader m_Instance;
    return m_Instance;
}

//////////////////////////////////////////////////////////////////////////////

void Shader::init(){
    GLuint v,f;
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
    
	std::string vs = readFile("/Users/wei/Desktop/Trilight/Trilight/smoke.vert");
    std::string fs = readFile("/Users/wei/Desktop/Trilight/Trilight/smoke.frag");
    
	const char * vv = vs.c_str();
	const char * ff = fs.c_str();
    
	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);
    
	glCompileShader(v);
	glCompileShader(f);
    
	printShaderInfoLog(v);
	printShaderInfoLog(f);
    
	program = glCreateProgram();
    
	glAttachShader(program,v);
	glAttachShader(program,f);
    
	glLinkProgram(program);
	printProgramInfoLog(program);
    
    //Detach and clean it since it uses a lot of spaces~
    glDetachShader(program, v);
    glDetachShader(program, f);
    glDeleteShader(v);
    glDeleteShader(f);
    
}

void Shader::use_shader(){
    glUseProgram(program);
}

void Shader::clear(){
    glDeleteProgram(program);
}