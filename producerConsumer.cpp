/*
* boundedBuffer.c - Producer-Consumer with POSIX Semaphores
*
* A complete example of a simple producer/consumer program. The Producer
* and Consumer functions run as independent threads, sharing a single buffer.
* The producer deposits integers from 1 to numIters into the buffer.
* The Consumer fetches these values and sums them.
* Two semaphores, sem_empty and sem_full, control access to the buffer.
*/

#include <iostream>
#include <thread>
#include <semaphore.h>
#include <cstdlib> // for atoi
#include <unistd.h> // for sleep()

using namespace std;

const int MAX = 100; // Maximum possible value for internal counter in semaphores

int buffer; // Shared buffer (size = 1)
int numIters; // Number of iterations

// POSIX Semaphores
sem_t sem_empty;
sem_t sem_full;

// Producer function: Deposits values 1 to numIters into the buffer
void Producer() {
    for (int produced = 0; produced < numIters; produced++) {
        sem_wait(&sem_empty); // Wait for empty slot
        buffer = produced; // Place item in buffer
        sem_post(&sem_full); // Signal that buffer is full
    }
}

// Consumer function: Fetches numIters items from the buffer and sums them
void Consumer() {
    int total = 0;
    for (int consumed = 0; consumed < numIters; consumed++) {
        sem_wait(&sem_full); // Wait for item in buffer
        total += buffer; // Consume item
        sem_post(&sem_empty); // Signal that buffer is empty
    }
    printf("The total is %d\n", total);
}

// Main function - Reads command line input, initializes semaphores, and creates threads
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <Number of Iterations>\n", argv[0]);
        exit(0);
    }

    numIters = atoi(argv[1]); // Convert argument to integer

    // Initialize semaphores: `sem_empty` starts at 1 (empty buffer), `sem_full` starts at 0 (empty)
    sem_init(&sem_empty, 0, 1);
    sem_init(&sem_full, 0, 0);

    thread producer(Producer);
    thread consumer(Consumer);

    producer.join();
    consumer.join();

    // Destroy semaphores
    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);

    return 0;
}
