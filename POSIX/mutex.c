#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 3
#define COUNT_LIMIT 16
pthread_mutex_t mutex;
int count = 0;
void *thread_function(void *arg)
{
    int thread_id = *(int *)arg;
    int i;

    for (i = 0; i < COUNT_LIMIT; ++i)
    {
        pthread_mutex_lock(&mutex);
        count++;
        printf("Thread %d incremented counter to %d\n", thread_id, count);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1, 2};
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Final count = %d\n", count);
    return 0;
}