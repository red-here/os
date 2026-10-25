#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>

int main()
{
    int fd, file;
    char ch;
    int characters = 0, words = 0, lines = 0;
    int inword = 0, last = '\n';
    char result[200];

    // Create two FIFOs
    if (mkfifo("/tmp/fifo1", 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo1");
        return 1;
    }

    if (mkfifo("/tmp/fifo2", 0666) == -1 && errno != EEXIST)
    {
        perror("mkfifo fifo2");
        return 1;
    }

    // Read sentences from Process 1
    fd = open("/tmp/fifo1", O_RDONLY);

    while (read(fd, &ch, 1) > 0)
    {
        characters++;

        if (ch == '\n')
            lines++;

        if (isspace((unsigned char)ch))
            inword = 0;
        else if (!inword)
        {
            words++;
            inword = 1;
        }

        last = (unsigned char)ch;
    }

    close(fd);

    // Count a final line without a newline character
    if (characters > 0 && last != '\n')
        lines++;

    // Save results in a text file
    file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (file == -1)
    {
        perror("output.txt");
        return 1;
    }

    snprintf(result, sizeof(result),
             "Characters: %d\nWords: %d\nLines: %d\n",
             characters, words, lines);

    write(file, result, strlen(result));
    close(file);

    // Send the file contents to Process 1
    fd = open("/tmp/fifo2", O_WRONLY);

    file = open("output.txt", O_RDONLY);

    while (1)
    {
        int n = read(file, result, sizeof(result));

        if (n <= 0)
            break;

        write(fd, result, n);
    }

    close(file);
    close(fd);

    return 0;
}