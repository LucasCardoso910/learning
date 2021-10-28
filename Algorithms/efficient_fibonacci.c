#include <stdio.h>
#include <stdlib.h>

#define NOT_CALCULATED -1

// array of calculated values of the fibonacci sequence
long long int *fibonacci_values;

long long int fib(int n) {
    // base case
    if (n <= 1) { 
        fibonacci_values[n] = n; 
    }
    
    if (fibonacci_values[n] == NOT_CALCULATED) {
        long long int n_value;

        n_value = fib(n - 1) + fib(n - 2);
        fibonacci_values[n] = n_value; 
    }

    return fibonacci_values[n];
}

int main() {
    int term;
    int size;

    printf("Insert the n term of Fibonacci: ");
    scanf("%d", &term);
    size = term + 1; // +1 to calculate also the term nº 0 

    fibonacci_values = (long long int*) malloc(sizeof(long long int) * size);
    for (int i = 0; i < size; i++) {
        fibonacci_values[i] = NOT_CALCULATED;
    }

    // Example:
    // Term = 8
    // Term     0   1   2   3   4   5   6   7   8  
    // Value    0   1   1   2   3   5   8   13  21

    printf("The term is: %lld\n", fib(term));

    return 0;
}
