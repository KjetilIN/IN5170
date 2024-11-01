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