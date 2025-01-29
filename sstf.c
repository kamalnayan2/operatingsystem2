#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to find the closest request
int findClosestRequest(int requests[], int n, int currentHead, int visited[]) {
    int closestIndex = -1;
    int minDistance = 10000; // A large number

    for (int i = 0; i < n; i++) {
        if (!visited[i]) { // Only consider unvisited requests
            int distance = abs(requests[i] - currentHead);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = i;
            }
        }
    }
    return closestIndex;
}

// Main function to implement SSTF disk scheduling
int main() {
    int requests[MAX_REQUESTS];
    int n, initialHead;

    // Input number of requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    // Input the disk requests
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Input the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    int totalSeekTime = 0;
    int currentHead = initialHead;
    int visited[MAX_REQUESTS] = {0}; // To track visited requests

    printf("Order of requests served: ");

    for (int i = 0; i < n; i++) {
        int closestIndex = findClosestRequest(requests, n, currentHead, visited);
        if (closestIndex == -1) {
            break; // No more requests to serve
        }

        // Mark the request as visited
        visited[closestIndex] = 1;

        // Calculate seek time
        totalSeekTime += abs(requests[closestIndex] - currentHead);
        currentHead = requests[closestIndex];

        // Print the served request
        printf("%d ", requests[closestIndex]);
    }

    printf("\nTotal seek time: %d\n", totalSeekTime);

    return 0;
}