// EXAM 2023: Problem 14

use std::thread;

fn f(write_ref: &mut Vec<i32>){
    write_ref[0] = 0;
}

fn g(read_ref : &Vec<i32>){
    println!("{}", read_ref[0])
}

fn main(){
    let mut vec = vec![1,2,3];        // Owner: vec
    f(&mut vec);                       // Owner: vec
    let handle = thread::spawn(move || g(&vec));  // Owner: transferred to the spawned thread's closure
    handle.join().unwrap();
}                                       