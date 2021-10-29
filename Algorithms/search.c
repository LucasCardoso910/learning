#include <stdio.h>

int binary_search(int *array, int size, int element) {
    int left = 0;
    int right = (size - 1);
    int middle;

    while (left <= right) {
        middle = (left + right) / 2;

        if (array[middle] == element) {
            return middle;
        }

        if (array[middle] < element) {
            left = middle + 1;
        }
        else { // array[middle] > element
            right = middle - 1;
        }
    }

    return -1;
}

int ternary_search(int *array, int size, int element) {
    int left = 0;
    int right = size - 1;
    int elem1, elem2;
    
    while (left <= right) {
        elem1 = left + (right - left) / 3;
        elem2 = left + (2 * (right - left)) / 3;

        if (element == elem1) {
            return elem1;
        }
        else if (element == elem2) {
            return elem2;
        }
        else if (element < array[elem1]) {
            right = elem1 - 1;
        }
        else if (element < array[elem2]) {
            left = elem1 + 1;
            right = elem2 - 1;
        }
        else {
            left = elem2 + 1;
        }
    }

    return -1;
}