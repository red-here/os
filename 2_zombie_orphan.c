#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Child Process
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        sleep(10);

        printf("Child running. New Parent PID: %d\n", getppid());
    }
    else if (pid > 0)
    {
        // Parent Process
        printf("Parent PID: %d\n", getpid());

        sleep(2);

        // CHANGE THIS LINE FOR ZOMBIE / ORPHAN
        exit(0);
    }

    return 0;
}

/*
ZOMBIE DEMONSTRATION:
1. In child, change sleep(10) to sleep(2).
2. In parent, replace exit(0) with:
       sleep(20);
       wait(NULL);
3. During the parent's sleep, check:
       ps -el | grep Z
4. Child terminates first, but parent hasn't called wait() yet.
   Therefore, child becomes a zombie.

ORPHAN DEMONSTRATION:
1. Keep child sleep(10) unchanged.
2. Keep parent exit(0) unchanged.
3. Parent terminates first while child is still running.
4. Child becomes an orphan and gets adopted by a
   system process or configured subreaper.
5. Observe the new PPID printed by the child.
*/
