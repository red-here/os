#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
    int p1, p2, ch = 0, words = 0, lines = 0;
    char str[100];

    mkfifo("f1", 0666);
    mkfifo("f2", 0666);

    p1 = open("f1", O_RDONLY);

    while (1)
    {
        read(p1, str, sizeof(str));

        if (strcmp(str, "END\n") == 0)
            break;

        ch += strlen(str);
        lines++;

        for (int i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == ' ' || str[i] == '\n')
                words++;
        }
    }

    words++;

    close(p1);

    FILE *fp = fopen("result.txt", "w");

    fprintf(fp, "Characters = %d\n", ch);
    fprintf(fp, "Words = %d\n", words);
    fprintf(fp, "Lines = %d\n", lines);

    fclose(fp);

    fp = fopen("result.txt", "r");
    p2 = open("f2", O_WRONLY);

    while (fgets(str, sizeof(str), fp))
        write(p2, str, strlen(str));

    fclose(fp);
    close(p2);

    return 0;
}
