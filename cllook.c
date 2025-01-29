#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100 // Define a maximum number of requests

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void c_look(int requests[], int n, int head, char direction) {
    // Sort the requests
    sort(requests, n);

    int total_head_movement = 0;
    int i;

    // Find the position of the head in the sorted requests
    for (i = 0; i < n; i++) {
        if (requests[i] >= head) {
            break;
        }
    }

    if (direction == 'R' || direction == 'r') {
        // Service requests from head to the end of the list
        for (int j = i; j < n; j++) {
            total_head_movement += abs(requests[j] - head);
            head = requests[j];
            printf("Servicing request: %d\n", requests[j]);
        }

        // Jump to the first request in the list
        if (i > 0) {
            total_head_movement += abs(requests[0] - head);
            head = requests[0];
            printf("Jumping to first request: %d\n", requests[0]);
        }

        // Service remaining requests
        for (int j = 0; j < i; j++) {
            total_head_movement += abs(requests[j] - head);
            head = requests[j];
            printf("Servicing request: %d\n", requests[j]);
        }
    } else if (direction == 'L' || direction == 'l') {
        // Service requests from head to the beginning of the list
        for (int j = i - 1; j >= 0; j--) {
            total_head_movement += abs(requests[j] - head);
            head = requests[j];
            printf("Servicing request: %d\n", requests[j]);
        }

        // Jump to the last request in the list
        if (i < n) {
            total_head_movement += abs(requests[n - 1] - head);
            head = requests[n - 1];
            printf("Jumping to last request: %d\n", requests[n - 1]);
        }

        // Service remaining requests
        for (int j = n - 1; j >= i; j--) {
            total_head_movement += abs(requests[j] - head);
            head = requests[j];
            printf("Servicing request: %d\n", requests[j]);
        }
    } else {
        printf("Invalid direction. Please use 'L' for left or 'R' for right.\n");
        return;
    }

    printf("Total head movement: %d\n", total_head_movement);
}

int main() {
    int n;
    int requests[MAX_REQUESTS]; // Fixed-size array for requests

    printf("Enter the number of disk requests (max %d): ", MAX_REQUESTS);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_REQUESTS) {
        printf("Error: Number of requests must be between 1 and %d.\n", MAX_REQUESTS);
        return 1;
    }

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0) {
            printf("Error: Disk request must be a non-negative integer.\n");
            return 1;
        }
    }

    int head;
    printf("Enter the current head position: ");
    scanf("%d", &head);
    if (head < 0) {
        printf("Error: Head position must be a non-negative integer.\n");
        return 1;
    }

    char direction;
    printf("Enter the direction of movement (L for left, R for right): ");
    scanf(" %c", &direction); // Note the space before %c to consume any newline character

    c_look(requests, n, head, direction);

    return 0;
}