#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd, n;
    char text[200];
    char result[500];

    // Send sentences to Process 2
    fd = open("/tmp/fifo1", O_WRONLY);

    printf("Enter sentences (type END to finish):\n");

    while (fgets(text, sizeof(text), stdin))
    {
        if (strcmp(text, "END\n") == 0 ||
            strcmp(text, "END") == 0)
            break;

        write(fd, text, strlen(text));
    }

    close(fd);

    // Receive results from Process 2
    fd = open("/tmp/fifo2", O_RDONLY);

    printf("\nResults received from Process 2:\n");

    while ((n = read(fd, result, sizeof(result) - 1)) > 0)
    {
        result[n] = '\0';
        printf("%s", result);
    }

    close(fd);

    return 0;
}