#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort - Ascending Order
void bubbleSortAsc(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Bubble Sort - Descending Order
void bubbleSortDesc(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] < arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int n, i;
    int arr[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        return 1;
    }

    else if (pid == 0)
    {
        // Child Process
        printf("\nChild Process (PID: %d)\n", getpid());

        bubbleSortDesc(arr, n);

        printf("Child Sorted Array (Descending): ");

        for (i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }

        printf("\n");

        exit(0);
    }

    else
    {
        // Parent Process
        printf("\nParent Process (PID: %d)\n", getpid());

        bubbleSortAsc(arr, n);

        printf("Parent Sorted Array (Ascending): ");

        for (i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }

        printf("\n");

        wait(NULL);

        printf("Parent: Child process completed.\n");
    }

    return 0;
}
