//
//  ReadyQueue.hpp
//  CPU_scheduling
//
//  Created by Melanie W. on 10/13/17.
//  Copyright © 2017 Melanie Woe. All rights reserved.
//

#ifndef ReadyQueue_h
#define ReadyQueue_h

#include "process.h"


class queue {
private:
    process* resize_arr(int, int);
    process* queue_process;
    int size;
    
public:
    queue();
    ~queue();
    int length();
    bool empty();
    void push(process&);
    process& pop(process*, int);
    process& remove(int, process*, int);
    void sort();
    void sortBurstTime();
    process* get(int);
};

#endif /* ReadyQueue_h */
