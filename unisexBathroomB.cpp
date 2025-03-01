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
    condition_variable cvMen, cvWomen;
    int menInside = 0, womenInside = 0;
    int menWaiting = 0, womenWaiting = 0;
    int wCount = 0, mCount = 0;
    int capacity = 3;
    const int switchNum = 10;
    bool menTurn = true;  // Ensures fairness by tracking whose turn it is

public:
    void manEnter(int id) {
        unique_lock<mutex> lock(mtx);
        menWaiting++;

        // Wait if women are inside, bathroom is full, or it's not men's turn
        cvMen.wait(lock, [this]() { 
            return womenInside == 0 && menInside < capacity 
                && menTurn && mCount < switchNum; 
        });

        menWaiting--;
        menInside++;
        mCount++;
        cout << "Man " << id << " entered. (Men inside: " << menInside << ")\n";
    }

    void manExit(int id) {
        unique_lock<mutex> lock(mtx);
        menInside--;
        cout << "Man " << id << " exited. (Men inside: " << menInside << ")\n";

        if (menInside == 0 && (mCount >= switchNum || womenWaiting > 0)) {
            // Force switch to women
            mCount = 0;
            menTurn = false;
            cvWomen.notify_all();
        } else {
            cvMen.notify_one();
        }
    }

    void womanEnter(int id) {
        unique_lock<mutex> lock(mtx);
        womenWaiting++;

        // Wait if men are inside, bathroom is full, or it's not women's turn
        cvWomen.wait(lock, [this]() { 
            return menInside == 0 && womenInside < capacity 
                && !menTurn && wCount < switchNum; 
        });

        womenWaiting--;
        womenInside++;
        wCount++;

        cout << "Woman " << id << " entered. (Women inside: " << womenInside << ")\n";
    }

    void womanExit(int id) {
        unique_lock<mutex> lock(mtx);
        womenInside--;
        cout << "Woman " << id << " exited. (Women inside: " << womenInside << ")\n";

        if (womenInside == 0 && (wCount >= switchNum || menWaiting > 0)) {
            // Force switch to men
            wCount = 0;
            menTurn = true;
            cvMen.notify_all();
        } else {
            cvWomen.notify_one();
        }
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
    for (int i = 0; i < 20; i++) {
        people.push_back(thread(OneMan, ref(bathroom), i + 1));
        people.push_back(thread(OneWoman, ref(bathroom), i + 1));
    }

    // Join all threads
    for (auto &t : people) {
        t.join();
    }

    return 0;
}
