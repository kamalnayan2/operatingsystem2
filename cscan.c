#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void scan(int requests[], int n, int head, int max_track, int direction) {
    int total_head_movement = 0;
    int *seek_sequence = (int *)malloc((n + 2) * sizeof(int));
    int index = 0;

    sort(requests, n);
    int pos;
    for (pos = 0; pos < n; pos++)
        if (requests[pos] >= head) break;

    if (direction == 1) {
        for (int i = pos; i < n; i++) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
        total_head_movement += abs(max_track - head);
        head = max_track;
        seek_sequence[index++] = 0;
        total_head_movement += abs(0 - head);
        head = 0;
        for (int i = 0; i < pos; i++) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
    } else {
        for (int i = pos - 1; i >= 0; i--) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
        total_head_movement += abs(0 - head);
        head = 0;
        seek_sequence[index++] = max_track;
        total_head_movement += abs(max_track - head);
        head = max_track;
        for (int i = pos; i < n; i++) {
            seek_sequence[index++] = requests[i];
            total_head_movement += abs(requests[i] - head);
            head = requests[i];
        }
    }

    printf("Order of servicing disk requests: ");
    for (int i = 0; i < index; i++) printf("%d ", seek_sequence[i]);
    printf("\nTotal Head Movement: %d\n", total_head_movement);
    free(seek_sequence);
}

int main() {
    int *requests, n, head, direction, max_track;
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    requests = (int *)malloc(n * sizeof(int));
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) 
    scanf("%d", &requests[i]);
    printf("Enter the current head position: ");
    scanf("%d", &head);
    printf("Enter the maximum track number: ");
    scanf("%d", &max_track);
    printf("Enter the direction of head movement (1 for right, 0 for left): ");
    scanf("%d", &direction);
    scan(requests, n, head, max_track, direction);
    free(requests);
    return 0;
}