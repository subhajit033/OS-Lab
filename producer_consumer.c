#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

// Shared buffer and related variables
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty;           // Counts empty slots
sem_t full;            // Counts filled slots
pthread_mutex_t mutex; // Ensures mutual exclusion

// Producer function
void *producer(void *arg)
{
    int producer_id = *((int *)arg);

    while (1)
    {
        int item = rand() % 100; // Produce an item

        sem_wait(&empty);           // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer %d: Produced item %d at position %d\n", producer_id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full);              // Signal that a slot is full

        sleep(rand() % 2 + 1); // Simulate production time
    }

    return NULL;
}

// Consumer function
void *consumer(void *arg)
{
    int consumer_id = *((int *)arg);

    while (1)
    {
        sem_wait(&full);            // Wait for a full slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Remove the item from the buffer
        int item = buffer[out];
        printf("Consumer %d: Consumed item %d from position %d\n", consumer_id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty);             // Signal that a slot is empty

        sleep(rand() % 2 + 1); // Simulate consumption time
    }

    return NULL;
}

int main()
{
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS], consumer_ids[NUM_CONSUMERS];

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are initially empty
    sem_init(&full, 0, 0);            // No slots are initially full
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        producer_ids[i] = i + 1;
        if (pthread_create(&producers[i], NULL, producer, &producer_ids[i]) != 0)
        {
            perror("Failed to create producer thread");
            return 1;
        }
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        consumer_ids[i] = i + 1;
        if (pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]) != 0)
        {
            perror("Failed to create consumer thread");
            return 1;
        }
    }

    // Join threads (infinite loop in this example, so not used)
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
