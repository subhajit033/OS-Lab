#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork(); // Create a child process

    if (pid == 0)
    { // Child process
        for (int i = 0; i < 5; i++)
        {
            printf("Child Process PID %d - Message %d\n", getpid(), i + 1);
            sleep(1); // Sleep for 1 second to simulate time-sharing
        }
    }
    else if (pid > 0)
    { // Parent process
        for (int i = 0; i < 5; i++)
        {
            printf("Parent Process PID %d - Message %d\n", getpid(), i + 1);
            sleep(1); // Sleep for 1 second to simulate time-sharing
        }
    }

    return 0;
}
