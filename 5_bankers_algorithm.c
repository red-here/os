#include <stdio.h>

int main(void)
{
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0}, safe[10], count = 0;

    printf("Enter number of processes and resource types (max 10 each): ");
    scanf("%d%d", &n, &m);
    if (n < 1 || n > 10 || m < 1 || m > 10)
    {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Enter Allocation matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources (%d values): ", m);
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            if (need[i][j] < 0)
            {
                printf("Error: allocation exceeds maximum.\n");
                return 1;
            }
        }

    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                int possible = 1;
                for (j = 0; j < m; j++)
                    if (need[i][j] > avail[j])
                        possible = 0;
                if (possible)
                {
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    safe[count++] = i;
                    finish[i] = 1;
                }
            }
        }
    }

    if (count == n)
    {
        printf("System is in a SAFE state.\nSafe sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d%s", safe[i], i == n - 1 ? "\n" : " -> ");
    }
    else
    {
        printf("System is in an UNSAFE state; no safe sequence found.\n");
    }
    return 0;
}

// Enter number of processes: 5
// Enter number of resource types: 3

// Enter Allocation matrix:
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// Enter Max matrix:
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3

// Enter Available resources:
// 3 3 2
