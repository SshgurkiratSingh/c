#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

void write_to_log(const char *message)
{
    pthread_mutex_lock(&mutex);
    FILE *f = fopen("log.txt", "a");
    if (f == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fprintf(f, "%s\n", message);
    fclose(f);
    pthread_mutex_unlock(&mutex);
}

void *communication_thread(void *arg)
{
    int channel_id = *(int *)arg;
    char msg[100];
    snprintf(msg, 100, "Channel %d: Communication established", channel_id);
    write_to_log(msg);
    sleep(2);
    snprintf(msg, 100, "Channel %d: Communication ended", channel_id);
    write_to_log(msg);
    return NULL;
}
int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[5];
    int channel_ids[5];
    for (int i = 0; i < 5; i++)
    {
        // channel_ids[i] = i;
        if (pthread_create(&threads[i], NULL, communication_thread, &channel_ids[i]))
        {
            perror("pthread_create");
            exit(1);
        }
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}