#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>

// BankAccount class simulates a simple bank account with thread-safe deposits and withdrawals.
class BankAccount {
private:
    int balance;
    std::mutex mtx;
    std::condition_variable cv;

public:
    BankAccount() : balance(0) {}

    // Deposits a specified amount into the account
    void deposit(int amount) {
        std::unique_lock<std::mutex> lock(mtx);
        balance += amount;
        std::cout << "Deposit: " << amount << ". New Balance: " << balance << std::endl;
        cv.notify_all();
    }

    // Withdraws a specified amount from the account, ensuring sufficient balance
    void withdraw(int amount) {
        std::unique_lock<std::mutex> lock(mtx);
        while (balance < amount) {
            std::cout << "Withdraw request: " << amount << " (Waiting). Balance: " << balance << std::endl;
            cv.wait(lock);
        }
        balance -= amount;
        std::cout << "Withdraw: " << amount << ". New Balance: " << balance << std::endl;
    }

    // Returns the current balance
    int getBalance() {
        std::unique_lock<std::mutex> lock(mtx);
        return balance;
    }
};

// Function to simulate a bank customer performing transactions
void customer(BankAccount &account, int id, bool forceWithdraw = false, int fixedAmount = -1) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> action(0, 1); // 0 for withdraw, 1 for deposit
    std::uniform_int_distribution<int> amount(50, 300);

    int transaction = (fixedAmount > 0) ? fixedAmount : amount(gen);

    // Randomly decide between deposit and withdrawal (unless forced)
    if (forceWithdraw || action(gen) == 0) {
        std::cout << "Customer " << id << " wants to withdraw " << transaction << "." << std::endl;
        account.withdraw(transaction);
    } else {
        std::cout << "Customer " << id << " deposits " << transaction << "." << std::endl;
        account.deposit(transaction);
    }
}

// Function to run different test cases
void runTest(int testNumber) {
    BankAccount account;
    std::vector<std::thread> customers;

    std::cout << "\nRunning Test Case " << testNumber << "...\n" << std::endl;

    switch (testNumber) {
        case 1: // Basic Functionality
            for (int i = 0; i < 10; ++i) {
                customers.emplace_back(customer, std::ref(account), i, false, -1);
            }
            break;

        case 2: // Withdraw Before Deposit
            for (int i = 0; i < 10; ++i) {
                customers.emplace_back(customer, std::ref(account), i, true, -1);
            }
            break;

        case 3: // Large Deposits and Withdrawals
            for (int i = 0; i < 5; ++i) {
                customers.emplace_back(customer, std::ref(account), i, false, 1000);
            }
            for (int i = 5; i < 10; ++i) {
                customers.emplace_back(customer, std::ref(account), i, true, 800);
            }
            break;

        case 4: // High Contention (Simultaneous Transactions)
            for (int i = 0; i < 20; ++i) {
                customers.emplace_back(customer, std::ref(account), i, false, -1);
            }
            break;

        case 5: // Continuous Deposits and Withdrawals
            for (int i = 0; i < 10; ++i) {
                customers.emplace_back([&account, i]() {
                    for (int j = 0; j < 5; ++j) {
                        customer(account, i, false, -1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    }
                });
            }
            break;

        default:
            std::cout << "Invalid test case number." << std::endl;
            return;
     }

    for (auto &t : customers) {
        t.join();
    }

    // Display the final balance after all transactions
    std::cout << "Final Balance: " << account.getBalance() << "\n" << std::endl;
}



int main() {
    int testNumber;
    std::cout << "Enter test case number (1-5): ";
    std::cin >> testNumber;
    runTest(testNumber);
    return 0;
}
