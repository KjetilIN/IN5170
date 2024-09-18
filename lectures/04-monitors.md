# Lecture 16.september 

- monitor in java where all methods are synchronized 
- monitor is a program module with more structure than semaphores
  - built in synchronization 
  - at most one procedure is active at the time for a monitor
  - two procedures in the same monitor can not run concurrently 

Cooperative scheduling: 
- procedures coordinate their monitor access 


Monitor usage:
- process is active if a statement in the procedure is executed by some process
- all shared variables inside the monitor

The **cond** act as a condition and a list of waiting procedures. The following commands are important to know:
- cond cv; # declares a condition variable cv
- empty(cv); # asks if the queue on cv is empty
- wait(cv); # causes process to wait in the cv queue
- signal(cv); # wakes up a process in the queue to cv
- signal_all(cv); # wakes up all processes in the cv queue

Signal and Wait (SW):
- the signaler waits and the singled process gets to execute immediately 

Signal and Continue (SC):
- the signaler continues and the signaled process waits 

Signal and Wait provides stronger guarantees about the state of shared resources when a thread resumes, as the waiting thread gets immediate access to the monitor.

Signal and Continue can be more efficient since the signaling thread does not have to give up control right away, but the waiting thread may need to re-check the condition when it finally gets control.