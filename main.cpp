//
//  main.cpp
//  CPU_scheduling
//
//  Created by Melanie W. on 10/13/17.
//  Copyright © 2017 Melanie Woe. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "queue.h"
#include "process.h"

using namespace std;

string file_process;
string file_process_output;

//int num_processes = 0;
//sum and avg
int   context_switch_total  = 0;
float avg_CPU_BURST = 0;
float avg_waiting_time = 0;
float avg_turnaround_time = 0;
float avg_response_time = 0;
int time_quantum = 0;


//read the processed from the file into 3 array
int get_processes(process* processes)
{
    int p = 0;
    int p_data[4];
    string curr_line;
    ifstream infile(file_process.c_str());
    
    if (infile.good())
    {
        while (getline(infile, curr_line))
        {
            int p_data_count = 0;
            
            for (int i = 0; i < curr_line.size(); ++i)
            {
                if (curr_line[i] != ' ')
                {
                    string num = "";
                    while (curr_line[i] != ' ' && curr_line[i] != '\0')
                    {
                        num += curr_line[i];
                        ++i;
                    }
                    
                    if (p_data_count < 4)
                    {
                        p_data[p_data_count] = atoi(num.c_str());
                        ++p_data_count;
                    }
                }
            }
            
            // Create a new FakeProcess from the current line of the input file
            process fp(p_data);
            
            // store new process
            processes[p] = fp;
            ++p;
        }
    }
    else
    {
        // unable to read file
        infile.close();
        return 1;
    }
    
    // file is successfilly stored
    infile.close();
    return 0;
}

//get total process
int get_total_process()
{
    int total_process = 0;
    string curr_line;
    ifstream infile(file_process.c_str());
    
    while (getline(infile, curr_line))
    {
        ++total_process;
    }
    
    infile.close();
    
    return total_process;
}

void star()
{
    for(int i=1;i<61;i++)
    {
        cout<<"**";
    }
    
    cout<<"\n";
}

void line()
{
    for(int i=1;i<61;i++)
    {
        cout<<"--";
    }
    
    cout<<"\n";
}


//print all the results
void print_stats(process* p, int total_process, int algorithm_type)
{
    ofstream outfile(file_process_output.c_str()); // open the output file
    string algorithm_type_output;
    
    if (algorithm_type == 0)
    {
        algorithm_type_output = "FCFS ";
    }
    else if (algorithm_type == 1)
    {
        algorithm_type_output = "SRTF ";
    }
    else if (algorithm_type == 2)
    {
        algorithm_type_output = "Round Robin ";
    }
    else if (algorithm_type == 3)
    {
        algorithm_type_output = "Preemptive Priority ";
    }
    
    
    //output to a new file
    if (!outfile)
    {
        // unable to read file
        cout << "Unable to output file" << endl;
        exit(0);
    }
     
    for(int i=1;i<61;i++)
    {
        outfile<<"**";
    }
    
    outfile<<"\n";
    outfile << setw(60) << "Scheduling Algorithm: " << algorithm_type_output << endl;
    
    //print time quantum if rr
    if (algorithm_type == 2)
    {
        outfile << setw(60) << "No. of Task = " << total_process << "Quantum = " << time_quantum << endl;
    }
    
    for(int i=1;i<61;i++)
    {
        outfile<<"**";
    }
    
    outfile<<"\n";
    outfile << endl;
    for(int i=1;i<61;i++)
    {
        outfile<<"--";
    }
    
    outfile<<"\n";
    
    outfile << "pid \t" << "arrival \t" << "CPU-burst \t" << "Priority \t" << "finish \t" << "waiting time \t" << "turn around \t" << "response time \t" << "No.of context \t" << endl;
    
    for(int i=1;i<61;i++)
    {
        outfile<<"--";
    }
    
    outfile<<"\n";
    
    for (int i = 0; i < total_process; i++)
    {
        outfile << fixed << setprecision(1) << setw(2) << p[i].getPID() << setw(10) << p[i].getArrivalTime() << setw(16) << p[i].original_CPU_BURST << setw(16) << p[i].getPriority() << setw(17) << p[i].time_of_completion << setw(13) << p[i].waiting_time << setw(14) << p[i].turnaround_time << setw(15) << p[i].response_time << setw(14) << p[i].num_context_switch << endl;
        
        avg_CPU_BURST += p[i].original_CPU_BURST;
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
        avg_response_time += p[i].response_time;
        context_switch_total += p[i].num_context_switch;
    }
    
    for(int i=1;i<61;i++)
    {
        outfile<<"--";
    }
    
    outfile<<"\n";
    
    avg_CPU_BURST /= total_process;
    avg_waiting_time /=  total_process;
    avg_turnaround_time /=  total_process;
    avg_response_time /=  total_process;
    
    outfile << fixed << setprecision(2) << "Average CPU burst time = " << avg_CPU_BURST << " ms" << endl;
    outfile << fixed << setprecision(2) << "Average waiting time = " << avg_waiting_time << " ms" << endl;
    outfile << fixed << setprecision(2) << "Average turn around time = " << avg_turnaround_time << " ms" << endl;
    outfile << fixed << setprecision(2) << "Average response time = " << avg_response_time << " ms" << endl;
    outfile << fixed << setprecision(2) << "Total No. of Context Switching Performed = " << context_switch_total << endl;
    
    // file is successfilly stored
    outfile.close();
    cout << "Done !" << endl;
}

