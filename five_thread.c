#include <stdio.h>
#include <pthread.h>

// Function that will be executed by each thread
void *thread_function(void *arg)
{
    int thread_num = *((int *)arg); // Extract the thread number
    printf("Hello from Thread %d!\n", thread_num);
    return NULL;
}

int main()
{
    pthread_t threads[5]; // Array to hold thread identifiers
    int thread_args[5];   // Array to hold arguments for each thread

    // Create five threads
    for (int i = 0; i < 5; i++)
    {
        thread_args[i] = i + 1; // Set thread argument as the thread number
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0)
        {
            perror("Thread creation failed");
            return 1;
        }
    }

    // Wait for all threads to finish execution
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
