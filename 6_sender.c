
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd1, fd2;
    char str[500];
    char buffer[100];

    // Open FIFO1 for writing
    fd1 = open("fifo1", O_WRONLY);

    printf("Enter sentences (type END to stop):\n");

    while (1)
    {
        fgets(str, sizeof(str), stdin);

        if (strcmp(str, "END\n") == 0)
            break;

        write(fd1, str, strlen(str));
    }

    close(fd1);

    // Open FIFO2 for reading
    fd2 = open("fifo2", O_RDONLY);

    printf("\nResult from Process 2:\n");

    int n;
    while ((n = read(fd2, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, n);
    }

    close(fd2);

    return 0;
}