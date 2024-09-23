# Lecture 23. september - Message passing and Channels 

- We have before handled shared memory concurrency
- This is the second part of the course
- Concurrent programming: two or more processes work together to perform a task. 
  - Both processed have access to shared memory
  - In DS. we don't have shared memory, and we need messages to pass information between processes. 


## Distributed Systems 

- Each process have their own memory
- Communication over network 
- Example(s):
  - Cloud computing: a lot of computing power, where the task is distributed
- SMP - Symmetric multiprocessing 


### Message passing: 

- Sending message to a process
- Synchronize and async message passing 
  - With sync. the sender blocks after sending.
    - This is a blocking procedure.
    - No memory buffer is required
    - Concurrency is reduced
    - Programs can deadlock
  - With async. the sender does not block after sending
    - Memory buffer  is required
    - Have more concurrency 
    - Less prone to deadlock 


### Channels 

- Abstraction of a communication network fir one-way communication between two entities. 
- Unbounded FIFO queue
- Assume atomic access, error-free and typed.

With Await language: 
- chan(type1 ...)
- send() => non-blocking messages is sent and process continues execution 
- receive() => Blocking review until received 
- empty() => if channel is empty

Note:
- Two processes both sending, can lead to any order of received. 


Channels act like a semaphore:
- send = V
- receive = P 
- Number of messages in queue = value of semaphore 



#### Filters - one-way interaction filter example: 
- Gets incoming messages on input channels, and output. 
- We can think of this as a function 
 
Sort filter: 
- Get N inputs 
- Want the N element to be sorted 
- Signaling value at the end of the channel output, so that we know no more values 

Filtering with two input channels: 
- Output sorted list again. (Merge sort)
- Use EOS to mark end of input. 
- Merge predicate:
  - All channels must be empty
  - Next in sent must be EOS
  - For all elements, we assume the sended values are sorted

```text
chan in1(int), in2(int), out(int);

process Merge{
    int v1, v2;

    # Receive the two first values
    receive in1(v1);
    receive in2(v2);

    # Loop while there is input from both channels 
    while (v1 != EOS and v2 != EOS){
        if(v1 <= v2){
            send out(v1);
            receive in1(v1);
        }else{
            send out(v2);
            receive in1(v2);
        }
    }


    # While first channel has input 
    while(v1 != EOS){
        send out(v1);
        receive in1(v1);
    }

    # While second channel has input 
    while (v2 != EOS){
        send out(v2);
        receive in1(v2);
    }


    send out(EOS);

}

```


How to communicate the result back to the channel?
- Bi-directional channel 


#### Client-Server using messages

- Server: handle request from client
- Client send request to server, and retrieves the result

With known amount of clients: 

```text
chan request(int, T1); # Client ID + arguments for operations 
chan reply[n](T2); # Results of the operation 
```


#### Monitor implementation of message passing 

- Classical monitor with procedures
- Active monitor => 
- Passive monitor => 

Channel with type:

```text
type op_kind = enum(ACQUIRE, release);

# Channel with the type
chan request(int clientID, op_kind kind);
```


TODO: add final notes from lecture 