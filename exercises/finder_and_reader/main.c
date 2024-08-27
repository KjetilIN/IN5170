#define _GNU_SOURCE
#include <pthread.h>  
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h> 
#include <string.h>

// Global lock in C with the pthread library 
pthread_mutex_t lock; 

// Buffer
char buffer[1024];

// Pattern that we are looking for 
char *pattern = "oil";

// File
FILE* file;

// Thread ids. 
pthread_t thread_id[2]; 

void* reader(void* arg){
    char* line = NULL; 
    size_t len = 0;
    ssize_t read;

    printf("Reader thread started\n");
    while ((read = getline(&line, &len, file)) != -1){
        // Acquire lock
        pthread_mutex_lock(&lock);

        printf("Line from reader: %s", line);

        // CS: Read to buffer 
        if (buffer[0] == '\0'){  // Correct comparison
            strcpy(buffer, line);
        }

        // Release lock 
        pthread_mutex_unlock(&lock);

        usleep(100);  // To avoid tight loop
    }

    // Buffer is empty. Acquire lock to tell end of file (EOF)
    pthread_mutex_lock(&lock);
    buffer[0] = EOF; 
    pthread_mutex_unlock(&lock);

    printf("Reader thread stopped\n");

    // Free the line pointer 
    free(line);

    return NULL;
}

void* finder(void* arg){
    char* line = NULL; 

    printf("Finder thread started\n");

    while (1){
        // Acquire lock
        pthread_mutex_lock(&lock);

        // CS:  Get from buffer and remove data from it 
        if (buffer[0] != '\0' && buffer[0] != EOF) {
            line = strdup(buffer); 
            buffer[0] = '\0';  // Clear the buffer
        }

        if (buffer[0] == EOF) {
            pthread_mutex_unlock(&lock);
            break;
        }

        // Release lock 
        pthread_mutex_unlock(&lock);

        // Compare and check for the pattern 
        if (strstr(line, pattern) != NULL) {
            printf("Pattern found: %s", line);  // Print line, not buffer
        }
    }

    printf("Finder thread stopped\n");

    return NULL;
}


int main(){
    int error; 
    
    // Init the mutex lock 
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n Mutex init has failed\n"); 
        return 1; 
    } 

    // Open and read the file 
    file = fopen("cheap_oil.txt", "r");
    if (file == NULL){
        printf("Was not able to open file");
        return 1; 
    }

    // Create threads
    error = pthread_create(&(thread_id[0]), NULL, &reader, NULL); 
    if (error != 0){
        printf("Could not create reader thread");
        return 1; 
    }
    
    error = pthread_create(&(thread_id[1]), NULL, &finder, NULL); 
    if (error != 0){
        printf("Could not create finder thread");
        return 1; 
    }
    
    // Make the program wait for the thread to stop  
    pthread_join(thread_id[0], NULL); 
    pthread_join(thread_id[1], NULL); 
    pthread_mutex_destroy(&lock); 


    // Mark file pointer to throw 
    fclose(file);
  
    return 0; 
}
