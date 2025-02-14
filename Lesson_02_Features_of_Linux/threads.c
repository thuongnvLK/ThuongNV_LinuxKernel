#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function(void* arg) {
    printf("Thread %ld has ID: %lu\n", (long)arg, pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];

    for (long i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void*)i);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}


