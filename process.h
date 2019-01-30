//
//  FakeProcess.hpp
//  CPU_scheduling
//
//  Created by Melanie W. on 10/13/17.
//  Copyright © 2017 Melanie Woe. All rights reserved.
//

#ifndef process_h
#define process_h

class process
{
    //implement the PCB process control block
    private:
        int pid;
        int arrival_time;
        int burst_time;
        int priority;
    
    public:
        process();
        process(int*);
    
        int getPID();
        int getArrivalTime();
        int getBurstTime();
        int getPriority();
        void setBurstTime(int);
        void progress();
    
        int num_context_switch;
        int original_CPU_BURST;
        bool waiting;
        bool finished;
        bool preempted;
    
        float time_of_completion;
        float waiting_time;
        float turnaround_time;
        float response_time;
    
};

#endif /* process_h */
