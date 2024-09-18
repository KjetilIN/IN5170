#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 20    // Number of bees
#define H 100   // Pot capacity (number of honey portions)

int pot_count = 0;          // Current number of honey portions in the pot
sem_t pot_mutex;            // Semaphore for mutual exclusion on the pot
sem_t pot_full;             // Semaphore to signal the bear when the pot is full

void* bee(void* arg) {
    int id = *(int*)arg;
    while (1) {
        sem_wait(&pot_mutex);  // Wait to access the pot

        if (pot_count < H) {
            pot_count++;
            printf("Bee %d added honey. Pot count: %d\n", id, pot_count);

            // If this bee fills the pot, signal the bear
            if (pot_count == H) {
                printf("Bee %d filled the pot! Waking the bear.\n", id);
                sem_post(&pot_full);  // Signal the bear that the pot is full
            }
        }

        sem_post(&pot_mutex);  // Release the pot mutex
        sleep(1);              // Simulate the time taken by the bee to gather honey
    }
    return NULL;
}

void* bear(void* arg) {
    while (1) {
        sem_wait(&pot_full);  // Wait for the pot to be full

        sem_wait(&pot_mutex);  // Lock the pot to eat honey
        printf("Bear is eating all the honey...\n");
        pot_count = 0;         // Reset the pot after eating
        sleep(2);              // Simulate the bear eating time
        printf("Bear has finished eating. Pot is empty.\n");
        sem_post(&pot_mutex);  // Release the pot mutex for the bees to continue

        // The bear automatically goes back to sleep and waits for the pot to be filled again
    }
    return NULL;
}

int main() {
    pthread_t bees[N];
    pthread_t bear_thread;
    int bee_ids[N];

    // Initialize the semaphores
    sem_init(&pot_mutex, 0, 1);  // Binary semaphore for mutual exclusion (mutex)
    sem_init(&pot_full, 0, 0);   // Semaphore for signaling when the pot is full

    // Create the bee threads
    for (int i = 0; i < N; i++) {
        bee_ids[i] = i + 1;
        pthread_create(&bees[i], NULL, bee, &bee_ids[i]);
    }

    // Create the bear thread
    pthread_create(&bear_thread, NULL, bear, NULL);

    // Wait for threads (although in this infinite loop, the program doesn't end)
    for (int i = 0; i < N; i++) {
        pthread_join(bees[i], NULL);
    }
    pthread_join(bear_thread, NULL);

    // Destroy the semaphores
    sem_destroy(&pot_mutex);
    sem_destroy(&pot_full);

    return 0;
}
