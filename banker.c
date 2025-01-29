#include <stdio.h>

int main() 
{
    int p, c, i, j, k, count = 0;
    int alc[10][10], max[10][10], need[10][10];
    int available[10], safe[10], done[10] = {0}; // Done array tracks completed processes
    char choice;

    // Input number of processes and resources
    printf("Enter the number of processes and resources: ");
    scanf("%d %d", &p, &c);

    // Input allocation matrix
    printf("Enter allocation of resources for all processes (%dx%d matrix):\n", p, c);
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &alc[i][j]);
        }
    }

    // Input maximum requirement matrix
    printf("Enter the max resources required by each process (%dx%d matrix):\n", p, c);
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Calculate need matrix
    for (i = 0; i < p; i++) {
        for (j = 0; j < c; j++) {
            need[i][j] = max[i][j] - alc[i][j];
        }
    }

    // Menu loop
    do {
        printf("\nMenu:\n");
        printf("a) Accept Available Resources\n");
        printf("b) Display Allocation and Max Matrices\n");
        printf("c) Display Need Matrix\n");
        printf("d) Display Available Resources\n");
        printf("e) Check Safe Sequence\n");
        printf("f) Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) 
        {
            case 'a': // Input available resources
                printf("Enter the available resources (%d values):\n", c);
                for (i = 0; i < c; i++) {
                    scanf("%d", &available[i]);
                }
                break;

            case 'b': // Display allocation and max matrices
                printf("\nAllocation Matrix:\n");
                for (i = 0; i < p; i++) {
                    for (j = 0; j < c; j++) {
                        printf("%d\t", alc[i][j]);
                    }
                    printf("\n");
                }
                printf("\nMax Matrix:\n");
                for (i = 0; i < p; i++) {
                    for (j = 0; j < c; j++) {
                        printf("%d\t", max[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 'c': // Display need matrix
                printf("\nNeed Matrix:\n");
                for (i = 0; i < p; i++) {
                    for (j = 0; j < c; j++) {
                        printf("%d\t", need[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 'd': // Display available resources
                printf("\nAvailable Resources:\n");
                for (i = 0; i < c; i++) {
                    printf("%d\t", available[i]);
                }
                printf("\n");
                break;

            case 'e': // Check for safe sequence
                count = 0; // Reset count of completed processes
                for (i = 0; i < p; i++) done[i] = 0; // Reset done array

                int work[10]; // Temporary available resources
                for (i = 0; i < c; i++) work[i] = available[i];

                while (count < p) {
                    int found = 0;
                    for (i = 0; i < p; i++) {
                        if (!done[i]) {
                            int canAllocate = 1;
                            for (j = 0; j < c; j++) {
                                if (need[i][j] > work[j]) {
                                    canAllocate = 0;
                                    break;
                                }
                            }
                            if (canAllocate) {
                                for (j = 0; j < c; j++) {
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
                        break;
                    }
                }

                if (count == p) {
                    printf("System is in a safe state. Safe sequence is:\n");
                    for (i = 0; i < p; i++) {
                        printf("P%d ", safe[i]);
                    }
                    printf("\n");
                }
                break;

            case 'f': // Exit
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 'f');

    return 0;
}
