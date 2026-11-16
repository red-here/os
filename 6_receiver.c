
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

int main()
{
    int fd1, fd2;
    char buffer[100];
    int characters = 0, words = 0, lines = 0;
    int inword = 0, n;
    char last = '\0';

    // Open FIFO1 for reading
    fd1 = open("fifo1", O_RDONLY);

    while ((n = read(fd1, buffer, sizeof(buffer))) > 0)
    {
        for (int i = 0; i < n; i++)
        {
            char ch = buffer[i];

            characters++;
            last = ch;

            if (ch == '\n')
                lines++;

            if (isspace((unsigned char)ch))
                inword = 0;
            else if (inword == 0)
            {
                words++;
                inword = 1;
            }
        }
    }

    close(fd1);

    if (characters > 0 && last != '\n')
        lines++;

    // Write results into file
    FILE *fp = fopen("output.txt", "w");

    fprintf(fp, "Characters: %d\n", characters);
    fprintf(fp, "Words: %d\n", words);
    fprintf(fp, "Lines: %d\n", lines);

    fclose(fp);

    // Read contents of file
    fp = fopen("output.txt", "r");

    // Open FIFO2 for writing
    fd2 = open("fifo2", O_WRONLY);

    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        write(fd2, buffer, n);
    }

    fclose(fp);
    close(fd2);

    return 0;
}
