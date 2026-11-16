
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;

// Philosopher Thread
void *philosopher(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 3; i++)
    {
        printf("Philosopher %d is thinking\n", id);

        sem_wait(&room);

        sem_wait(&forks[id]);
        sem_wait(&forks[(id + 1) % N]);

        printf("Philosopher %d is eating\n", id);

        sleep(1);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        sem_post(&room);

        printf("Philosopher %d finished eating\n", id);
    }

    return NULL;
}

int main()
{
    pthread_t threads[N];
    int id[N];

    // Initialize semaphores
    sem_init(&room, 0, 4);

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++)
    {
        id[i] = i + 1;
        pthread_create(&threads[i], NULL, philosopher, &id[i]);
    }

    // Wait for all threads
    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
