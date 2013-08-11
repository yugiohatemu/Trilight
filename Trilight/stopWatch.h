//
//  stopWatch.h
//  ForScience
//
//  Created by Yue on 7/20/13.
//  Copyright (c) 2013 Yue. All rights reserved.
//

#ifndef __ForScience__stopWatch___
#define __ForScience__stopWatch___

class StopWatch{
private:
    double time_left;
    int start_tick;
    double count_down;
public:
    
    StopWatch(double count_down);
    ~StopWatch();
    bool is_timeup();
    void start();
    void reset();
    
};


#endif /* defined(__ForScience__stopWatch___) */
