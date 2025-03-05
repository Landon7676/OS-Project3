#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>

class BankAccount {
private:
    int balance;
    std::mutex mtx;
    std::condition_variable cv;

public:
    BankAccount() : balance(0) {}

    void deposit(int amount) {
        std::unique_lock<std::mutex> lock(mtx);
        balance += amount;
        std::cout << "Deposit: " << amount << ". New Balance: " << balance << std::endl;
        cv.notify_all();
    }

    void withdraw(int amount) {
        std::unique_lock<std::mutex> lock(mtx);
        while (balance < amount) {
            std::cout << "Withdraw request: " << amount << " (Waiting). Balance: " << balance << std::endl;
            cv.wait(lock);
        }
        balance -= amount;
        std::cout << "Withdraw: " << amount << ". New Balance: " << balance << std::endl;
    }
};

void customer(BankAccount &account, int id) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> action(0, 1); // 0 for withdraw, 1 for deposit
    std::uniform_int_distribution<int> amount(50, 300);

    int transaction = amount(gen);
    if (action(gen) == 0) {
        std::cout << "Customer " << id << " wants to withdraw " << transaction << "." << std::endl;
        account.withdraw(transaction);
    } else {
        std::cout << "Customer " << id << " deposits " << transaction << "." << std::endl;
        account.deposit(transaction);
    }
}

int main() {
    BankAccount account;
    std::vector<std::thread> customers;
    
    for (int i = 0; i < 10; ++i) {
        customers.emplace_back(customer, std::ref(account), i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small delay for better output visibility
    }

    for (auto &t : customers) {
        t.join();
    }

    return 0;
}
