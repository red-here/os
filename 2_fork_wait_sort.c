#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void sort(int a[], int n)
{
    int i, j, t;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1])
            {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
}
void print_array(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
int main(void)
{
    int a[100], n, i;
    pid_t pid;

    printf("How many integers (1-100)? ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 100)
        return 1;
    printf("Enter integers: ");
    for (i = 0; i < n; i++)
        if (scanf("%d", &a[i]) != 1)
            return 1;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild (PID %d) sorting: ", getpid());
        sort(a, n);
        print_array(a, n);
        _exit(0);
    }
    else
    {
        printf("Parent (PID %d) sorting: ", getpid());
        sort(a, n);
        print_array(a, n);
        wait(NULL);
        printf("Parent: child finished; wait() returned.\n");
    }
    return 0;
}
