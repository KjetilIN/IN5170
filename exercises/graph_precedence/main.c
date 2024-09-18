#include <pthread.h>  
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <semaphore.h>


// Thread ids. 
pthread_t thread_id[5]; 

// Initialize a counter to keep track of each thread
int counter;

// Semaphores 
sem_t t1_done;
sem_t t2_done;
sem_t t3_done;
sem_t t4_done;


// Processes 

void* t1(void* arg){
    // No waiting just start
    printf("T1 task executed\n");    

    // Signal twice
    // This will allow T2 and T3 to run concurrently 
    sem_post(&t1_done);
    sem_post(&t1_done);
    return NULL;
}

void* t2(void* arg){
    // Wait on T1 for a permit 
    sem_wait(&t1_done);
    printf("T2 task executed\n");

    // Notify that t2 is done
    sem_post(&t2_done);
    return NULL;
}

void* t3(void* arg){
    // Wait for T1 for a permit
    sem_wait(&t1_done);

    printf("T3 task executed\n");

    // Notify t3 is done
    sem_post(&t3_done);
    return NULL;
}

void* t4(void* arg){
    // Wait for t2 to be done 
    sem_wait(&t2_done);
    printf("T4 task executed\n");
    
    // Notify t4 is done
    sem_post(&t4_done);
    return NULL;
}

void* t5(void* arg){
    // Wait until T3 and T4 to be done
    sem_wait(&t3_done);
    sem_wait(&t4_done);
    printf("T5 task executed\n");
    return NULL;
}

/**
 * This program will ensure the following constraints
 * - 5 nodes. 
 * - T1 first
 * - T2 and T3 can run concurrently
 * - T4 must be after T2
 * - T5 must be after T4 and T3
 * 
 * @brief Program for Exercise 1 in Group Session 3
 * 
 * @return int status for execution 
 */

int main(){

    int error; 

    // Init semaphores
    sem_init(&t1_done, 0, 0);
    sem_init(&t2_done, 0, 0);
    sem_init(&t3_done, 0, 0);
    sem_init(&t4_done, 0, 0);
    
    // Create threads 
    error = pthread_create(&(thread_id[0]), NULL, &t1, NULL); 
    error = pthread_create(&(thread_id[1]), NULL, &t2, NULL);
    error = pthread_create(&(thread_id[2]), NULL, &t3, NULL);
    error = pthread_create(&(thread_id[3]), NULL, &t4, NULL);
    error = pthread_create(&(thread_id[4]), NULL, &t5, NULL);

    if (error != 0) 
        printf("\nThread can't be created");

    
    // Make the program wait for the thread to stop  
    pthread_join(thread_id[0], NULL); 
    pthread_join(thread_id[1], NULL); 
    pthread_join(thread_id[2], NULL); 
    pthread_join(thread_id[3], NULL); 
    pthread_join(thread_id[4], NULL);


    // Destroy semaphores
    sem_destroy(&t1_done);
    sem_destroy(&t2_done);
    sem_destroy(&t3_done);
    sem_destroy(&t4_done); 
  
    return 0; 
}