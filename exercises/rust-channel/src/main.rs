use std::thread; 
use std::sync::mpsc;

fn main() {
    // Create a channel
    let (tx, rx) = mpsc::channel();

    // Cloning transmitter of the channel to allow multiple sends 
    let tx1 = tx.clone();

    // Create a new thread
    // Sender is moved here with the move keyword
    thread::spawn(move || {
        // Message
        let s = String::from("Hello from thread");

        // Send to channel
        // Move to send function
        tx.send(s).unwrap();
    });

    // Creates a another thread 
    thread::spawn(move || {
        let s = String::from("Hello from the other thread");

        // Use the other sender to send to the same receiver
        tx1.send(s).unwrap();
    });

    // Receive => which is blocking
    // Do this twice 
    println!("{}", rx.recv().unwrap());
    println!("{}", rx.recv().unwrap());
}
