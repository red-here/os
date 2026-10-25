#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); return 1; }

    if (pid == 0) {
        printf("Child PID=%d, initial PPID=%d\n", getpid(), getppid());
        sleep(3);
        printf("Child PID=%d, PPID after parent exits=%d (orphan demo)\n",
               getpid(), getppid());
        return 0;
    } else {
        printf("Parent PID=%d, child PID=%d\n", getpid(), pid);
        printf("Parent exits now; child may become an orphan.\n");
        /* Parent deliberately does not wait in this branch. */
        sleep(1);
        return 0;
    }
}
/*
To observe a zombie separately, temporarily replace the parent branch with:
    sleep(10);   // child exits, parent stays alive without wait()
Then run `ps -o pid,ppid,state,cmd -p CHILD_PID`; state Z means zombie.
Do not call wait() until after observing the zombie.
*/
