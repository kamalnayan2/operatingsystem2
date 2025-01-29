#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    // Simple bubble sort for sorting the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void scan(int requests[], int n, int head, int direction) {
    int total_head_movement = 0;
    int seek_sequence[100];
    int index = 0;

    // Sort the requests
    sort(requests, n);

    // Find the position of the head in the sorted array
    int pos;
    for (pos = 0; pos < n; pos++) {
        if (requests[pos] >= head) {
            break;
        }
    }

    // Move towards the end of the disk
    if (direction == 1) {
        for (int i = pos; i < n; i++) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
        // Move to the end of the disk (assuming 200)
        total_head_movement += abs(200 - head);
        head = 200;

        // Move back to the beginning
        for (int i = pos - 1; i >= 0; i--) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
    } else { // Move towards the beginning of the disk
        for (int i = pos - 1; i >= 0; i--) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
        // Move to the beginning of the disk (0)
        total_head_movement += abs(0 - head);
        head = 0;

        // Move back to the end
        for (int i = pos; i < n; i++) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
    }

    // Print the seek sequence
    printf("Seek Sequence: ");
    for (int i = 0; i < index; i++) {
        printf("%d ", seek_sequence[i]);
    }
    printf("\nTotal Head Movement: %d\n", total_head_movement);
}

int main() {
    int requests[100], n, head, direction;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the direction of head movement (1 for right, 0 for left): ");
    scanf("%d", &direction);

    scan(requests, n, head, direction);

    return 0;
}