#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

const int N = 5;
sem_t forks[N];
sem_t room;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    for (int cycle = 0; cycle < 2; cycle++) {
        cout << "Philosopher " << id << " is thinking" << endl;
        usleep(100000);
        sem_wait(&room);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        cout << "Philosopher " << id << " is eating (fork "
             << left << " and fork " << right << ")" << endl;
        usleep(150000);
        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&room);
        cout << "Philosopher " << id << " finished eating and put down forks" << endl;
    }
    return NULL;
}

int main() {
    pthread_t philo[N];
    int ids[N];
    for (int i = 0; i < N; i++) sem_init(&forks[i], 0, 1);
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philo[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(philo[i], NULL);
    for (int i = 0; i < N; i++) sem_destroy(&forks[i]);
    sem_destroy(&room);
    return 0;
}