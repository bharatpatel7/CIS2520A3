#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

int main(void){
    int array[20][10];
    int key[20];
    int i = 0, j = 0;

    FILE *fp;
    fp = fopen("f.dat", "r");

    // Check if file is opened successfully
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1; // Return with an error code
    }

    // Storing the input into a 2D Array after reading from the input
    for (i = 0; i < 20; ++i) {
        for (j = 0; j < 10; ++j) {
            fscanf(fp, "%d", &(array[i][j]));
        }
    }

    // Close the file after reading
    fclose(fp);

    // Evaluating the keys and storing them in the key array. The key array is used for the heap.
    for (i = 0; i < 20; ++i) {
        key[i] = array[i][0] + array[i][1] + array[i][2]; // Sum of the first 3 elements
    }

    // Apply downheap from the last internal node to the root (index 19 to 0)
    for (i = 19; i >= 0; --i) {
        downHeap(key, i, array);
    }

    // Printing the sorted array
    for (i = 0; i < 20; ++i) {
        for (j = 0; j < 10; ++j) {
            // Print elements with leading zeros if less than 10
            if (array[i][j] < 10) {
                printf("0%d ", array[i][j]);
            } else {
                printf("%d ", array[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
