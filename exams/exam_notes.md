# Semaphores

- Manipulated by two atomic operations
  - P : wait for signal
    - Wait until greater than zero and decrease value by one 
    - Guaranteed that you only have access when P is successful (and initial value 1)
  - V: Signal an event, release
    - Increase the value by one 

Useful way to think about what the initial value of a semaphore means:
- 0: "Wait for someone else to give permission"
- N: "Here are N permits to use right away"

```text
# Create semaphore 
sem s; // Init value 0 
sem s := 1; 
sem s[4] := ([4] 1) 
```
Example of usage:
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

Split semaphores: when the sum of all semaphores is equal to 1
Useful for: 
- Turn-taking problems: such as producer consumer, or the order of operation is important (i.e bee and bear)


# Concurrency Evaluation Cheat Sheet

## 1. Mutual Exclusion
Mutual exclusion ensures that only one process or thread accesses a critical section at a time.

**What to Look For:**
- **Locks**: Check if locks are correctly used around critical sections.
- **Atomic Operations**: Ensure critical actions that require exclusive access are atomic (i.e., non-interruptible).
- **Data Integrity**: Look for any instances where shared data could be accessed by multiple threads simultaneously, leading to inconsistency.

**How to Solve:**
- **Mutex Locks**: Use mutex locks (e.g., `pthread_mutex_lock`) around critical sections.
- **Semaphores**: Use semaphores to limit access when multiple instances are acceptable but restricted (e.g., binary semaphore for binary mutual exclusion).

## 2. Absence of Deadlock
Deadlock occurs when two or more threads are waiting on each other, causing all threads to halt.

**What to Look For:**
- **Circular Wait**: Identify any circular dependency where processes hold resources while waiting for others.
- **Resource Acquisition Order**: Check if processes acquire resources in different orders.
- **Hold and Wait**: See if threads hold onto resources while waiting to acquire others.

**How to Solve:**
- **Resource Ordering**: Impose a strict order on resource acquisition to avoid circular dependencies.
- **Timeouts**: Implement timeouts for lock acquisition, allowing threads to release held resources and retry.
- **Avoid Hold-and-Wait**: Release all held resources if a thread cannot acquire all needed resources immediately.

## 3. Absence of Unnecessary Delay (2 points)
Unnecessary delay means a process that could proceed is blocked without reason, reducing system efficiency.

**What to Look For:**
- **Excessive Locking**: Identify cases where resources remain locked longer than needed.
- **Blocking Calls**: Check for blocking calls that might hold up threads unnecessarily (e.g., waiting on conditions when not needed).
- **Long Critical Sections**: Critical sections that take too long might prevent other threads from proceeding.

**How to Solve:**
- **Minimize Critical Sections**: Reduce the scope of locks so critical sections are as short as possible.
- **Non-blocking Synchronization**: Use non-blocking algorithms where possible, like lock-free or wait-free techniques.
- **Condition Variables**: Use condition variables to wake up threads only when they have work to do, reducing unnecessary waiting.

## 4. Fairness
Fairness ensures that all threads get a fair chance to execute, without starvation or priority inversion.

**What to Look For:**
- **Starvation**: Check if any thread or process is indefinitely delayed in accessing the resource.
- **Priority Inversion**: Look for cases where a lower-priority thread is holding a resource needed by a higher-priority thread.
- **Balanced Access**: Ensure that the same thread or process does not consistently access the critical section over others.

**How to Solve:**
- **Fair Locks**: Use fair locking mechanisms (like `ReentrantLock(true)` in Java) that serve threads in FIFO order.
- **Priority Inheritance**: Implement priority inheritance to temporarily raise the priority of a low-priority thread holding a resource needed by a higher-priority thread.
- **Balanced Scheduling**: Use fair scheduling algorithms like round-robin or proportional share to distribute CPU time fairly among threads.