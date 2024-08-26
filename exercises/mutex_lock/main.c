#include <pthread.h>  
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 


// Initialize a global lock in C with the pthread library 
pthread_mutex_t lock; 

// Thread ids. 
pthread_t thread_id[2]; 

// Initialize a counter to keep track of each thread
int counter;

void* worker(void* arg){
    // Acquire lock
    pthread_mutex_lock(&lock);

    // Critical section after lock has been acquired
    counter += 1; 
    printf("\n Job %d has started\n", counter); 

    // Simulate a process that takes long time 
    for(int i = 0; i< 1000000000; i++); 

    printf("\n Job %d has finished\n", counter); 

    // Release lock 
    pthread_mutex_unlock(&lock);

    return NULL;
}


int main(){
    int i = 0; 
    int error; 
    
    // Init the mutex lock 
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    
    // Create threads 
    while (i < 2) { 
        // Create a thread
        error = pthread_create(&(thread_id[i]), NULL, &worker, NULL); 

        if (error != 0) 
            printf("\nThread can't be created");

        i++; 
    } 
    
    // Make the program wait for the thread to stop  
    pthread_join(thread_id[0], NULL); 
    pthread_join(thread_id[1], NULL); 
    pthread_mutex_destroy(&lock); 
  
    return 0; 
}