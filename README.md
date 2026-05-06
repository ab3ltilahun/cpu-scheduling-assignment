# cpu-scheduling-assignment
Banker’s Algorithm
A deadlock happens when processes are permanently stuck waiting for resources that are held by 
each other. Because all the processes are waiting, none of them will ever cause any event that could 
wake up any of the other members of the set, and all the processes continue to wait forever.
In most cases, the event that each process is waiting for is the release of some resource currently 
possessed by another member of the set. In other words, each member of the set of deadlocked 
processes is waiting for a resource that is owned by a deadlocked process. None of the processes 
can run and none of them can release any resources.
The main algorithms for deadlock avoidance are based on the concept of safe states. A state is said 
to be safe if there is some scheduling order in which every process can run to completion even if all 
of them suddenly request their maximum number of resources immediately. 
The Banker's Algorithm acts like a cautious bank manager to avoid this. Before the Operating System 
grants a resource request, it simulates the allocation. It checks if doing so leaves the system in a 
"safe state",meaning there is at least one sequence of execution where all processes can finish 
without deadlocking. If a safe sequence exists, the request is granted; if not, the process must wait.

For More Visit Documentation.
