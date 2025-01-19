#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5 // Size of the shared buffer

// Shared buffer and associated variables
int buffer[BUFFER_SIZE];
int count = 0; // Counter to keep track of the number of items in the buffer

// Mutex and condition variables for synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

// Producer function
void *producer(void *arg)
{
    int item;
    while (1)
    {
        item = rand() % 100;        // Generate a random item
        pthread_mutex_lock(&mutex); // Lock the mutex before modifying the buffer

        // Wait if the buffer is full
        while (count == BUFFER_SIZE)
        {
            pthread_cond_wait(&not_full, &mutex);
        }

        // Add item to the buffer
        buffer[count] = item;
        count++;
        printf("Produced: %d\n", item);

        // Signal the consumer that the buffer is not empty
        pthread_cond_signal(&not_empty);

        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sleep(1);                     // Simulate time taken to produce an item
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg)
{
    int item;
    while (1)
    {
        pthread_mutex_lock(&mutex); // Lock the mutex before accessing the buffer

        // Wait if the buffer is empty
        while (count == 0)
        {
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Consume item from the buffer
        item = buffer[count - 1];
        count--;
        printf("Consumed: %d\n", item);

        // Signal the producer that the buffer is not full
        pthread_cond_signal(&not_full);

        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sleep(1);                     // Simulate time taken to consume an item
    }
    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    // Create the producer and consumer threads
    if (pthread_create(&producer_thread, NULL, producer, NULL) != 0)
    {
        perror("Producer thread creation failed");
        return 1;
    }

    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0)
    {
        perror("Consumer thread creation failed");
        return 1;
    }

    // Join the threads (this won't actually happen in this infinite loop example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
