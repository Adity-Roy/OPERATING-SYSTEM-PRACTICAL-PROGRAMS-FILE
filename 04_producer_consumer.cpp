#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

const int BUFFER_SIZE = 5;
const int ITEMS = 10;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t emptySlots, fullSlots, mutexSem;

void *producer(void *) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&emptySlots);
        sem_wait(&mutexSem);
        buffer[in] = i;
        cout << "Producer produced item " << i << " at slot " << in << endl;
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutexSem);
        sem_post(&fullSlots);
        usleep(100000);
    }
    return NULL;
}

void *consumer(void *) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&fullSlots);
        sem_wait(&mutexSem);
        int item = buffer[out];
        cout << "\t\tConsumer consumed item " << item << " from slot " << out << endl;
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutexSem);
        sem_post(&emptySlots);
        usleep(150000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    sem_init(&mutexSem, 0, 1);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    sem_destroy(&mutexSem);
    cout << "All items produced and consumed." << endl;
    return 0;
}