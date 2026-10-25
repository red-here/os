#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    int p1[2], p2[2];
    pid_t pid;
    char filename[100];
    char buffer[1024];
    int fd, n;

    pipe(p1);
    pipe(p2);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid > 0)
    {
        // Parent process
        close(p1[0]);
        close(p2[1]);

        printf("Enter file pathname: ");
        scanf("%99s", filename);

        write(p1[1], filename, strlen(filename) + 1);
        close(p1[1]);

        printf("\nFile contents:\n");

        while ((n = read(p2[0], buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, n);
        }

        close(p2[0]);
        wait(NULL);
    }
    else
    {
        // Child process
        close(p1[1]);
        close(p2[0]);

        read(p1[0], filename, sizeof(filename));
        close(p1[0]);

        fd = open(filename, O_RDONLY);

        if (fd == -1)
        {
            char msg[] = "Error: Cannot open file.\n";
            write(p2[1], msg, strlen(msg));
            close(p2[1]);
            exit(1);
        }

        while ((n = read(fd, buffer, sizeof(buffer))) > 0)
        {
            write(p2[1], buffer, n);
        }

        close(fd);
        close(p2[1]);
        exit(0);
    }

    return 0;
}