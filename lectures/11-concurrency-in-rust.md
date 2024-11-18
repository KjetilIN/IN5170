# Lecture 18.nov - Concurrency in Rust 

- Rust and Go have native implementations of concurrent systems
- RAII => Resource allocation is initialization. 
- RBMM => Region/Scope Based memory management (RBMM)
  - RAII often refer to RBMM


Rust uses ownership to keep track of memory without GC
- Variables are owned by a single variable
- Only one owner at the time 
- When owner goes out of scope, the value is dropped/freed 

```rust
let a = vec![1, 2, 3]; // A is owner
let b = a; // Move happened here, A can no longer be used because of the move
```

- We can copy a primitive value or a value that has the `Copy` trait
  - Must have known size at compile time
- Then a move will work fine!
- Linearity is considered with respect to move
- `clone()` => create new data
  - Not very memory efficient


- Rust requires to explicit that our variable is mutable:
```rust
let mut var = 4; // Mutable variable 
```

- Rust thinks ownership as borrowing something in real life: you usually give it back 
- We can specify a reference to the variable => this is how we borrow

References:
- Mutable or immutable references 
- Only one immutable reference is allowed in Rust 

Lifetimes: 
- Variables has lifetimes
- They are limited to their scope => out of scope leads to de-allocation of the variable. 
- "borrowed but does not live long enough" => when we use a borrowed value that is dropped 


Channels in Rust: 
- Rust has channels
- Multiple producer, single consumer channel => `mpsc::channel`


Thread example:
```rust
use std::thread; // STD thread implementation 


fn main(){
    // Create a new thread 
    let handle = thread::spawn( || {
        println!("Hello");
    });

    // Wait for the thread to be finished
    handle.join().unwrap();
}
```


AtomicUsize => atomic operations on usize
Ordering => memory ordering 
Arc => atomic reference counter


Example: 
```rust
// Atomic usize with a reference counter
// Here is an index
let idx = Arc::new(AtomicUsize::new(0));

// THREAD OPERATION THAT CHANGES THE INDEX

if idx.load(Ordering::SeqCst) < data.len(){
    // Index is valid, we can use it to get data 

    // DATA RACE CAN STILL OCCUR WHEN WE SHARE BETWEEN THREADS
}
```