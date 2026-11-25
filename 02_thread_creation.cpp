#include <iostream>
#include <pthread.h>
using namespace std;

const int NUM_THREADS = 4;

struct PartialSum {
    int start, end;
    long long sum;
};

void *sumArray(void *arg) {
    PartialSum *p = (PartialSum *)arg;
    p->sum = 0;
    for (int i = p->start; i < p->end; i++)
        p->sum += i;
    cout << "Thread " << (unsigned long)pthread_self() % 100000
         << ": sum[" << p->start << ".." << p->end << ") = " << p->sum << endl;
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    PartialSum data[NUM_THREADS];
    int n = 1000000;
    int chunk = n / NUM_THREADS;
    long long total = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].start = i * chunk;
        data[i].end = (i == NUM_THREADS - 1) ? n : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, sumArray, &data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total += data[i].sum;
    }

    cout << "Total sum (0 to " << n - 1 << ") computed using "
         << NUM_THREADS << " threads = " << total << endl;
    return 0;
}