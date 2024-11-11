# Lecture 11. November 

Session is a sequence of related interactions between at least 2 parties over a certain time frame. 
- A channel os only used for a single session. 
- Linear types describes a session with a single interaction 
- Usage types describes a complex session and distribute interactions using +.


Creating a channel for a session 
```text
(x, y) := make(chan T1, chan T2)
```
- Same "channel" 
- Make sure that T1 and T2 match using duality => if one send, one must receive 
- S (session type) is a non-terminal symbol that are used to defined more advanced types 

Session example: 
```text
chan!int.?bool.0
```
- Send int, receive bool, then terminate 
- Same as usage types, but with different datatype on the channel

Choice - how to continue a session?
- Communicated over the channel
- One part have a choice 

Labels => to allow what branch we use
- internal choice => active part => encoded with a circle with a cross or `+` 
  - Send something 
  - Makes a choice and sends the label to show its choice
- external choice => inactive part => encoded with `&`
  - Receive something 

Example: 

```math
\begin{equation}
    \begin{array}{l}
        \text { !string.?int. } \oplus\left\{\begin{array}{ll}
        \text { accept: !(chan ?string.0). } 0 \\
        \text { reject: } 0
    \end{array}\right\} 
    \end{array}
\end{equation}
```

or another example


```text
?string.!int.&
- accept: ?string.0
- rejected: 0 
```
- For a customer receiving 
- It gets the product name, and then send the price
  - Then we responds based on if the user accepts or rejects the offer.  
- It is passive, i.e receiving
- Shows how to accept and reject string 


Duality:
- Ensure that both parties communicate over the channel with symmetric view. 
- It works sort of like syntax tree 

There are typing rules for choices in a session:
- One rule for both internal and external choices
- For the external rule, we must check all choices, if they type check 


Sub typing for choices:
- Internal choice can have more branches => active choice to never take these branches
- External channels can have less branches => branches are never chosen anyway 

Type soundness for session types:
- Guarantee deadlock freedom 
- Guarantee liveness property 
- A single session never blocks 


Typing environment
Each restricted variable is split into exactly one sub-environment.

$$
\begin{aligned}
\Gamma_1(x)= & \Gamma_2(x)=\left(\Gamma_1+\Gamma_2\right)(x) & & \text { if un }(\Gamma(x)) \\
& \left(\Gamma_1+\Gamma_2\right)(x)=\Gamma_1(x) & & \text { if } \neg \text { un }\left(\Gamma_1(x)\right) \text { and } x \notin \operatorname{dom} \Gamma_2 \\
& \left(\Gamma_1+\Gamma_2\right)(x)=\Gamma_2(x) & & \text { if } \neg \text { un }\left(\Gamma_2(x)\right) \text { and } x \notin \operatorname{dom} \Gamma_1
\end{aligned}
$$


Where $\operatorname{un}(T)$ holds if $T$ is a data type or 0 .

## Multi-party session types

- For more than two parties in a session
- For example:
  - Three parties, where one sends, one checks, and one that receives

Role: a view of an endpoint in the session 
- Now, N endpoints 
- Local types are describes the session from the view of a single role
- Global types give an overview to the whole session 

Global types:
P -> q: p communicates to q. 



## Uniqueness Types

A uniqueness type system ensures that every value (channel etc.) has at most one usable
reference pointing to it.


Calls creates new objects

Pass by reference uses up the type. 

For threads: 
- Exclude race conditions by the type systems, because only one can use the data 