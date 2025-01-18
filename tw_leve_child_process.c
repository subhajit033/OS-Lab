#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid1 = fork(); // First fork to create the first-level child

    if (pid1 < 0)
    {
        // Error in creating the first child
        perror("First fork failed");
        return 1;
    }

    if (pid1 == 0)
    {
        // First-level child process
        printf("First-level Child Process: My PID is %d\n", getpid());

        // Second fork to create the second-level child inside the first-level child
        pid_t pid2 = fork();

        if (pid2 < 0)
        {
            // Error in creating the second-level child
            perror("Second fork failed");
            return 1;
        }

        if (pid2 == 0)
        {
            // Second-level child process
            printf("Second-level Child Process: My PID is %d, My Parent's PID is %d\n", getpid(), getppid());
        }
        else
        {
            // First-level child process
            printf("First-level Child Process: I created the second-level child with PID %d\n", pid2);
        }
    }
    else
    {
        // Parent process
        printf("Parent Process: My PID is %d, I created the first-level child with PID %d\n", getpid(), pid1);
    }

    return 0;
}
