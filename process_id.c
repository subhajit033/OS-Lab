#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = getpid();   // Get the Process ID (PID)
    pid_t ppid = getppid(); // Get the Parent Process ID (PPID)

    printf("Process ID (PID): %d\n", pid);
    printf("Parent Process ID (PPID): %d\n", ppid);

    return 0;
}
