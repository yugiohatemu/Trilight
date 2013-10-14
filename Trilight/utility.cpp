//
//  utility.cpp
//  Trilight
//
//  Created by Yue on 10/8/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "utility.h"
#include <iostream>

//void error(std::string s){
//    std::cout<<"ERROR: "<<s<<std::endl;
//}
//
//void debug(std::string s){
//    std::cout<<"DEBUG: "<<s<<std::endl;
//}
//
//bool check_collision(A_Rect A, B_Rect B  ){
//    //The sides of the rectangles
//    int leftA, leftB;
//    int rightA, rightB;
//    int topA, topB;
//    int bottomA, bottomB;
//    
//    //Calculate the sides of rect A
//    leftA = A.x;
//    rightA = A.x + A.w;
//    topA = A.y;
//    bottomA = A.y + A.h;
//    
//    //Calculate the sides of rect B
//    leftB = B.x;
//    rightB = B.x + B.w;
//    topB = B.y;
//    bottomB = B.y + B.h;
//    
//    //If any of the sides from A are outside of B
//    if( bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
//        return false;
//    
//    //If none of the sides from A are outside B
//    return true;
//}
