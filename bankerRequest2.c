#include <stdio.h>

void acceptAvailableResources(int c, int available[]) {
    printf("Enter the available resources (%d values):\n", c);
    for (int i = 0; i < c; i++) {
        scanf("%d", &available[i]);
    }
}

void displayMatrices(int p, int c, int alc[10][10], int max[10][10]) {
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

void checkSafeSequence(int p, int c, int alc[10][10], int max[10][10], int available[]) {
    int need[10][10], done[10] = {0}, safe[10], count = 0;

    for (int i = 0; i < p; i++)
        for (int j = 0; j < c; j++)
            need[i][j] = max[i][j] - alc[i][j];

    int work[10];
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

int requestResources(int p, int c, int alc[10][10], int max[10][10], int available[], int processID, int request[]) {
    for (int j = 0; j < c; j++) {
        if (request[j] > (max[processID][j] - alc[processID][j]) || request[j] > available[j]) {
            printf("Error: Invalid request.\n");
            return 0;
        }
    }

    for (int j = 0; j < c; j++) {
        available[j] -= request[j];
        alc[processID][j] += request[j];
    }

    checkSafeSequence(p, c, alc, max, available);
    return 1;
}

int main() {
    int p, c, alc[10][10], max[10][10], available[10];

    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &p, &c);

    printf("Enter allocation matrix (%dx%d):\n", p, c);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &alc[i][j]);

    printf("Enter max matrix (%dx%d):\n", p, c);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < c; j++)
            scanf("%d", &max[i][j]);

    acceptAvailableResources(c, available);
    displayMatrices(p, c, alc, max);

    int processID;
    printf("Enter process ID to request resources (0 to %d): ", p - 1);
    scanf("%d", &processID);

    int request[10];
    printf("Enter request for process P%d (%d values):\n", processID, c);
    for (int i = 0; i < c; i++) {
        scanf("%d", &request[i]);
    }


    requestResources(p, c, alc, max, available, processID, request);
    return 0;
}