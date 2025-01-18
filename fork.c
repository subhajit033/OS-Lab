#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork(); // Create a child process

    if (pid < 0)
    {
        // Error in creating process
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("This is the Child process. My PID is: %d\n", getpid());
        printf("My Parent's PID is: %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("This is the Parent process. My PID is: %d\n", getpid());
        printf("I created a child process with PID: %d\n", pid);
    }

    return 0;
}
