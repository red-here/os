#include <stdio.h>
#include <stdlib.h>

int main()
{
    int req[100], a[100], n, head;
    int i, j, temp, cur, total, min, pos;
    int visited[100] = {0};

    printf("Enter number of requests: ");
    scanf("%d", &n);

    if (n < 1 || n > 100)
    {
        printf("Invalid number of requests!\n");
        return 1;
    }

    printf("Enter disk requests (0-199): ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);

        if (req[i] < 0 || req[i] > 199)
        {
            printf("Invalid track number!\n");
            return 1;
        }
    }

    printf("Enter initial head position (0-199): ");
    scanf("%d", &head);

    if (head < 0 || head > 199)
    {
        printf("Invalid head position!\n");
        return 1;
    }

    // SSTF
    for (i = 0; i < n; i++)
        a[i] = req[i];

    cur = head;
    total = 0;

    printf("\nSSTF: %d", head);

    for (i = 0; i < n; i++)
    {
        min = 9999;
        pos = -1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] && abs(cur - req[j]) < min)
            {
                min = abs(cur - req[j]);
                pos = j;
            }
        }

        visited[pos] = 1;
        total += abs(cur - req[pos]);
        cur = req[pos];

        printf(" -> %d", cur);
    }

    printf("\nTotal head movement = %d\n", total);

    // Sort requests for SCAN and C-LOOK
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (req[j] > req[j + 1])
            {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // SCAN: Move toward 199, then reverse
    cur = head;
    total = 0;

    printf("\nSCAN: %d", head);

    for (i = 0; i < n; i++)
    {
        if (req[i] >= head)
        {
            total += abs(cur - req[i]);
            cur = req[i];
            printf(" -> %d", cur);
        }
    }

    if (cur != 199)
    {
        total += abs(cur - 199);
        cur = 199;
        printf(" -> %d", cur);
    }

    for (i = n - 1; i >= 0; i--)
    {
        if (req[i] < head)
        {
            total += abs(cur - req[i]);
            cur = req[i];
            printf(" -> %d", cur);
        }
    }

    printf("\nTotal head movement = %d\n", total);

    // C-LOOK: Move upward, then jump to lowest request
    cur = head;
    total = 0;

    printf("\nC-LOOK: %d", head);

    for (i = 0; i < n; i++)
    {
        if (req[i] >= head)
        {
            total += abs(cur - req[i]);
            cur = req[i];
            printf(" -> %d", cur);
        }
    }

    for (i = 0; i < n; i++)
    {
        if (req[i] < head)
        {
            total += abs(cur - req[i]);
            cur = req[i];
            printf(" -> %d", cur);
        }
    }

    printf("\nTotal head movement = %d\n", total);

    return 0;
}