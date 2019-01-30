//
//  ReadyQueue.cpp
//  CPU_scheduling
//
//  Created by Melanie W. on 10/29/17.
//  Copyright © 2017 Melanie Woe. All rights reserved.
//

#include "queue.h"
#include "process.h"
#include <cstring>

int HEAD = 0;
int TAIL = 1;
int INCREASE = 1;
int DECREASE = -1;

queue::queue()
{
    queue_process = new process[0];
    size = 0;
}

queue::~queue()
{
    delete[] queue_process;
}

void queue::push(process& p)
{
    queue_process = resize_arr(INCREASE, TAIL);
    queue_process[size - 1] = p;
}

process& queue::pop(process* p, int num_processes)
{
    process fp = queue_process[0];
    for (int i = 0; i < num_processes; ++i)
    {
        if (queue_process[0].getPID() == p[i].getPID())
        {
            p[i].setBurstTime(queue_process[0].getBurstTime());
            p[i].finished = queue_process[0].finished;
            p[i].num_context_switch = queue_process[0].num_context_switch;
            p[i].response_time = queue_process[0].response_time;
            p[i].time_of_completion = queue_process[0].time_of_completion;
            p[i].turnaround_time = queue_process[0].turnaround_time;
            p[i].waiting = queue_process[0].waiting;
            p[i].waiting_time = queue_process[0].waiting_time;
            break;
        }
    }
    //queue[0].~FakeProcess();
    queue_process = resize_arr(DECREASE, HEAD);
    
    return fp;
}

process& queue::remove(int pos, process* p, int num_processes)
{
    process fp = queue_process[pos];
    for (int i = 0; i < num_processes; ++i)
    {
        if (queue_process[pos].getPID() == p[i].getPID())
        {
            p[i].setBurstTime(queue_process[pos].getBurstTime());
            p[i].finished = queue_process[pos].finished;
            p[i].num_context_switch = queue_process[pos].num_context_switch;
            p[i].response_time = queue_process[pos].response_time;
            p[i].time_of_completion = queue_process[pos].time_of_completion;
            p[i].turnaround_time = queue_process[pos].turnaround_time;
            p[i].waiting = queue_process[pos].waiting;
            p[i].waiting_time = queue_process[pos].waiting_time;
            break;
        }
    }
    
    for (int i = pos; i < size - 1; ++i)
        queue_process[i] = queue_process[i + 1];
    
    queue_process = resize_arr(DECREASE, TAIL);
    
    return fp;
}

void queue::sort()
{
    process temp;
    bool swapped = true;
    int idx = 0;
    
    while (swapped)
    {
        swapped = false;
        ++idx;
        for (int i = 0; i < size - idx; ++i)
        {
            if (queue_process[i].getBurstTime() > queue_process[i + 1].getBurstTime())
            {
                temp = queue_process[i];
                queue_process[i] = queue_process[i + 1];
                queue_process[i + 1] = temp;
                swapped = true;
            }
        }
    }
}

void queue::sortBurstTime()
{
    process temp;
    bool swapped = true;
    int idx = 0;
    
    while (swapped)
    {
        swapped = false;
        ++idx;
        for (int i = 0; i < size - idx; ++i)
        {
            if (queue_process[i].getPriority() > queue_process[i + 1].getPriority())
            {
                temp = queue_process[i];
                queue_process[i] = queue_process[i + 1];
                queue_process[i + 1] = temp;
                swapped = true;
            }
        }
    }
}

process* queue::resize_arr(int mode, int from)
{
    size += mode;
    process* new_queue = new process[size];
    
    for (int i = 0; i < size; ++i)
    {
        if ((mode == INCREASE && from == TAIL) || (mode == DECREASE && from == TAIL))
        {
            new_queue[i] = queue_process[i];
        }
        else
        {
            new_queue[i] = queue_process[i + 1];
        }
    }
    
    return new_queue;
}

process* queue::get(int i)
{
    return &queue_process[i];
}

int queue::length()
{
    return size;
}

bool queue::empty()
{
    bool empty = false;
    if (size == 0)
        empty = true;
    
    return empty;
}
