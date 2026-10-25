#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5
sem_t forks[N];
sem_t room;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id, right = (id + 1) % N;

    for (int meal = 1; meal <= 2; meal++) {
        printf("Philosopher %d is thinking\n", id);
        sem_wait(&room);          /* At most N-1 compete for forks */
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        printf("Philosopher %d is eating (meal %d)\n", id, meal);
        sleep(1);
        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&room);
    }
    return NULL;
}
int main(void) {
    pthread_t threads[N];
    int ids[N];
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++) sem_init(&forks[i], 0, 1);
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(threads[i], NULL);
    for (int i = 0; i < N; i++) sem_destroy(&forks[i]);
    sem_destroy(&room);
    return 0;
}
