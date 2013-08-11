//
//  Color.h
//  Trilight
//
//  Created by Yue on 8/11/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__Color__
#define __Trilight__Color__

class Color {
public:
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    //unsigned char 0-255

    Color();
    //Simple fuction for extracting colour values using a colour mask
    void setRGBA(int colour) ;
    int getRGBA();
};
#endif /* defined(__Trilight__Color__) */
