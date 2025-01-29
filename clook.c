#include <stdio.h>
#include <stdlib.h>

void sortRequests(int *requests, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

void clookAlgorithm(int *requests, int n, int head, int direction) {
    int total_head_movement = 0;
    int current_position = head;

    sortRequests(requests, n);


    int *order = (int *)malloc(n * sizeof(int));
    int index = 0;

    if (direction == 1) { 
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current_position) {
                order[index++] = requests[i];
                total_head_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }

        for (int i = 0; i < n; i++) {
            if (requests[i] < head) {
                order[index++] = requests[i];
                total_head_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
    } else { 
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= current_position) {
                order[index++] = requests[i];
                total_head_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }

        
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] > head) {
                order[index++] = requests[i];
                total_head_movement += abs(current_position - requests[i]);
                current_position = requests[i];
            }
        }
    }

    
    printf("Order of servicing: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", order[i]);
    }
    printf("\nTotal head movement: %d\n", total_head_movement);

    free(order);
}

int main() {
    int n;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int *requests = (int *)malloc(n * sizeof(int));

    
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int head; 
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int direction; 
    printf("Enter the direction of servicing (1 for upper side, 0 for lower side): ");
    scanf("%d", &direction);

    clookAlgorithm(requests, n, head, direction);

    free(requests);
    return 0;
}