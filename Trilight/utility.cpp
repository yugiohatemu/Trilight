//
//  utility.cpp
//  Trilight
//
//  Created by Yue on 10/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "utility.h"
#include <iostream>

void error(std::string s){
    std::cout<<"ERROR: "<<s<<std::endl;
}

void debug(std::string s){
    std::cout<<"DEBUG: "<<s<<std::endl;
}