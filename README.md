# cpu-scheduling-assignment
CPU Scheduling
When a computer is multi programmed, it frequently has multiple processes competing for the CPU at the same time and when these processes are there in the ready state than the number of available CPUs, the operating system must decide which process to run first. 
CPU Scheduling is deciding which process to execute and when to excute each process in order to use the efficient use of the CPU.The Algorithm we use to perform each scheduling is called Scheduling algorithm.Scheduling algorithms can be divided into two categories with respect to how they deal with clock interrupts.
Preemptive scheduling: allows releasing the current executing process from CPU when another process comes and need execution.
Non-preemptive scheduling: once the CPU has been allocated to a process, the process keeps the CPU until it release the CPU . 
We use different terms to express time periods each process used while being processed and while waiting for to be excuted such as,
Turnaround time:For a particular process, it is the total time needed for process execution It is the sum of process execution time and its waiting times.
Waiting time:The waiting time for a specific process is the sum of all periods it spends waiting in the ready queue.
Response time:It is the time from the submission of a process until the first response is produced (the time the process takes to start responding).