//determine if any process can be added to the ready queue, needed for srtf
bool time_in_range(int clock, int arrival_time, int cswitches)
{
    bool in_range = false;
    
    for (int i = 0; i <= cswitches; ++i)
    {
        if (clock - (0.5 * i) == arrival_time)
        {
            in_range = true;
            break;
        }
    }
    
    return in_range;
}

//implement FCFS algortihm
void FCFS(process* p, int total_process, int choice)
{
    queue ready_queue; //queue fifo
    float time = 0;
    int p_idx = 0;          //next process to be added to queue
    int p_count = total_process; //total_process has not queue
    int context_switch_count = 0;
    
    while (p_count != 0)
    {
        process fp;
        p[p_idx].waiting = true;
        ready_queue.push(p[p_idx]);
        ++p_idx;
        
        if (!ready_queue.empty())
        {
            if (ready_queue.get(0)->waiting == true)
            {
                if (!ready_queue.get(0)->preempted)
                {
                    ready_queue.get(0)->response_time = time - ready_queue.get(0)->getArrivalTime();
                }
                
                ready_queue.get(0)->waiting = false;
            }
            
            // Decrement the CPU Burst field of the current process's PCB
            ready_queue.get(0)->progress();
            if (ready_queue.get(0)->getBurstTime() == 0)
            {
                ready_queue.get(0)->time_of_completion = time + 1;
                ready_queue.get(0)->turnaround_time = time + 1 - ready_queue.get(0)->getArrivalTime();
                ready_queue.get(0)->finished = true;
                
                // Adjust total waiting time of the process to include 0.5 ms for each
                // context switch it had encountered while waiting
                if (context_switch_count > 0)
                {
                    ready_queue.get(0)->waiting_time += context_switch_count * 0.5;
                }
                
                ready_queue.pop(p, total_process);
                --p_count;
            }
        }
        
        for (int i = 0; i < ready_queue.length(); ++i)
        {
            if (!ready_queue.get(i)->finished && ready_queue.get(i)->waiting)
                ++ready_queue.get(i)->waiting_time;
        }
        
        ++time;
    }
    
    // Print results and compute avg
    print_stats(p, total_process, choice);
}


