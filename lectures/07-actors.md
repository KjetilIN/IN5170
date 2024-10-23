# Lecture 14.oct - Actors, Active objects and Async. communication 

## Actors

- Channels need complex typing disciplines 
- Actors sends messages between objects
- Actors communicate between other actors 
- We know how we are talking to 
  - Actors know the other actors it is sending messages it sends 
- A programming concept implement some models

Combines topics: 
- Active monitor
- objects and encapsulation
- race-free (no race condition on shared state) 

Idea is to decouple communication and control 
Actors reacts to incoming messages.

We can think of actors as an object that can only communicate asynchronous.  

> Causality is when there is a guarantee of ordering of messages 

Example of actor: 
- Erlang implementation of matching messages to a Pub-Sub server 
- Erlang keeps state in the recursive call

## Futures and promises

- Handling return values from actors 
- We need to identify callback messages 
- Solutions: futures => a mailbox for results are stored at specific addresses 

A future is a handle for the caller of a process that will contain the result of value once computed. 
- Future is blocking. (The thread getting the value is blocked)
- A promise is a future that which is not clear who is computes it


## Active Objects 

- Messages between objects with cooperative scheduling
- Active object is a implicit message server that communicates only asynchronous
  - One process/thread per objects
  - Implicit queue of tasks (Actors does not have an implicit queue)
  - Cooperative concurrency 



## Erlang example: 


```erlang
runServer(Subs) ->
  receive
    {sub, from} -> runServer(Subs + from);
    {publish, value} -> 
      for(id in Subs) 
        id!{value};
      runServer(Subs);
    _ -> runServer(Subs);

Server{
  start() -> spawn(func() -> runServer([]));
}

Client{
  start() -> Server!{sub, self}, Server!{publish, 10};
}
```