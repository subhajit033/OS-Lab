
// An orphan process is a process whose parent process has terminated or exited, but the orphan process is still running. In Unix-like systems, orphan processes are adopted by the init process (PID 1).

// To create an orphan process:

// A child process is created using fork().
// The parent process is made to exit before the child process, so the child becomes an orphan.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork(); // Create a child process

    if (pid < 0)
    {
        // Error in creating process
        perror("Fork failed");
        return 1;
    }

    if (pid > 0)
    {
        // Parent process exits, making the child an orphan
        printf("Parent process: My PID is %d. I am exiting now.\n", getpid());
        exit(0); // Parent exits
    }
    else
    {
        // Child process
        sleep(2); // Give parent time to exit
        printf("Child process: My PID is %d, My Parent's PID was %d. I am now an orphan.\n", getpid(), getppid());
        sleep(5); // Keep the child alive to observe the orphan process
    }

    return 0;
}