// implements SRTF algorithm
void SRTF(process* p, int total_process, int choice)
{
    queue ready_queue; //queue fifo
    float time = 0;
    int p_idx = 0;          //next process to be added to queue
    int p_count = total_process; //total_process has not queue
    int last_process_pid = 1;
    int context_switch_count = 0;
    
    while (p_count != 0)
    {
        if (time_in_range(time, p[p_idx].getArrivalTime(), context_switch_count))
        {
            process fp;
            
            p[p_idx].waiting = true;
            ready_queue.push(p[p_idx]);
            ++p_idx;
            
            ready_queue.sort();
        }
        
        if (!ready_queue.empty())
        {
            if (ready_queue.get(0)->waiting == true)
            {
                if (last_process_pid != ready_queue.get(0)->getPID())
                {
                    for (int i = 0; i < ready_queue.length(); ++i)
                    {
                        if (ready_queue.get(i)->getPID() == last_process_pid)
                        {
                            ++ready_queue.get(i)->num_context_switch;
                            
                            // Identify a preempted process and add 0.5 to the clock
                            if (!ready_queue.get(i)->finished)
                            {
                                ready_queue.get(i)->waiting = true;
                                ready_queue.get(i)->preempted = true;
                                time = time + 0.5;
                                ++context_switch_count;
                            }
                            break;
                        }
                    }
                    
                }
                
                if (!ready_queue.get(0)->preempted)
                {
                    ready_queue.get(0)->response_time = time - ready_queue.get(0)->getArrivalTime();
                }
                
                ready_queue.get(0)->waiting = false;
            }
            
            last_process_pid = ready_queue.get(0)->getPID();
            
            // Decrement the CPU Burst field of the current process's PCB
            ready_queue.get(0)->progress();
            
            if (ready_queue.get(0)->getBurstTime() == 0)
            {
                ready_queue.get(0)->time_of_completion = time + 1;
                ready_queue.get(0)->turnaround_time = time + 1 - ready_queue.get(0)->getArrivalTime();
                ready_queue.get(0)->finished = true;
                
                // Adjust total waiting time of the process to include 0.5 ms for each
                // context switch it had encountered while waiting
                if (context_switch_count > 0)
                    ready_queue.get(0)->waiting_time += context_switch_count * 0.5;
                
                ready_queue.pop(p, total_process);
                
                --p_count;
            }
        }
        
        ready_queue.sort();
        
        for (int i = 0; i < ready_queue.length(); ++i)
        {
            if (!ready_queue.get(i)->finished && ready_queue.get(i)->waiting)
                ++ready_queue.get(i)->waiting_time;
        }
        
        ++time;
    }
    
    // Print results and compute avg
    print_stats(p, total_process, choice);
}
// implements the cpu scheduling algorithm RR
void RR(process* p, int total_process, int choice, int quantum)
{
    queue ready_queue; //queue fifo
    float time = 0;
    int p_idx = 0;          //next process to be added to queue
    int p_count = total_process; //total_process has not queue
    int last_process_pid = 1;
    int context_switch_count = 0;
    int iterations = quantum;
    bool rr_exception = false;
    
    while (p_count != 0)
    {
        if (time_in_range(time, p[p_idx].getArrivalTime(), context_switch_count))
        {
            process fp;
            int end_idx = ready_queue.length() - 1;
            
            if (!rr_exception && ready_queue.length() > 1 && quantum == iterations)
            {
                fp = ready_queue.remove(end_idx, p, total_process);
            }
            
            p[p_idx].waiting = true;
            ready_queue.push(p[p_idx]);
            ++p_idx;
            
            if (rr_exception)
            {
                process temp = ready_queue.pop(p, total_process);
                ready_queue.push(temp);
                rr_exception = false;
            }
            else
            {
                if (end_idx + 1 > 1 && quantum == iterations)
                {
                    ready_queue.push(fp);
                }
            }
        }
        
        else
        {
            if (last_process_pid == ready_queue.get(0)->getPID() && iterations == quantum)
            {
                rr_exception = true;
            }
        }
        
        if (!ready_queue.empty())
        {
            if (ready_queue.get(0)->waiting == true)
            {
                if (last_process_pid != ready_queue.get(0)->getPID())
                {
                    for (int i = 0; i < ready_queue.length(); ++i)
                    {
                        if (ready_queue.get(i)->getPID() == last_process_pid)
                        {
                            ++ready_queue.get(i)->num_context_switch;
                                
                            // Identify a preempted process and add 0.5 to the clock
                            if (!ready_queue.get(i)->finished)
                            {
                                ready_queue.get(i)->waiting = true;
                                ready_queue.get(i)->preempted = true;
                                time = time + 0.5;
                                ++context_switch_count;
                            }
                            break;
                        }
                    }
                    
                }
                
                if (!ready_queue.get(0)->preempted)
                {
                    ready_queue.get(0)->response_time = time - ready_queue.get(0)->getArrivalTime();
                }
                
                ready_queue.get(0)->waiting = false;
            }
            
            last_process_pid = ready_queue.get(0)->getPID();
            
            
            // Decrement the CPU Burst field of the current process's PCB
            ready_queue.get(0)->progress();
        
            --iterations;
            
            if (ready_queue.get(0)->getBurstTime() == 0)
            {
                ready_queue.get(0)->time_of_completion = time + 1;
                ready_queue.get(0)->turnaround_time = time + 1 - ready_queue.get(0)->getArrivalTime();
                ready_queue.get(0)->finished = true;
                
                // Adjust total waiting time of the process to include 0.5 ms for each
                // context switch it had encountered while waiting
                if (context_switch_count > 0)
                    ready_queue.get(0)->waiting_time += context_switch_count * 0.5;
                
                ready_queue.pop(p, total_process);
                
                iterations = quantum;
                
                --p_count;
            }
            else
            {
                if (iterations == 0)
                {
                    process temp = ready_queue.pop(p, total_process);
                    ready_queue.push(temp);
                    iterations = quantum;
                }
            }
        }
        
        for (int i = 0; i < ready_queue.length(); ++i)
        {
            if (!ready_queue.get(i)->finished && ready_queue.get(i)->waiting)
            {
                ++ready_queue.get(i)->waiting_time;
            }
        }
        
        ++time;
    }
    
    // Print results and compute avg
    print_stats(p, total_process, choice);
}

