#include <stdio.h>
#include <stdlib.h>
// Explanation
// compare function: A comparator for qsort that sorts integers in ascending order.
// findIndex function: Searches for a value in arr2 and returns its index or -1 if not found.
// relativeSort function:
// Allocates an auxiliary array extra to store elements of arr1 that are not in arr2.
// Partitions arr1 into two parts: elements found in arr2 and elements not found (which go into extra).
// Sorts the extra array.
// Rearranges arr1 to follow the order in arr2 and appends sorted extra elements at the end.
// Frees the allocated memory for extra.
// printArray function: Prints an array.
// main function:
// Initializes arr1 and arr2.
// Prints the original arr1.
// Calls relativeSort to sort arr1.
// Prints the sorted arr1.
// This annotated code should help you understand each step in the process of sorting arr1 based on the relative order of arr2 with additional elements placed at the end in ascending order.
// Comparator function for qsort, used for sorting integers in ascending order
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to find the index of an element in arr2, returns -1 if not found
int findIndex(int *arr2, int size2, int value) {
    for (int i = 0; i < size2; i++) {
        if (arr2[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to sort arr1 according to the relative order of elements in arr2
void relativeSort(int *arr1, int size1, int *arr2, int size2) {
    // Create an auxiliary array to store elements not in arr2
    int *extra = (int *)malloc(size1 * sizeof(int));
    int extraCount = 0;

    // Traverse arr1 and move elements not in arr2 to the extra array
    int k = 0;
    for (int i = 0; i < size1; i++) {
        if (findIndex(arr2, size2, arr1[i]) != -1) {
            arr1[k++] = arr1[i];
        } else {
            extra[extraCount++] = arr1[i];
        }
    }

    // Sort the extra array in ascending order
    qsort(extra, extraCount, sizeof(int), compare);

    // Traverse arr2 and rearrange arr1 in the order of arr2
    int j = 0;
    for (int i = 0; i < size2; i++) {
        for (int m = 0; m < size1; m++) {
            if (arr1[m] == arr2[i]) {
                arr1[j++] = arr2[i];
            }
        }
    }

    // Append the sorted extra elements to the end of arr1
    for (int i = 0; i < extraCount; i++) {
        arr1[j++] = extra[i];
    }

    // Free the allocated memory for the extra array
    free(extra);
}

// Function to print an array
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19};
    int arr2[] = {2, 1, 4, 3, 9, 6};

    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Original arr1: ");
    printArray(arr1, size1);

    relativeSort(arr1, size1, arr2, size2);

    printf("Sorted arr1: ");
    printArray(arr1, size1);

    return 0;
}
