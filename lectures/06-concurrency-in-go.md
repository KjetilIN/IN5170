# Lecture 30. september - Go practical lecture 


### Go basics

- Replace C and C++ => make it easier to use 
- Go prioritizes readability and synchronize communication
  - Rust prioritizes safety 



- Go has structs, not classes
- Inheritance does not exist
- Interfaces as types 

Milner's dictum on static type systems: 
"Well-typed programs cannot go wrong" 


- Interfaces in go contains methods 

- Duck typing => uses the capabilities to identify a type 
  - If it walks like a duck, swims like a duck, then it probably is a duck 
- Go does static duck typing for checking types at compile time 

### Go concurrency 

- Shared memory via global variables
- Use instead message passing for memory sharing 
  - Share memory by communicating 
- Ownership are transferred

Go routines:
- Lightweight threads
- Main method are a go routine, and all go routine created by main method will terminate when main terminate 

Go channels:
- Synchronized and typed
- bidirectional 

- go => start a async go routine
- defer => guarantee that a line of code is executed after the function terminates 


When the main function in go terminates, all go routines are also terminated 


```go
import "fmt"


// Make a channel
chl := make(chan float64)

// Start a go routine 
go send(chl)


func send(chl chan<- float64){
    chl <- 4
}

func receive(ch <-chan float64){
    fmt.Println(<- chl)
}
```

- Reading from a channel is blocking 

WaitGroup is a semaphore used to join activities:

```go
import("fmt", "sync")

func main(){
    messages := []string{"a", "b", "c"}
    var msg string
    var wg sync.WaitGroup

    for _, msg = range messages{
        wg.Add(1)

        go func(m string){
            fmt.Println(m)
            wg.Done()
        }(msg)
    }
}
```


Channel with bounded:
- bounded => limit about of messages
- With two input 
- Note the non blocking read and deadlock 

```go
chl := make(chan string, 2)

chl <- 1 // non blocking!
chl <- 2 
chl <- 3 // Deadlock! 

```

- Writer can close a channel 
- Read a closed channel, gets the default value 
- Use switch statement for allowing the program to do other things while waiting on a channel 

Use a channel as a lock by setting bounding size to one. 

In Go, you need a pointer to change value, else you get a copy of the value. 