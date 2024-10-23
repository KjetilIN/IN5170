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
				if state.kind == SNGL{
					given_msg.ret<-given_msg.p1+given_msg.p2;
				}
			case INC:
				if(state.kind == DUAL){
					given_msg.ret<-state.sum + given_msg.p1
				}
			case STORE:
				if state.kind == SNGL{
					state.sum = given_msg.p1
				}
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

	go loop1(input, State{})

	res := make(chan int)

	input <- Msg{STORE, 2, 0, res}
	input <- Msg{INC, 5, 0, res}

	close(input)

	// Should be 7
	fmt.Println(<-res)
}
