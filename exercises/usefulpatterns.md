# List of Useful Patterns to remember

## Bounded Buffer with Monitor 

A bounded buffer is an array with limited space.
We use a single counter to keep track of where we are in the array. 
It has N slots. We put data in the buffer when we can, and remove it when there is space. 

Here is the implementation: 

![image](./pattern_images/bounder_buffer_monitor.png)


## Reader and Writer problem with monitor 

Readers and writer problem involves having readers and writers accessing resources. 

Tips: 
- Use variables to keep track of how many readers and writers there are. 
- Define the invariant based on the variables 

![image](./pattern_images/reader_writer_monitor.png)


## Shortest job next with monitor

Allocate resources based on what sources are used. 
See that we queue process based on their time of completion, and then take the shortest job first when we signal. 

![image](./pattern_images/shortest_job_first.png)


## Barber Shop with monitor

Here is a few tips: 
- Use while statements around wait, because we may need to recheck the condition when the process is awaken again
- Increment/decrement only after the while statement (makes a good pattern).
- Consider the invariant and when we should signal the processes 

![image](./pattern_images/barber_monitor.png)