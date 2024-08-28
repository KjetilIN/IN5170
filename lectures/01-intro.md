# Lecture notes

- Concurrency - doing more than one task at the time
- Can lead to flaws in security 
- Very hard or impossible to test
- Modern languages have concurrent mechanisms 
- Will look into deadlock, fairness. Will also analyze a parallel system.

Course struct: 
- Shared memory with java
- Message passing with Go
- Analyses and Tool Support with Rust 

Two assignments and weekly exercises. 
Exam: 28.11.2024


Books:
- Foundation of Multithreaded, Parallel and distributed systems: 
- Lectures for the last two parts. 

Reading: Chapter 1 of Andrews, slides about Java


## Shared Memory Concurrency 
- Sequential program: one thread has full control of the whole memory 
- Parallel/concurrent program: several threads needs t access and modify the same memory
- If operations can be performed independently then performance may increase 
- `{}` describe conditions before or after a statement 
- Use `:=` to specify reassignment
- Java has `assert` to check such conditions
- JML language can be used to specify more complex condition.
- To specify parallel operations use `||`  
  - `co S1 || S2 || ... || Sn oc`

Threads: 
- Cooperation to obtain a result
- Compete for resources

Synchronization restrict the access of interleaving of parallel processes. 
We will increase the atomicity and mutual exclusion to introduce critical sections which can not be executed concurrency.
Processes may need to wait. 


## Atomic Operations

Java is compiled down to JVL, which is not corresponded to 1-to-1 machine instructions. 
- 4-6 machine code instructions (it depends on the architecture). 

Atomic operation cannot be divided into smaller operations. Either it happens or it does not. 
Assignments are not atomic!


### Example 1

`{x = 0} co x:= x + 1 || x:= x - 1 ox {?}`
- Each statement is 3 operations => read, inc, write
- The order will be the same 

Program Order: two statements are program-ordered if the same thread of program 

Interleaving: .....

- To find the solution we can look at all the different orders of all the interleaving.

ANS:
`{x = 0} co x:= x + 1 || x:= x - 1 ox { -1 <= x <= 1}`

Such a program is random. We cannot predict the value. In reality it is not random because it is dependent on the order of the program. 


- The more process, the more growth.
- You do not want to restrict, because that will make the program less concurrent and will impact performance. 

**Formula for number of executions:**
n - processes
m - atomic operations per process (?)

....

Fine grained atomicity:
- Only the most basic read write operations are atomic.  
- However, non-atomic interactions appear to be atomic. 


**At most once** property: 
x:= e satisfies this: 
- e contains no critical reference
- e contains at most one critical reference and x is not referenced by other processes 



Example:

x, y shared variables, r, s local variables. 

{ x=y=0} co x := x+1 | | y := x+1 oc { x = 1 & ( y = 1 | y = 2 ) }
{ x=y=0} co x := y+1 | | y := x+1 oc { ( x , y ) ∈ { ( 1 , 1 ) , ( 1, 2 ) , ( 2 , 1 ) } }
{ x=y=0} co x := y+1 | | x := y+3 | | y := 1 oc { y = 1 & 1<=x<=4}
{ x=y=0} co r := y+1 | | s := y−1 | | y := 5 oc {?}


## A Minimal Language for concurrency 

Await is used to illustrate basic concurrency without boilerplate from mainstream languages. 

- Standard imperative constructs: sequence (;), assignment, branching, loops
- co .. || .. oc for parallel execution
- < .. > for atomic sections
- await for synchronization

For modularity we can also use process to block a process:

```
process bar1{
    for [i = 1 to n]
        write(i);
}
```

To declare N process: `process barn [i=1 to n]{}`

Use synchronized keyword in Java to assure that they are atomical keyword. 

## Read and Write variables 

V: set of global variables 
W: set of write global variables

Processes without any common global variables are interference free.
- If variables accessed by both process are read-only variables, then it is also interference free. If reading then there are to race conditions. 

## Critical sections and Invariants

You can classify a program with properties: 

- Safety property: program will never reach an undesirable state
- Liveness property: program will eventually reach a desirable state. 
- Termination: all executions are finite
- Partial correctness: if the program terminates it is in a desired state. 
- Total correctness: the program terminates and is partially correct. 


Invariant is a property of the program states, that holds for all reachable states of the program. 
- Does not require final state. 

Invariant types: 
- Strong: all reachable states. 
- Weak invariant: holds for all states where an atomic block starts or ends. 
- loop: holds at the start and end of loop. 
- ......


One can show that a program has weak invariant by:
1. Showing invariant property at the start
2. And that it is for each atomic statement. 

**Dijkstra's dictum:** a test can only show errors, but never prove that a program is correct! 

- `<await(B) S >` where B is a condition, that when is true, will execute the process S. 