#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "a3q2_header.h"

/*
 * The downHeap function performs the downheap algorithm.
 * The key at the passed position is swapped with the key of it's child with the smallest value.
 * If the key is smaller, than both of it's children's keys then no swap happens.
 * After swap, the downHeap is called again to the new position of the swapped key and it terminates when it's value is smaller than both children.
*/
void downHeap(int key[20], int pos, int array[20][10]){
    
    int smallest = pos;
    int left = 2 * pos + 1;  // Left child index
    int right = 2 * pos + 2; // Right child index
    

    // Check if left child exists and is larger than current node
    if (left < 20 && key[left] > key[smallest]) {
        smallest = left;
    }

    // Check if right child exists and is larger than the largest so far
    if (right < 20 && key[right] > key[smallest]) {
        smallest = right;
    }

    // If largest is not the current node, swap and call downHeap recursively
    if (smallest != pos) {
        swap(pos, smallest, key, array);  // Swap the keys and corresponding rows
        downHeap(key, smallest, array);   // Recursively heapify the affected subtree
    }

}

// The isParent function returns true if the passed position has a child or false if there's no child
bool isParent(int keyPos){

       return (2 * keyPos + 1) < 20;

}

// The swap function swaps 2 rows in the 2D array and the key array. It receives the position of the 2 rows to be swapped, the key array, and the 2D array in its arguements.
void swap(int key1Pos, int key2Pos, int key[20], int array[20][10]){

int tempKey = key[key1Pos];
    key[key1Pos] = key[key2Pos];
    key[key2Pos] = tempKey;

    // Swap the corresponding rows in the 2D array
    for (int i = 0; i < 10; i++) {
        int temp = array[key1Pos][i];
        array[key1Pos][i] = array[key2Pos][i];
        array[key2Pos][i] = temp;
    }

}


