#include <stdio.h>
#include <stdlib.h>
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

    if (pid == 0)
    {
        // Child process
        printf("Child process: PID %d is running and will exit now.\n", getpid());
        exit(0); // Child process terminates
    }
    else
    {
        // Parent process
        printf("Parent process: PID %d created a child process with PID %d.\n", getpid(), pid);
        printf("Parent process: Sleeping for 10 seconds to keep child in zombie state.\n");
        sleep(10); // Keep parent alive, child becomes a zombie
        printf("Parent process: Exiting now.\n");
    }

    return 0;
}

// A zombie process is a process that has completed execution but still has an entry in the process table. It occurs when a child process has finished running, but its parent process has not yet terminated it and released its resources. Zombie processes take up system resources and can cause stability issues if not properly handled1

// In this program, we create a child process using fork(). The parent process then sleeps for 10 seconds to keep the child process in a zombie state. The child process terminates immediately after creation. When the parent process exits, the child process becomes a zombie process. You can observe the zombie process using the ps command in the terminal.

// A zombie process occurs when a child process has completed execution, but its parent process has not yet read its exit status using the wait() system call. The child process remains in the "zombie" state until the parent acknowledges its termination.

// Steps to Create a Zombie Process:
// Create a child process using fork().
// Allow the child process to terminate immediately using exit(0).
// Keep the parent process running without calling wait() for the child process.