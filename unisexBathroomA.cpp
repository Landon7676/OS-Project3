#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

class UnisexBathroom {
private:
    mutex mtx;
    condition_variable cv;
    int menInside = 0, womenInside = 0;
    int capacity = 3;

public:
    void manEnter(int id) {
        unique_lock<mutex> lock(mtx);
        
        // Wait if women are inside or capacity is full
        cv.wait(lock, [this]() { return womenInside == 0 && menInside < capacity; });

        menInside++;
        cout << "Man " << id << " entered. (Men inside: " << menInside << ", Women inside: " << womenInside << ")\n";
        
        lock.unlock();
        useBathroom();
        
        lock.lock();
        menInside--;
        cout << "Man " << id << " exited. (Men inside: " << menInside << ", Women inside: " << womenInside << ")\n";
        
        cv.notify_all(); // Notify others when a man exits
    }

    void womanEnter(int id) {
        unique_lock<mutex> lock(mtx);

        // Wait if men are inside or capacity is full
        cv.wait(lock, [this]() { return menInside == 0 && womenInside < capacity; });

        womenInside++;
        cout << "Woman " << id << " entered. (Men inside: " << menInside << ", Women inside: " << womenInside << ")\n";

        lock.unlock();
        useBathroom();

        lock.lock();
        womenInside--;
        cout << "Woman " << id << " exited. (Men inside: " << menInside << ", Women inside: " << womenInside << ")\n";

        cv.notify_all(); // Notify others when a woman exits
    }

private:
    // Function to simulate bathroom usage time
    void useBathroom() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(100, 2000);
        this_thread::sleep_for(chrono::milliseconds(dist(gen)));
    }
};

// Man thread function
void OneMan(UnisexBathroom &bathroom, int id) {
    bathroom.manEnter(id);
}

// Woman thread function
void OneWoman(UnisexBathroom &bathroom, int id) {
    bathroom.womanEnter(id);
}

// Main function
int main() {
    UnisexBathroom bathroom;
    vector<thread> people;

    // Create 10 men and 10 women threads
    for (int i = 0; i < 10; i++) {
        people.push_back(thread(OneMan, ref(bathroom), i + 1));
        people.push_back(thread(OneWoman, ref(bathroom), i + 1));
    }

    // Join all threads
    for (auto &t : people) {
        t.join();
    }

    return 0;
}
