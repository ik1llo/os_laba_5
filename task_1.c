#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define ITERATIONS_COUNT 5
#define SLEEP_TIME 2

void* child_thread_function (void* arg) {
    for (int k = 1; k <= ITERATIONS_COUNT; k++) {
        printf("Child Thread. Iteration: %d\n", k);
        sleep(SLEEP_TIME);
    }

    return NULL;
}

int main () {
    pthread_t child_thread;

    if (pthread_create(&child_thread, NULL, child_thread_function, NULL) != 0)
        return 1;

    for (int k = 1; k <= ITERATIONS_COUNT; k++) {
        printf("Main Thread. Iteration: %d\n", k);
        sleep(SLEEP_TIME);
    }

    pthread_join(child_thread, NULL);

    return 0;
}
