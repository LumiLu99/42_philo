#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *routine(void *arg)
{
    int id = *(int *)arg;
    printf("Thread handle: %d\n", id);
}

int main()
{
    pthread_t thread[5];
    int id[5];

    for (int i = 0; i < 5; i++)
    {
        id[i] = i;
        pthread_create(&thread[i], NULL, routine, &id[i]);
    }
    for (int i = 0; i < 5; i++)
        pthread_join(thread[i], NULL);
}
