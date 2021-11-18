#include <stdlib.h>

char** expand_array(char** array, int *size) {
    (*size)++;
    array = (char**) realloc(array, sizeof(char*) * (*size));

    return array;
}

char** set_last_value(char** array, int size, char* string, int string_size) {
    array[size - 1] = (char*) malloc(sizeof(char) * string_size);
    strcpy(array[size - 1], string);

    return array;
}

char** append(char** array, int *size, char* string, int string_size) {
    array = expand_array(array, size);
    array = set_last_value(array, *size, string, string_size);

    return array;
}

char** split(char* string, int size, char split_char, int *array_size) 
{
    int string_size = 0;
    char** string_array;
    char* current_string;
    
    *array_size = 0;
    // Max size of current string is the string initial size
    current_string = (char*) malloc(sizeof(char) * size);

    if (size <= 0) {
        // In a zero size string, there is one empty string after split
        string_array = (char**) malloc(sizeof(char*) * *array_size);
        string_array[0] = (char*) malloc(sizeof(char));
        string_array[0][0] = '\0';

        return string_array;
    }

    string_array = (char**) malloc(sizeof(char*) * *array_size);

    for (int i = 0; i < size; i++) {
        if (string[i] == split_char) {
            append(string_array, array_size, current_string, string_size);
            string_size = 0;
        }
        else {
            current_string[string_size] = string[i];
            string_size++;
        }
    }

    append(string_array, array_size, current_string, string_size);

    return string_array;
}
