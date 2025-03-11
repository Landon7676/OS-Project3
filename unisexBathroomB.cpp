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
    bool menTurn = true; 
    int consecutiveCount = 0;  // Number of consecutive users of the same gender
    const int maxConsecutiveUsers = 10; // Limit before switching genders

public:
    void enterBathroom(int id, bool isMale) {
        unique_lock<mutex> lock(mtx);

        if (isMale) {
            menWaiting++;
            cout << "Person " << id << " (male) wants to enter. #Men: " 
                 << menInside << ", #Women: " << womenInside << "\n";

            // Wait if the bathroom is occupied by the other gender, if at capacity, 
            // or if men have already reached the consecutive limit
            cv.wait(lock, [this]() { 
                return (womenInside == 0 && menInside < capacity && (menTurn || consecutiveCount < maxConsecutiveUsers));
            });

            menWaiting--;
            menInside++;
            consecutiveCount++;  // Increase consecutive count
            cout << "Person " << id << " (male) enters. #Men: " 
                 << menInside << ", #Women: " << womenInside << "\n";
        } else {
            womenWaiting++;
            cout << "Person " << id << " (female) wants to enter. #Men: " 
                 << menInside << ", #Women: " << womenInside << "\n";

            // Wait if the bathroom is occupied by the other gender, at capacity, 
            // or if women have already reached the consecutive limit
            cv.wait(lock, [this]() { 
                return (menInside == 0 && womenInside < capacity && (!menTurn || consecutiveCount < maxConsecutiveUsers));
            });

            womenWaiting--;
            womenInside++;
            consecutiveCount++;  // Increase consecutive count
            cout << "Person " << id << " (female) enters. #Men: " 
                 << menInside << ", #Women: " << womenInside << "\n";
        }

        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(500));  // Simulate usage
        lock.lock();

        // Exiting the bathroom
        if (isMale) {
            menInside--;
            cout << "Person " << id << " (male) exits. #Men: " 
                 << menInside << ", #Women: " << womenInside << "\n";

            // If men have reached the limit, switch to women
            if (menInside == 0 && (womenWaiting > 0 || consecutiveCount >= maxConsecutiveUsers)) {
                menTurn = false;
                consecutiveCount = 0;  // Reset counter
                cv.notify_all();
            } else {
                cv.notify_one();
            }
        } else {
            womenInside--;
            cout << "Person " << id << " (female) exits. #Men: " 
                 << menInside << ", #Women: " << womenInside << "\n";

            // If women have reached the limit, switch to men
            if (womenInside == 0 && (menWaiting > 0 || consecutiveCount >= maxConsecutiveUsers)) {
                menTurn = true;
                consecutiveCount = 0;  // Reset counter
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
