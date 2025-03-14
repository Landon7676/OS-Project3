#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>
#include <chrono>

class BankAccount
{
private:
    int balance;
    std::mutex mtx; // Mutex to ensure thread-safe access to balance
    std::condition_variable cv;
    std::queue<std::pair<int, std::condition_variable *>> wait_queue; // Queue for withdrawal requests

public:
    BankAccount() : balance(0) {}

    // Deposit function to add money to the account
    void deposit(int amount)
    {
        std::unique_lock<std::mutex> lock(mtx);
        balance += amount;
        std::cout << "Deposit: " << amount << ". New Balance: " << balance << std::endl;

        // Notify the first waiting withdrawal request (if any)
        if (!wait_queue.empty())
        {
            wait_queue.front().second->notify_one();
        }
    }

    // Withdraw function, ensuring that withdrawals only proceed if funds are available
    void withdraw(int amount)
    {
        std::unique_lock<std::mutex> lock(mtx);
        std::condition_variable cv_local;
        wait_queue.push({amount, &cv_local});

        // Wait until it's the turn of this request and there are enough funds
        while (wait_queue.front().first != amount || balance < amount)
        {
            std::cout << "Withdraw request: " << amount << " (Waiting in queue). Balance: " << balance << std::endl;
            cv_local.wait(lock);
        }

        // Process withdrawal
        wait_queue.pop();
        balance -= amount;
        std::cout << "Withdraw: " << amount << ". New Balance: " << balance << std::endl;

        // Notify the next waiting withdrawal request, if any
        if (!wait_queue.empty())
        {
            wait_queue.front().second->notify_one();
        }
    }

    // Returns the current account balance
    int getBalance()
    {
        std::unique_lock<std::mutex> lock(mtx);
        return balance;
    }
};

// Simulates a customer interacting with the bank account
void customer(BankAccount &account, int id, bool forceWithdraw = false, int fixedAmount = -1)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> action(0, 1); // 0 for withdraw, 1 for deposit
    std::uniform_int_distribution<int> amount(50, 300);

    // Use a fixed amount if specified; otherwise, generate a random amount
    int transaction = (fixedAmount > 0) ? fixedAmount : amount(gen);
    
    // Determine whether the customer deposits or withdraws
    if (forceWithdraw || action(gen) == 0)
    {
        std::cout << "Customer " << id << " wants to withdraw " << transaction << "." << std::endl;
        account.withdraw(transaction);
    }
    else
    {
        std::cout << "Customer " << id << " deposits " << transaction << "." << std::endl;
        account.deposit(transaction);
    }
}

// Runs a test scenario based on the test case number
void runTest(int testNumber)
{
    BankAccount account;
    std::vector<std::thread> customers;

    std::cout << "\nRunning Test Case " << testNumber << "...\n"
              << std::endl;

    switch (testNumber)
    {
    case 1: // Basic Functionality
        for (int i = 0; i < 10; ++i)
        {
            customers.emplace_back(customer, std::ref(account), i, false, -1);
        }
        break;

    case 2: // Withdraw Before Deposit
        for (int i = 0; i < 10; ++i)
        {
            customers.emplace_back(customer, std::ref(account), i, true, -1);
        }
        break;

    case 3: // Large Deposits and Withdrawals
        for (int i = 0; i < 5; ++i)
        {
            customers.emplace_back(customer, std::ref(account), i, false, 1000);
        }
        for (int i = 5; i < 10; ++i)
        {
            customers.emplace_back(customer, std::ref(account), i, true, 800);
        }
        break;

    case 4: // High Contention (Simultaneous Transactions)
        for (int i = 0; i < 20; ++i)
        {
            customers.emplace_back(customer, std::ref(account), i, false, -1);
        }
        break;

    case 5: // Continuous Deposits and Withdrawals
        for (int i = 0; i < 10; ++i)
        {
            customers.emplace_back([&account, i]()
                                   {
                    for (int j = 0; j < 5; ++j) {
                        customer(account, i, false, -1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    } });
        }
        break;

    default:
        std::cout << "Invalid test case number." << std::endl;
        return;
    }

    for (auto &t : customers)
    {
        t.join();
    }

    // Display the final balance after all transactions
    std::cout << "Final Balance: " << account.getBalance() << "\n"
              << std::endl;
}

int main()
{
    int testNumber;
    std::cout << "Enter test case number (1-5): ";
    std::cin >> testNumber;
    runTest(testNumber);
    return 0;
}
