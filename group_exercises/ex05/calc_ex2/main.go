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
	ret chan<- int 
}

type State struct{
	sum int;
	kind OP;
}

func loop1(ch <-chan Msg, state State){
	for given_msg := range ch{
		switch(given_msg.op){
			case ADD:
				state.sum += given_msg.p1+given_msg.p2
				given_msg.ret<-state.sum;
			case INC:
				state.sum += given_msg.p1
				given_msg.ret<-state.sum
			case STORE:
				state.sum = given_msg.p1
			case DUAL:
				state.kind = DUAL;
			case SNGL:
				state.kind = SNGL;
			default:
				fmt.Println("Unknown OP")
		}
	}

}

func main(){
	input:= make(chan Msg)

	go loop1(input, State{0, 0})

	res := make(chan int)

	input <- Msg{STORE, 2, 0, res}
	input <- Msg{INC, 5, 0, res}

	// Should be 7
	fmt.Println(<-res)
}
