#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

// Shared resource
int shared_data = 0;

// Mutex and condition variables for synchronization
pthread_mutex_t read_mutex = PTHREAD_MUTEX_INITIALIZER;    // For reading
pthread_mutex_t write_mutex = PTHREAD_MUTEX_INITIALIZER;   // For writing
pthread_cond_t read_condition = PTHREAD_COND_INITIALIZER;  // For readers waiting
pthread_cond_t write_condition = PTHREAD_COND_INITIALIZER; // For writers waiting

int readers_count = 0; // Number of readers currently reading

// Reader thread function
void *reader(void *arg)
{
    int reader_id = *((int *)arg);

    while (1)
    {
        pthread_mutex_lock(&read_mutex); // Lock the read mutex

        // Wait if a writer is writing (ensure no writer writes when readers are reading)
        while (readers_count == -1)
        {
            pthread_cond_wait(&read_condition, &read_mutex);
        }

        readers_count++;                   // Increment the number of readers
        pthread_mutex_unlock(&read_mutex); // Unlock the read mutex

        // Read the shared data
        printf("Reader %d: Read shared data = %d\n", reader_id, shared_data);

        pthread_mutex_lock(&read_mutex); // Lock the read mutex again

        readers_count--; // Decrement the number of readers
        if (readers_count == 0)
        {
            pthread_cond_signal(&write_condition); // Signal any waiting writer
        }

        pthread_mutex_unlock(&read_mutex); // Unlock the read mutex

        sleep(1); // Simulate reading time
    }

    return NULL;
}

// Writer thread function
void *writer(void *arg)
{
    int writer_id = *((int *)arg);

    while (1)
    {
        pthread_mutex_lock(&write_mutex); // Lock the write mutex

        // Wait for all readers to finish and ensure no readers are active
        pthread_mutex_lock(&read_mutex);
        while (readers_count > 0)
        {
            pthread_cond_wait(&write_condition, &read_mutex);
        }

        // Set readers_count to -1 to indicate a writer is writing
        readers_count = -1;

        pthread_mutex_unlock(&read_mutex); // Unlock the read mutex

        // Write to the shared resource
        shared_data++;
        printf("Writer %d: Wrote shared data = %d\n", writer_id, shared_data);

        pthread_mutex_unlock(&write_mutex); // Unlock the write mutex

        // Signal all waiting readers that they can read again
        pthread_cond_broadcast(&read_condition);

        sleep(2); // Simulate writing time
    }

    return NULL;
}

int main()
{
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++)
    {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0)
        {
            perror("Reader thread creation failed");
            return 1;
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0)
        {
            perror("Writer thread creation failed");
            return 1;
        }
    }

    // Join the threads (in a real program, this might not terminate, as it's an infinite loop)
    for (int i = 0; i < NUM_READERS; i++)
    {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++)
    {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
