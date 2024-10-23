package main

import "fmt"


type OP int

const(
	ADD OP = 0
	INC OP = 1
	STORE OP = 2
	DUAL OP = 3
	SNGL OP = 4
)

type Msg struct{
	op OP
	p1 int
	p2 int 
	ret chan int 
}

type State struct{

}

func loop1(ch chan Msg, state State){

}

func main(){
	input:= make(chan Msg)

	go loop1(input, State{})

	res := make(chan int)

	input <- Msg{STORE, 2, 0, res}
	input <- Msg{INC, 5, 0, res}

	// Should be 7
	fmt.Println(<-res)
}
