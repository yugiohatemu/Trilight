//
//  Color.cpp
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "Color.h"

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

//Simple fuction for extracting colour values using a colour mask
void Color::setRGBA(int colour) {
    r = (colour & 0xFF000000) >> 24;
    g = (colour & 0x00FF0000) >> 16;
    b = (colour & 0x0000FF00) >> 8;
    a = (colour & 0x000000FF);
}
int Color::getRGBA() {
    return( (r << 24) & (g << 16) & (b << 8) & a );
}