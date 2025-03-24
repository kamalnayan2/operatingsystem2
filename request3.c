#include <stdio.h>

int main() {
    int p, c, i, j, count = 0;
    int alc[10][10], max[10][10], need[10][10], available[10], safe[10], done[10] = {0};

    // Input processes, resources, allocation, and max requirement
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &p, &c);

    printf("Enter allocation matrix (%dx%d):\n", p, c);
    for (i = 0; i < p; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &alc[i][j]);

    printf("Enter max matrix (%dx%d):\n", p, c);
    for (i = 0; i < p; i++)
        for (j = 0; j < c; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources (%d values): ", c);
    for (i = 0; i < c; i++)
        scanf("%d", &available[i]);

    // Calculate need matrix
    for (i = 0; i < p; i++)
        for (j = 0; j < c; j++)
            need[i][j] = max[i][j] - alc[i][j];

    // Safe sequence calculation
    while (count < p) {
        int found = 0;
        for (i = 0; i < p; i++) {
            if (!done[i]) {
                int canAllocate = 1;
                for (j = 0; j < c; j++) {
                    if (need[i][j] > available[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (j = 0; j < c; j++)
                        available[j] += alc[i][j];
                    safe[count++] = i;
                    done[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state!\n");
            return 0;
        }
    }

    // Print safe sequence
    printf("Safe sequence: ");
    for (i = 0; i < count; i++)
        printf("P%d ", safe[i]);
    printf("\n");

    return 0;
}
