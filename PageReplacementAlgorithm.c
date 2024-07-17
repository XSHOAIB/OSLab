#include <stdio.h>

void fifo(int page[], int n, int capacity) {
  int frames[capacity];
  int pageFaults = 0, pageHits = 0;

  // Initialize all frames as empty
  for (int i = 0; i < capacity; i++) {
    frames[i] = -1;
  }

  for (int i = 0; i < n; i++) {
    int found = 0;

    // Check if the page is already in the frame
    for (int j = 0; j < capacity; j++) {
      if (frames[j] == page[i]) {
        found = 1;
        pageHits++;
        break;
      }
    }

    // If not found, replace the oldest page
    if (!found) {
      pageFaults++;

      // Find the first empty frame
      int j;
      for (j = 0; j < capacity; j++) {
        if (frames[j] == -1) {
          break;
        }
      }

      // If all frames are full, replace the oldest page
      if (j == capacity) {
        for (j = 0; j < capacity - 1; j++) {
          frames[j] = frames[j + 1];
        }
      }

      frames[j] = page[i];
    }

    // Print the current frame contents
    printf("Page %d: ", page[i]);
    for (int j = 0; j < capacity; j++) {
      if (frames[j] != -1) {
        printf("%d ", frames[j]);
      } else {
        printf("- ");
      }
    }
    printf("\n");
  }

  printf("Total Page Faults: %d\n", pageFaults);
  printf("Total Page Hitss: %d\n", pageHits);
}

int main() {
  int page[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
  int capacity = 4;
  int n = sizeof(page) / sizeof(page[0]);

  fifo(page, n, capacity);

  return 0;
}
