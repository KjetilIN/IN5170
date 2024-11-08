package main

import (
    "fmt"
    "time"
)

func main() {
    buf := make(chan int, 1)
    turn1 := make(chan bool, 1)
	turn2 := make(chan bool, 1)

	// Set turn to 1s turn
	turn1<-true;

    go Producer1(buf, turn1, turn2)
    go Producer2(buf, turn2, turn1)
    go Consumer(buf)

    // Wait for the program to finish
    select {}
}

func Producer1(buf chan<- int, turn1 <-chan bool, turn2 chan<- bool) {
    for {
        // Wait for Producer1's turn
        <-turn1

        // Write to the buffer
        buf <- 1

        // Signal that it's Producer2's turn
        turn2 <- false
    }
}

func Producer2(buf chan<- int, turn2 <-chan bool, turn1 chan<- bool) {
    for {
        // Wait for Producer2's turn
        <-turn2

        // Write to the buffer
        buf <- 2

        // Signal that it's Producer1's turn
        turn1 <- true
    }
}

func Consumer(buf <-chan int) {
    for {
        // Read from the buffer
        value := <-buf
        fmt.Println("Consumed value:", value)

        // Simulate some processing time
        time.Sleep(50 * time.Millisecond)
    }
}