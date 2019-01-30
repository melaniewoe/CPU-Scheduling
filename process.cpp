//
//  FakeProcess.cpp
//  CPU_scheduling
//
//  Created by Melanie W. on 10/13/17.
//  Copyright © 2017 Melanie Woe. All rights reserved.
//

#include "process.h"

process::process()
{
    pid = 0;
    arrival_time = 0;
    burst_time = 0;
    priority = 0;
    original_CPU_BURST = 0;
    time_of_completion = 0;
    waiting_time = 0;
    turnaround_time = 0;
    response_time = 0;
    num_context_switch = 0;
    waiting = false;
    finished = false;
    preempted = false;
}

process::process(int* p_data)
{
    pid = p_data[0];
    arrival_time = p_data[1];
    burst_time = p_data[2];
    priority = p_data[3];
    original_CPU_BURST = burst_time;
    time_of_completion = 0;
    waiting_time = 0;
    turnaround_time = 0;
    response_time = 0;
    num_context_switch = 0;
    waiting = false;
    finished = false;
    preempted = false;
}

int process::getPID()
{
    return pid;
}

int process::getArrivalTime()
{
    return arrival_time;
}

int process::getBurstTime()
{
    return burst_time;
}

int process::getPriority()
{
    return priority;
}

void process::setBurstTime(int burst)
{
    burst_time = burst;
}

void process::progress()
{
    --burst_time;
}
