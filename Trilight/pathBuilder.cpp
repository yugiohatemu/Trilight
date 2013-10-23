//
//  pathBuilder.cpp
//  Trilight
//
//  Created by Yue on 10/19/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#include "pathBuilder.h"
#include <fstream>
#include "utility.h"


int get_int_from_file(std::ifstream &file){
    int n = -1;
    file >> n;
    if (file.fail()) debug("READ INT fail");
    
    return n;
}

Point get_point_from_file(std::ifstream &file){
    //format of point (x,y)
    int x, y;
    char l_c,r_c,sel;
    file>>l_c>>x>>sel>>y>>r_c;
    if (l_c == '(' && sel == ',' && r_c == ')') {
        return Point(x,y);
    }else{
        return Point(-1,-1);
        debug("READ POINT fail");
    }
    
}

std::vector<Point> get_beizier_list(Point start,Point control,Point end){
    std::vector<Point> point_list;
    int strip = 10;
    //TODO: decide how many stripe do we need?
    
    float a = 1.0f;
    float b = 0.0f;
    
    //calculate beizier curve by ourselves and store it
    for (int i = 0; i <= strip; i++){
        float a_sq = a * a;
        float b_sq = b * b;
        float px = start.x * a_sq + control.x * 2 * a * b + end.x * b_sq;
        float py = start.y * a_sq + control.y * 2 * a * b + end.y * b_sq;
        
        point_list.push_back(Point (px, py));
        //Z(a) = Az·a² + Bz·2·a·b + Cz·b²
        //we do not need to calculate z since we are guaranteed on 2 dimesnsion
        
        a -= 1/(float)strip;
        b = 1.0 - a;
    }

    return point_list;
}


Path * read_path(std::string filename){
    std::ifstream file(filename.c_str());
    
    Path * path = NULL;
    Path * last = path;
    
    int n = get_int_from_file(file);
    if (n < 0) return NULL;
    
    for (int i = 0; i < n; i ++) {
        int c = get_int_from_file(file);
//        debug(c);
        if (c == 2) {
            Point start = get_point_from_file(file);
            Point end = get_point_from_file(file);
            if (start != Point(-1,-1) && end != Point(-1,-1)) {
                Path * p = new Path(start, end);
                if (last) {
                    last->next = p;
                    p->prev = last;
                    last = p;
                }else{ //first root
                    path = p;
                    last = path;
                }
                
            }else{
                delete_path(path);
                path = NULL;
                break;
            }
//            debug(start);
//            debug(end);
        }else if(c==3){
            Point start = get_point_from_file(file);
            Point control = get_point_from_file(file);
            Point end = get_point_from_file(file);
            
            if (start != Point(-1,-1) && end != Point(-1,-1) && control != Point(-1,-1)){
                //now ask control to produce beizier curve
                std::vector<Point> point_list = get_beizier_list(start, control, end);
                //based on that, create a path
                for (int i = 0; i < point_list.size()-1; i++) {
                    Path * p = new Path(point_list[i], point_list[i+1]);
//                    debug(point_list[i]);
                    if (last) {
                        last->next = p;
                        p->prev = last;
                        last = p;
                    }else{ //first root
                        path = p;
                        last = path;
                    }
                }
                
            }else{
                delete_path(path);
                path = NULL;
                break;
            }
        }else{
            delete_path(path);
            path = NULL;
            break;
        }
    }
    
    file.close();
    
    return path;
}

void render_path(Path * p){
    
    if (p){
        Path * prev = p->prev;
        Path * next = p;
        
        while (prev != NULL) {
            Path * temp = prev->prev;
            prev->render();
            prev = temp;
        }
        while (next != NULL) {
            Path * temp = next->next;
            next->render();
            next = temp;
        }
    }
}

void delete_path(Path * p){
    if (p){
        Path * prev = p->prev;
        Path * next = p;
        
        while (prev != NULL) {
            Path * temp = prev->prev;
            delete prev;
            prev = temp;
        }
        while (next != NULL) {
            Path * temp = next->next;
            delete next;
            next = temp;
        }
    }
}

std::vector<Edge> get_edge_from_path(Path * p){
    //do a boundary test when the scene get large~~
    
    std::vector<Edge> edge_list;
    Path * prev = p->prev;
    Path * next = p;
    
    while (prev != NULL) {
        Path * temp = prev->prev;
        edge_list.push_back(prev->get_edge());
        prev = temp;
    }
    while (next != NULL) {
        Path * temp = next->next;
        edge_list.push_back(next->get_edge());
        next = temp;
    }
    
    return edge_list;
}
