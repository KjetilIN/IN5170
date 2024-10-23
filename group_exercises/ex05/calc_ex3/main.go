package main


import "fmt"


func f(fut chan<- int, p1 int, p2 int){
	sum := p1+p2
	for{
		fut<-sum
	}
}

func main(){
	ch := make(chan int)

	go f(ch, 1, 2)

	// Should work with any number of reads 
	fmt.Println(<-ch)
	fmt.Println(<-ch)
}