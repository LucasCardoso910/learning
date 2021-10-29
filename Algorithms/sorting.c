#include <stdio.h>

int* insert_sort(int* array, int size) {
    for (int i = 1; i < size; i++) {
        int search_element = array[i];
        int j = i;
        
        array[0] = search_element;

        while (search_element < array[j - 1]) {
            array[j] = array[j - 1];
            j--;
        }

        array[j] = search_element;
    }

    return array;
}