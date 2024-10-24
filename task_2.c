#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREADS_COUNT 4

typedef struct {
    const char* name;
    const char* str;
    int num;
} thread_args_t;

void* thread_fn (void* args) {
    thread_args_t* thread_args = (thread_args_t*) args;

    for (int k = 1; k <= thread_args->num; k++)
        printf("%s. %s %d\n", thread_args->name, thread_args->str, k);
    printf("\n");

    return NULL;
}

int main() {
    pthread_t threads[THREADS_COUNT];
    thread_args_t thread_args[THREADS_COUNT];

    const char* thread_names[THREADS_COUNT] = { "Thread #1", "Thread #2", "Thread #3", "Thread #4" };

    for (int k = 0; k < THREADS_COUNT; k++) {
        thread_args[k].name = thread_names[k];
        thread_args[k].str = "test_string";
        thread_args[k].num = 3;

        if (pthread_create(&threads[k], NULL, thread_fn, &thread_args[k]) != 0)
            return 1;
    }

    for (int k = 0; k < THREADS_COUNT; k++)
        pthread_join(threads[k], NULL);

    return 0;
}
