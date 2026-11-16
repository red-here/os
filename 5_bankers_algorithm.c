
#include <stdio.h>

int main()
{
    int n, m;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0};
    int safe[10], count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Maximum Matrix
    printf("Enter Maximum Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Available Resources
    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Display Need Matrix
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    // Banker's Safety Algorithm
    while (count < n)
    {
        int found = 0;

        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int j;

                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                        break;
                }

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0)
            break;
    }

    // Display Safe Sequence
    if (count == n)
    {
        printf("\nSystem is in SAFE STATE\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++)
            printf("P%d ", safe[i]);
    }
    else
    {
        printf("\nSystem is in UNSAFE STATE");
    }

    printf("\n");

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
