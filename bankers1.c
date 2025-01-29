#include <stdio.h>

void acceptAvailableResources(int c, int available[]) {
    printf("Enter the available resources (%d values):\n", c);
    for (int i = 0; i < c; i++) {
        scanf("%d", &available[i]);
    }
}

void displayAllocationAndMax(int p, int c, int alc[10][10], int max[10][10]) {
    printf("\nAllocation Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d\t", alc[i][j]);
        }
        printf("\n");
    }
    printf("\nMax Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d\t", max[i][j]);
        }
        printf("\n");
    }
}

void displayNeedMatrix(int p, int c, int need[10][10]) {
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < c; j++) {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }
}

void displayAvailableResources(int c, int available[]) {
    printf("\nAvailable Resources:\n");
    for (int i = 0; i < c; i++) {
        printf("%d\t", available[i]);
    }
    printf("\n");
}

void checkSafeSequence(int p, int c, int alc[10][10], int max[10][10], int available[]) {
    int need[10][10];
    int done[10] = {0};
    int safe[10], count = 0;

    for (int i = 0; i < p; i++) {
        for (int j = 0; j < c; j++) {
            need[i][j] = max[i][j] - alc[i][j];
        }
    }

    int work[10]; // Temporary available resources
    for (int i = 0; i < c; i++) work[i] = available[i];

    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!done[i]) {
                int canAllocate = 1;
                for (int j = 0; j < c; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < c; j++) {
                        work[j] += alc[i][j];
                    }
                    safe[count++] = i;
                    done[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state! No safe sequence exists.\n");
            return;
        }
    }

    printf("System is in a safe state. Safe sequence is:\n");
    for (int i = 0; i < p; i++) {
        printf("P%d ", safe[i]);
    }
    printf("\n");
}

int main() 
{
    int p, c;
    int alc[10][10], max[10][10];
    int available[10];

    // Input number of processes and resources
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &p, &c);

    // Input allocation matrix
    printf("Enter allocation of resources for all processes (%dx%d matrix):\n", p, c);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &alc[i][j]);
        }
    }

    // Input maximum requirement matrix
    printf("Enter the max resources required by each process (%dx%d matrix):\n", p, c);
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Accept available resources
    acceptAvailableResources(c, available);

    // Display allocation and max matrices
    displayAllocationAndMax(p, c, alc, max);

    // Display need matrix
    int need[10][10];
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < c; j++) {
            need[i][j] = max[i][j] - alc[i][j];
        }
    }
    displayNeedMatrix(p, c, need);

    // Display available resources
    displayAvailableResources(c, available);

    // Check for safe sequence
    checkSafeSequence(p, c, alc, max, available);

    return 0;
}
