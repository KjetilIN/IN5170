# Lecture 2.sep. 2024 - Semaphores

- Hardware support (CMPXCHG)
  - Well known and implemented at OS level
- Inspired by railroad traffic sync. 
  - Railroad clear or not
- Manipulated by two atomic operations
  - P : wait for signal
    - Wait until greater than zero and decrease value by one 
    - Guaranteed that you only have access when P is successful (and initial value 1)
  - V: Signal an event, release
    - Increase the value by one 
- 

With await syntax:

```text
# Create semaphore 
sem s; // Init value 0 
sem s := 1; 
sem s[4] := ([4] 1) 

# P:
<await (s>0)s:=s-1>

# S:
<s:= s+1>
```

No direct access to the value of a semaphore 

General Semaphore: all non-negative integers
Binary semaphore: only 0 and 1 possible 

- Order is FIFO (you can assume)
- Setting a semaphore to 1 means that you want one process to access at the same time
- Always P -> V
- Can also be used in the other order to signal events
  - Signal that you a process has arrived (barrier)

Split binary semaphore:
- Set of semaphores whore sum <= 1
  - Meaning only one can access at the time (After P is successful)

Buffer Capacity with Semaphores
- Ring buffer with two int (front and rear)
- Number of slots, keep track of empty slots => represented as a semaphore 
- No critical sections when you have one producer and consumer
- Need sync. with more producers and consumers. 
  - Solution => two mutex for denying access to buffer (fetch and put)
  - Two things that you are protecting. Buffer and Buffer access (to modify the pointers)

## Example: Dining philosophers 

- Each person needs two forks to eat
- Five people and only one fork between each person. 
- Everyone cannot eat at the same time
- They think and eat alternatively. 
  
The problem is programming this:
- If everyone start by take the left, there is a high chance on deadlock
- We can fix this by making a philosopher take to the right first. 


## Invariants and Condition Synchronization 
- Classical problem for shared access
- Exp: readers and writers for a database
  - Readers and writers compete (writers also compete against writers)
  - Mutex solves this but is unfair
  - Conditional synchronization 
    - Using split binary semaphores

You can implement mutex with semaphores:

```text
int nr := 0; 
sem rw := 1; 
sem mutexR := 1; 

process Reader [i=1 to M]{
    while(true){
        P(mutexR)
            nr := nr +1; 
            if (nr = 1) P(rw)
        V(mutexR)

        # Read

        P(mutexR)
            nr := nr - 1; 
            if (nr = 0) P(rw)
        V(mutexR)
    }
}
```

- This is unfair. Writer will never run with a constant stream of readers. 

Solution: 
- Two counters: active readers and writers 
- Consider what invariant we want here. Invariant must be hold 
- Implement Split binary semaphore with split binary semaphores
- SIGNAL to wake up readers and writers AND in such a way that makes invariant hold 
  - SIGNAL should contain all signaling => usually by calling release on a semaphore 



## Java

Semaphores are trivial.
Condition interface has await and signal method.