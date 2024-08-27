#include <pthread.h>  
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 

// Global lock in C with the pthread library 
pthread_mutex_t lock; 

// Buffer
char *buffer; 

// Thread ids. 
pthread_t thread_id[2]; 

void* reader(void* arg){
    while (1 == 1){
        // Acquire lock
        pthread_mutex_lock(&lock);

        // CS: Read to buffer 
        if (buffer == ""){
            // Read line into buffer
        }

        // Release lock 
        pthread_mutex_unlock(&lock);
    }
    
    return NULL;
}

void* finder(void* arg){
    char *line = "";
    while (1 == 1){
        // Acquire lock
        pthread_mutex_lock(&lock);

        // CS:  Get from buffer and remove data from it 
        line = buffer; 
        buffer = "";

        // Release lock 
        pthread_mutex_unlock(&lock);


        // Find path and print 
    }

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
    
    
    
    // Make the program wait for the thread to stop  
    pthread_join(thread_id[0], NULL); 
    pthread_join(thread_id[1], NULL); 
    pthread_mutex_destroy(&lock); 
  
    return 0; 
}