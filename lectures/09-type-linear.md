# Lecture 28.oct - Type systems for message-passing concurrency 

Data and behavior types: 
- Data over memory
- Behavior for an operation 

Type soundness: 
- Guarantee preservation => well typed expression evaluated ..
- Guarantee Progress => If not terminated, there must be another step 

There is a typing rule for channels, both send and receive 

Sub typing channels based on their operations

Weakening rule => allows to make type less specific by changing the environment 
- Cannot apply this rule to give a channel the right operation


## Linear Types

Linearity: the system do not prevent the channels from being used to little or to often
- We want to define a channel that for example only be used once

Note that:
```text
chan ?n, !m, 
```
- !0 would mean not send
- !1 means only one message would receive 
- ?0, !0 => channel is not usable 


Typing environment can be split into different typing environments. 
- For example splitting a channel into two environments
- Splitting the channel allows for more expressing with more axioms. 

Channels are unrestricted if all contained channels have n = 0, m = 0 - i.e unusable channels


## Usage Types 

Linear types are not enough to describe protocols. 

Usage describes the structure of all allowed actions on a channel. For example:
- Receive, send, parallel usage, alternative (course does not consider infinite usage denotation)
- Denoted with U 
- For example:
  - ?.!.0 => firs receive, then receive and the i cannot use the channel
  - ?.0&!.0 => send or receive, no other operation
  - ?.0 + !.0 => use for sync once