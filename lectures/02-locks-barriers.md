# Lecture 26.aug 2024

- You want execution under mutual exclusion when working with a critical section
- Locks are low-level operation with hardware support. 
- Locks are used when you want to protect a critical section.
- Entry and exit protocols are typical patterns for Critical sections.
- All processes should do the exit protocol, else the resource will be locked forever.

- Busy waiting: doing nothing while waiting to get access. 
- The problem with busy waiting is both speed and when there is more processes. 
  - Fairness is also a problem


The desired critical section implementation: 
- mutual exclusion
- no deadlock
- no unnecessary delay
- Eventual entry => a process will eventually enter CS

The await syntax will not always be easy to implement in all languages. 


Lock is a primitive state that prevents multiple threads to access or modify the hidden state. 
- wait until the lock is free and then you take the lock
  - `< await (!lock) lock:=true>` => taking the lock when its free


TAS => Test and Set is a pattern for implementing a conditional atomic action
- Exists as an atomic operation. 
- https://en.wikipedia.org/wiki/Test-and-set

Test, Testa and set reduces the number of writes by introducing more reads to the protocol. 
- Reading cache is less expensive, it performs better than TAS 

If we have a good entry anc exit protocol, we assure that the critical section is correctly shared.

Enabledness => when a statement is enabled in stat if the statement can be in principle be executed next  

Unconditional fairness => ?
Weak fairness
- Unconditional fair
- when becomes true, stays true until executed

Unfair => not all processes have the chance to execute

Strong Fairness:
- Unconditionally fair
- if condition is true infinitely often 

When a entry protocol allows more than one process to access the critical section then we do w...

Turn `<await(B)>` to implementation by negating the condition and put it in a while loop. 

Spinlock: 
- Implementation with 

Tie Break algorithm: 
- .

Ticket Algorithm: 
- Generalizable to many processes.


Fetch and Add: 
- Fetch and add a number atomically
- Some machines have this implemented as a machine instruction

Shared counter:
- A way to wait for all processes to be done with their task. 


Flag synchronization principles: 
1. Process waiting for a flag is the one to reset the flag 
2. Flag will not be set before it is reset

Java has a set of classes that one can work with: 
- `java.util.concurrent.locks` packages
- Useful to use try-finally block. 
  - No matter what, always release the lock again


Barrier: property that will wait on multiple threads until the 