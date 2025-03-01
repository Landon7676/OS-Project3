#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

//Part a

class UnisexBathroom {
private:
    mutex mtx;
    condition_variable cv;
    int menInside = 0, womenInside = 0;
    int capacity = 3;

public:
    void manEnter(int id) {
        unique_lock<mutex> lock(mtx);

        // Wait if women are in the bathroom or it's full
        cv.wait(lock, [this]() { return womenInside == 0 && menInside < capacity; });

        menInside++;
        cout << "Man " << id << " entered. (Men inside: " << menInside << ")\n";
    }

    void manExit(int id) {
        unique_lock<mutex> lock(mtx);
        menInside--;
        cout << "Man " << id << " exited. (Men inside: " << menInside << ")\n";

        // Notify waiting threads
        cv.notify_all();
    }

    void womanEnter(int id) {
        unique_lock<mutex> lock(mtx);

        // Wait if men are in the bathroom or it's full
        cv.wait(lock, [this]() { return menInside == 0 && womenInside < capacity; });

        womenInside++;
        cout << "Woman " << id << " entered. (Women inside: " << womenInside << ")\n";
    }

    void womanExit(int id) {
        unique_lock<mutex> lock(mtx);
        womenInside--;
        cout << "Woman " << id << " exited. (Women inside: " << womenInside << ")\n";

        // Notify waiting threads
        cv.notify_all();
    }
};

// Function to simulate bathroom usage time
void useBathroom() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(100, 2000);
    this_thread::sleep_for(chrono::milliseconds(dist(gen)));
}

// Man thread function
void OneMan(UnisexBathroom &bathroom, int id) {
    bathroom.manEnter(id);
    useBathroom();
    bathroom.manExit(id);
}

// Woman thread function
void OneWoman(UnisexBathroom &bathroom, int id) {
    bathroom.womanEnter(id);
    useBathroom();
    bathroom.womanExit(id);
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
