//
//  polygon.cpp
//  Trilight
//
//  Created by Yue on 9/4/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "polygon.h"

Polygon::Polygon(){
    
}

Polygon::Polygon(std::vector<Point> points):points(points){
    
}

void Polygon::add_point(Point point){
    points.push_back(point);
}

void Polygon::clear_point(){
    points.clear();
}

std::vector<Edge> Polygon::getEdges(){
    std::vector<Edge> vec;
    for (int i = 0; i < points.size()-1; i++) {
        vec.push_back(Edge(points[i], points[i+1]));
    }
    vec.push_back(Edge(points[points.size()-1], points[0]));
    
    return vec;
}