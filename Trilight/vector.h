//
//  vector.h
//  Trilight
//
//  Created by Yue on 9/2/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __Trilight__vector__
#define __Trilight__vector__

//used for lighting calculation

//need to change vector definition
//this one is wrong
#include <iostream>

struct Vector{
    float x, y;
    
    Vector();
    Vector(float xx, float yy);
    Vector(Vector const & vec);
    float dot(Vector vec);
    float cross(Vector vec);
    
    Vector operator*(float t);
    Vector operator+(const Vector &vec);
    Vector operator=(const Vector & vec);
    bool operator==(const Vector & vec);
    bool operator!=(const Vector & vec);
    Vector rotate(float angel);
    Vector normalize();
    float get_norm();
    friend std::ostream& operator<< (std::ostream& stream, const Vector& vec);
    float get_angel();
};

bool is_vector_parallel(Vector a, Vector b);
Vector get_perpendicular(Vector a);

#endif /* defined(__Trilight__vector__) */
