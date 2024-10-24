#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define DEFAULT_CATALAN_COUNT 10
#define DEFAULT_PRIME_COUNT 10

typedef struct {
    int n;
    int* results_array;
} thread_data_t;

void* calculate_catalan_numbers (void* arg) {
    thread_data_t* data = (thread_data_t*) arg;
    data->results_array = malloc(data->n * sizeof(int));

    for (int k = 0; k < data->n; k++) {
        if (k == 0)
            data->results_array[k] = 1;
        else {
            data->results_array[k] = 0;
            for (int j = 0; j < k; j++)
                data->results_array[k] += data->results_array[j] * data->results_array[k - 1 - j];
        }
    }

    return NULL;
}

void* calculate_prime_numbers (void* arg) {
    thread_data_t* data = (thread_data_t*) arg;
    data->results_array = malloc(data->n * sizeof(int));
    
    int count = 0;
    int number = 2;
    while (count < data->n) {
        int is_prime = 1;
        for (int k = 2; k * k <= number; k++) {
            if (number % k == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            data->results_array[count] = number;
            count++;
        }

        number++;
    }

    return NULL;
}

int main (int argc, char* argv[]) {
    int catalan_count = DEFAULT_CATALAN_COUNT;
    int prime_count = DEFAULT_PRIME_COUNT;

    if (argc == 3) {
        catalan_count = atoi(argv[1]);
        prime_count = atoi(argv[2]);
    } 
    else if (argc > 3)
        return 1;

    pthread_t catalan_thread, prime_thread;
    thread_data_t catalan_data, prime_data;

    catalan_data.n = catalan_count;
    prime_data.n = prime_count;

    if (pthread_create(&catalan_thread, NULL, calculate_catalan_numbers, (void*) &catalan_data) != 0)
        return 1;

    if (pthread_create(&prime_thread, NULL, calculate_prime_numbers, (void*) &prime_data) != 0)
        return 1;

    pthread_join(catalan_thread, NULL);
    pthread_join(prime_thread, NULL);

    printf("catalan numbers: ");
    for (int k = 0; k < catalan_count; k++)
        printf("%d ", catalan_data.results_array[k]);
    printf("\n");

    printf("prime numbers: ");
    for (int k = 0; k < prime_count; k++)
        printf("%d ", prime_data.results_array[k]);
    printf("\n");

    free(catalan_data.results_array);
    free(prime_data.results_array);

    return 0;
}
