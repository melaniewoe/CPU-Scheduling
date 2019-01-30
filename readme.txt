*******************************************************
*  Description of the program
*******************************************************

CPU Scheduling is c++ a program that selects a processor from
a ready queue and executes the program by given scheduling
algorithm. User can choose any scheduling algorithm (FCFS, 
SRTF, RR-with quantum, and PP). The program will also 
display its activities and evaluate its performance
based on collected some measurements such as average, 
turn-around time, average waiting time, and average 
response time. 

The user can select one algorithm when they start the 
simulator as the 3rd argument. For example,
FCFS :./myscheduler test-input-file-name output-file-name 0
SRTF: ./myscheduler test-input-file-name output-file-name 1PP: ./myscheduler test-input-file-name output-file-name 3
while for RR, it needs the time quantum as the 4th 
argument:
RR:./myscheduler test-input-file-name output-file-name 2 quantum size

When the program runs successfully, it will output “Done”
and the new file will be in the folder.

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program. All the implementation of scheduling algorithms are done in this file. The program reads in 
the input text file (arg[1]) and placed them in array. 
The array is then passed to function depending on the 
user’s prompt (can be FCFS, SRTF, RR, or PP). Each algorithm 
functions will use the while loop until all processes have 
the status of finished. The program then output the file 
to a new text file that is named by user.

Name: queue.h
   Header file for queue.cpp.

Name: queue.cpp
   This is the implementation of queue. It contains the 
functions to sort(), sortBurstTime(), push(), pop(), remove()
to manage the queue. 

Name: process.h
   Header file for process.cpp.

Name: process.cpp
   This is the implementation of PCB structures for each
process.

*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on xCode version 7.2

*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [Woe7790]

   Now you should see a directory named homework with the files:
        main.cpp
        queue.h
	queue.cpp
	process.h
	process.cpp
        makefile
        Readme.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd [Woe7790] 

    Compile the program by:
    % g++ -w main.cpp queue.cpp process.cpp -o myscheduler

3. Run the program by:
   % ./myscheduler test-input-file-name output-file-name algorithm-choice

4. Delete the obj files, executables, and core dump by
   %./make clean

