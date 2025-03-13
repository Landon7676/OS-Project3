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
#include <unistd.h> // for usleep()
#include <vector>

using namespace std;

const int MAX = 100; // Maximum possible value for internal counter in semaphores

int bufferSize; //Size of buffer
int numIters; // Number of iterations
vector<int> buffers; //Circular Buffer
int in = 0, out = 0; //Buffer indices

// POSIX Semaphores
sem_t sem_empty;
sem_t sem_full;
sem_t mutex;

// Producer function: Deposits values 1 to numIters into the buffer
void Producer(int id) {
    for (int produced = 0; produced < numIters; produced++) {
        sem_wait(&sem_empty); // Wait for empty slot
        sem_wait(&mutex);//Lock buffer access

        buffers[in] = produced;//Produce item
        cout << "Produced " << id << " produced " << produced << " at index " << in << endl;
        in = (in +1) % bufferSize; //Move to next position

        sem_post(&mutex);//Unlock buffer access
        sem_post(&sem_full); // Signal that buffer is full and an item is available

        usleep(100000);//Add delay(100 ms)
    }
}

// Consumer function: Fetches numIters items from the buffer and sums them
void Consumer(int id) {
    int total = 0;
    for (int consumed = 0; consumed < numIters; consumed++) {
        sem_wait(&sem_full); // Wait for item in buffer
        sem_wait(&mutex);//Lock buffer access

        int item = buffers[out]; //Consume item
        cout << "Consumer " << id << " consumed " << item << " from index " << out << endl;
        total += item; 
        out = (out +1) % bufferSize; //Move to next position

        sem_post(&mutex);//Unlock access to buffer
        sem_post(&sem_empty); // Signal that buffer is empty

        usleep(150000);//Add delay (150 ms)
    }
    cout << "Consumer " << id << " total: " << total << endl;
}

// Main function - Reads command line input, initializes semaphores, and creates threads
int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <Buffer Size> <Number of Iterations>" << endl;
        return 1;
    }

    bufferSize = atoi(argv[1]);
    numIters = atoi(argv[2]);
    buffers.resize(bufferSize); // Initialize buffer size

    // Initialize semaphores
    sem_init(&sem_empty, 0, bufferSize); // Start with all slots empty
    sem_init(&sem_full, 0, 0); // No filled slots initially
    sem_init(&mutex, 0, 1); // Mutex for mutual exclusion

    vector<thread> producers, consumers;
    for (int i = 0; i < 3; i++) {
        producers.push_back(thread(Producer, i));
        consumers.push_back(thread(Consumer, i));
    }

    for (auto &p : producers) p.join();
    for (auto &c : consumers) c.join();

    // Destroy semaphores
    sem_destroy(&sem_empty);
    sem_destroy(&sem_full);
    sem_destroy(&mutex);

    return 0;
}
