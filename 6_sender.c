#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int p1, p2;
    char str[100], result[200];

    p1 = open("f1", O_WRONLY);

    printf("Enter sentences (END to stop):\n");

    while (1)
    {
        fgets(str, 100, stdin);
        write(p1, str, strlen(str) + 1);

        if (strcmp(str, "END\n") == 0)
            break;
    }

    close(p1);

    p2 = open("f2", O_RDONLY);

    read(p2, result, sizeof(result));
    printf("\nResult:\n%s", result);

    close(p2);

    return 0;
}