void PP(process* p, int total_process, int choice)
{
    queue ready_queue; //queue fifo
    float time = 0;
    int p_idx = 0;          //next process to be added to queue
    int p_count = total_process; //total_process has not queue
    int last_process_pid = 1;
    int context_switch_count = 0;
    
    while (p_count != 0) {
        if (time_in_range(time, p[p_idx].getArrivalTime(), context_switch_count))
        {
            process fp;
            int end_idx = ready_queue.length() - 1;
            
            p[p_idx].waiting = true;
            ready_queue.push(p[p_idx]);
            ++p_idx;
            
            ready_queue.sort();
            ready_queue.sortBurstTime();
            
        }
        
        if (!ready_queue.empty())
        {
            if (ready_queue.get(0)->waiting == true)
            {
                if (last_process_pid != ready_queue.get(0)->getPID())
                {
                    for (int i = 0; i < ready_queue.length(); ++i)
                    {
                        if (ready_queue.get(i)->getPID() == last_process_pid)
                        {
                            ++ready_queue.get(i)->num_context_switch;
                            
                            // Identify a preempted process and add 0.5 to the clock
                            if (!ready_queue.get(i)->finished)
                            {
                                ready_queue.get(i)->waiting = true;
                                ready_queue.get(i)->preempted = true;
                                time = time + 0.5;
                                ++context_switch_count;
                            }
                            break;
                        }
                    }
                }
                
                
                if (!ready_queue.get(0)->preempted)
                {
                    ready_queue.get(0)->response_time = time - ready_queue.get(0)->getArrivalTime();
                }
                
                ready_queue.get(0)->waiting = false;
            }
            
            last_process_pid = ready_queue.get(0)->getPID();
            
            // Decrement the CPU Burst field of the current process's PCB
            ready_queue.get(0)->progress();
            
            if (ready_queue.get(0)->getBurstTime() == 0)
            {
                ready_queue.get(0)->time_of_completion = time + 1;
                ready_queue.get(0)->turnaround_time = time + 1 - ready_queue.get(0)->getArrivalTime();
                ready_queue.get(0)->finished = true;
                
                // Adjust total waiting time of the process to include 0.5 ms for each
                // context switch it had encountered while waiting
                if (context_switch_count > 0)
                    ready_queue.get(0)->waiting_time += context_switch_count * 0.5;
                
                ready_queue.pop(p, total_process);
                
                
                --p_count;
            }
        }
        
        ready_queue.sort();
        ready_queue.sortBurstTime();
        
        for (int i = 0; i < ready_queue.length(); ++i)
        {
            if (!ready_queue.get(i)->finished && ready_queue.get(i)->waiting)
                ++ready_queue.get(i)->waiting_time;
        }
        
        ++time;
    }
    
    // Print the modified fields of each process to a table,
    // and also compute some averages
    print_stats(p, total_process, choice);
}

int main(int argc, char* argv[])
{
    file_process = string(argv[1]);
    file_process_output = string(argv[2]);
    int total_process = get_total_process();
    int algorithm_type = atoi(argv[3]);
    
    process* new_process;
    
    //if algorithm = 2, round robin requires time quantum
    if (algorithm_type == 2)
    {
        if (argv[4] != NULL)
        {
            time_quantum = atoi(argv[4]);
        }
        else
        {
            cout << "Time quantum is not defined" << endl;
            return -1;
        }
    }
    
    if (time_quantum > -1)
    {
        new_process = new process[total_process ];
        
        if (get_processes(new_process) != 1)
        {
            switch (algorithm_type)
            {
                case 0:
                    FCFS(new_process, total_process, algorithm_type);
                    break;
                case 1:
                    SRTF(new_process, total_process, algorithm_type);
                    break;
                case 2:
                    RR(new_process, total_process, algorithm_type, time_quantum);
                    break;
                case 3:
                    PP(new_process, total_process, algorithm_type);
                    break;
            }
            
        }
        else
        {
            cout << "Unable to read file" << endl;
            return -1;
        }
        
        delete [] new_process;
    }
    
    return 0;
}
