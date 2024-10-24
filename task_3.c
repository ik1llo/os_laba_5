#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define ITERATIONS_COUNT 10

#define MIN_RANDOM 1
#define MAX_RANDOM 20

#define STOP_NUMBER 10

#define SLEEP_TIME 2

void* print_string (void* arg) {
    const char* str = (const char*) arg;

    for (int k = 1; k <= ITERATIONS_COUNT; k++) {
        printf("child thread | string | iteration: %d | message: %s\n", k, str);
        sleep(SLEEP_TIME);
    }

    return NULL;
}

void* generate_random_numbers (void* arg) {
    srand(time(NULL) ^ pthread_self());
    int random_number;

    for (int k = 1; k <= ITERATIONS_COUNT; k++) {
        random_number = rand() % (MAX_RANDOM - MIN_RANDOM + 1) + MIN_RANDOM;
        printf("child thread | random number | generated: %d\n", random_number);
        sleep(SLEEP_TIME);

        if (random_number == STOP_NUMBER) {
            printf("child thread | random number | stop number %d found!\n", STOP_NUMBER);
            return NULL;
        }
    }

    return NULL;
}

int main() {
    pthread_t string_thread, random_thread;
    const char* message = "test_string";

    if (pthread_create(&string_thread, NULL, print_string, (void*) message) != 0)
        return 1;

    if (pthread_create(&random_thread, NULL, generate_random_numbers, NULL) != 0)
        return 1;

    pthread_join(string_thread, NULL);
    pthread_join(random_thread, NULL);

    return 0;
}
