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
    int menWaiting = 0, womenWaiting = 0;
    int capacity = 3;
    bool menTurn = true; // Tracks whose turn it is when switching

public:
    void enterBathroom(int id, bool isMale) {
        unique_lock<mutex> lock(mtx);
        
        if (isMale) {
            menWaiting++;
            cout << "Person " << id << " (male) wants to enter the bathroom. #Men: " 
                 << menInside << ". #Women: " << womenInside << ".\n";

            cv.wait(lock, [this]() { return womenInside == 0 && menInside < capacity; });

            menWaiting--;
            menInside++;
            cout << "Person " << id << " (male) enters the bathroom. #Men: " 
                 << menInside << ". #Women: " << womenInside << ".\n";
        } else {
            womenWaiting++;
            cout << "Person " << id << " (female) wants to enter the bathroom. #Men: " 
                 << menInside << ". #Women: " << womenInside << ".\n";

            cv.wait(lock, [this]() { return menInside == 0 && womenInside < capacity; });

            womenWaiting--;
            womenInside++;
            cout << "Person " << id << " (female) enters the bathroom. #Men: " 
                 << menInside << ". #Women: " << womenInside << ".\n";
        }

        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(500));  // Simulate bathroom usage
        lock.lock();

        // Exiting the bathroom
        if (isMale) {
            menInside--;
            cout << "Person " << id << " (male) exits the bathroom. #Men: " 
                 << menInside << ". #Women: " << womenInside << ".\n";

            // Allow waiting women to enter only if no men remain
            if (menInside == 0 && womenWaiting > 0) {
                menTurn = false;
                cv.notify_all();
            } else {
                cv.notify_one();
            }
        } else {
            womenInside--;
            cout << "Person " << id << " (female) exits the bathroom. #Men: " 
                 << menInside << ". #Women: " << womenInside << ".\n";

            // Allow waiting men to enter only if no women remain
            if (womenInside == 0 && menWaiting > 0) {
                menTurn = true;
                cv.notify_all();
            } else {
                cv.notify_one();
            }
        }
    }
};

// Thread function
void personThread(UnisexBathroom &bathroom, int id) {
    bool isMale = rand() % 2;  // Randomly assign gender
    bathroom.enterBathroom(id, isMale);
}

int main() {
    srand(time(0)); // Seed random number generator

    UnisexBathroom bathroom;
    vector<thread> people;

    // Create 50 people (randomly assigned male/female)
    for (int i = 0; i < 50; i++) {
        people.emplace_back(personThread, ref(bathroom), i);
    }

    // Join all threads
    for (auto &t : people) {
        t.join();
    }

    return 0;
}
