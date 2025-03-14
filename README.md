# **Unisex Bathroom Problem**

## **Part a:**

File: unisexBathroomA.cpp

Compilation: g++ -o unisexBathroomA unisexBathroomA.cpp -std=c++17 -pthread
This ensures C++ 17 features are enabled

Execution: ./unisexBathroomA

Explanation: The program begins in the main function by creating and running 20 threads (10 for men and 10 for women).
Each thread runs the OneMan or OneWoman function, which in turn, calls manEnter or womenEnter. 
The bathroom checks if the entry conditions are satisfied before allowing a man or woman to enter. 
The person enters, uses the bathroom, and then exits which is simulated by useBathroom function. 
When the person exits, the number of peoiple inside the bathroom is updated and other waiting threads are notified thay they can now enter.

Example Output: 

Man 1 entered. (Men inside: 1, Women inside: 0)
Man 3 entered. (Men inside: 2, Women inside: 0)
Man 2 entered. (Men inside: 3, Women inside: 0)
Man 1 exited. (Men inside: 2, Women inside: 0)
Man 5 entered. (Men inside: 3, Women inside: 0)
Man 3 exited. (Men inside: 2, Women inside: 0)
Man 6 entered. (Men inside: 3, Women inside: 0)
Man 2 exited. (Men inside: 2, Women inside: 0)
Man 4 entered. (Men inside: 3, Women inside: 0)
Man 5 exited. (Men inside: 2, Women inside: 0)
Man 9 entered. (Men inside: 3, Women inside: 0)
Man 4 exited. (Men inside: 2, Women inside: 0)
Man 10 entered. (Men inside: 3, Women inside: 0)
Man 10 exited. (Men inside: 2, Women inside: 0)
Man 8 entered. (Men inside: 3, Women inside: 0)
Man 6 exited. (Men inside: 2, Women inside: 0)
Man 7 entered. (Men inside: 3, Women inside: 0)
Man 9 exited. (Men inside: 2, Women inside: 0)
Man 7 exited. (Men inside: 1, Women inside: 0)
Man 8 exited. (Men inside: 0, Women inside: 0)
Woman 8 entered. (Men inside: 0, Women inside: 1)
Woman 9 entered. (Men inside: 0, Women inside: 2)
Woman 6 entered. (Men inside: 0, Women inside: 3)
Woman 6 exited. (Men inside: 0, Women inside: 2)
Woman 1 entered. (Men inside: 0, Women inside: 3)
Woman 8 exited. (Men inside: 0, Women inside: 2)
Woman 4 entered. (Men inside: 0, Women inside: 3)
Woman 9 exited. (Men inside: 0, Women inside: 2)
Woman 5 entered. (Men inside: 0, Women inside: 3)
Woman 4 exited. (Men inside: 0, Women inside: 2)
Woman 3 entered. (Men inside: 0, Women inside: 3)
Woman 1 exited. (Men inside: 0, Women inside: 2)
Woman 2 entered. (Men inside: 0, Women inside: 3)
Woman 2 exited. (Men inside: 0, Women inside: 2)
Woman 10 entered. (Men inside: 0, Women inside: 3)
Woman 3 exited. (Men inside: 0, Women inside: 2)
Woman 7 entered. (Men inside: 0, Women inside: 3)
Woman 10 exited. (Men inside: 0, Women inside: 2)
Woman 5 exited. (Men inside: 0, Women inside: 1)
Woman 7 exited. (Men inside: 0, Women inside: 0)

## **Part b:**

File: unisexBathroomB.cpp

Compilation: g++ -o unisexBathroomB unisexBathroomB.cpp -std=c++17 -pthread
This ensures C++ 17 features are enabled

Execution: ./unisexBathroomB

Explanation: The program creates 50 threads, each with a random gender assigned. Each person calls the enterBathroom function, passing their ID and gender. When a person attempts to enter, they increment either menWaiting or womenWaiting. The progra, then checks the bathroom conditions to see if women or men can enter. Once the conditions are met, the person enters the bathrom and either menInside or womenInside is updated. Bathroom usage is simulated by sleeping the thread. Once a person finishes they exit the bathroom and the appropriate "Inside" variable is decremented. Once there are no people of tjhe current gener left, the program checks if the other gender can enter, allowing only 10 consecutive threads of the same gender.

Example Output:
Person 0 (female) wants to enter the bathroom. #Men: 0. #Women: 0.
Person 0 (female) enters the bathroom. #Men: 0. #Women: 1.
Person 4 (male) wants to enter the bathroom. #Men: 0. #Women: 1.
Person 1 (male) wants to enter the bathroom. #Men: 0. #Women: 1.
Person 2 (male) wants to enter the bathroom. #Men: 0. #Women: 1.
Person 7 (female) wants to enter the bathroom. #Men: 0. #Women: 1.
Person 7 (female) enters the bathroom. #Men: 0. #Women: 2.
Person 5 (male) wants to enter the bathroom. #Men: 0. #Women: 2.
Person 6 (female) wants to enter the bathroom. #Men: 0. #Women: 2.
Person 6 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 3 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 9 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 8 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 11 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 12 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 10 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 13 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 14 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 15 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 16 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 17 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 18 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 19 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 20 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 21 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 22 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 23 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 24 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 25 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 26 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 27 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 28 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 29 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 30 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 31 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 32 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 33 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 34 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 35 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 36 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 37 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 38 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 39 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 40 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 41 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 42 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 43 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 44 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 45 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 46 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 47 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 48 (female) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 49 (male) wants to enter the bathroom. #Men: 0. #Women: 3.
Person 0 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 7 (female) exits the bathroom. #Men: 0. #Women: 1.
Person 6 (female) exits the bathroom. #Men: 0. #Women: 0.
Person 1 (male) enters the bathroom. #Men: 1. #Women: 0.
Person 2 (male) enters the bathroom. #Men: 2. #Women: 0.
Person 9 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 2 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 5 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 1 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 8 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 9 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 11 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 5 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 12 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 8 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 11 (male) exits the bathroom. #Men: 1. #Women: 0.
Person 12 (male) exits the bathroom. #Men: 0. #Women: 0.
Person 16 (male) enters the bathroom. #Men: 1. #Women: 0.
Person 14 (male) enters the bathroom. #Men: 2. #Women: 0.
Person 21 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 21 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 14 (male) exits the bathroom. #Men: 1. #Women: 0.
Person 16 (male) exits the bathroom. #Men: 0. #Women: 0.
Person 24 (female) enters the bathroom. #Men: 0. #Women: 1.
Person 25 (female) enters the bathroom. #Men: 0. #Women: 2.
Person 27 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 25 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 24 (female) exits the bathroom. #Men: 0. #Women: 1.
Person 27 (female) exits the bathroom. #Men: 0. #Women: 0.
Person 30 (female) enters the bathroom. #Men: 0. #Women: 1.
Person 35 (female) enters the bathroom. #Men: 0. #Women: 2.
Person 15 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 35 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 30 (female) exits the bathroom. #Men: 0. #Women: 1.
Person 15 (female) exits the bathroom. #Men: 0. #Women: 0.
Person 34 (male) enters the bathroom. #Men: 1. #Women: 0.
Person 39 (male) enters the bathroom. #Men: 2. #Women: 0.
Person 47 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 39 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 34 (male) exits the bathroom. #Men: 1. #Women: 0.
Person 47 (male) exits the bathroom. #Men: 0. #Women: 0.
Person 40 (female) enters the bathroom. #Men: 0. #Women: 1.
Person 48 (female) enters the bathroom. #Men: 0. #Women: 2.
Person 10 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 40 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 13 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 48 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 18 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 10 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 19 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 13 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 20 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 19 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 17 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 18 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 20 (female) exits the bathroom. #Men: 0. #Women: 1.
Person 17 (female) exits the bathroom. #Men: 0. #Women: 0.
Person 32 (male) enters the bathroom. #Men: 1. #Women: 0.
Person 42 (male) enters the bathroom. #Men: 2. #Women: 0.
Person 44 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 32 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 42 (male) exits the bathroom. #Men: 1. #Women: 0.
Person 44 (male) exits the bathroom. #Men: 0. #Women: 0.
Person 43 (male) enters the bathroom. #Men: 1. #Women: 0.
Person 46 (male) enters the bathroom. #Men: 2. #Women: 0.
Person 4 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 46 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 43 (male) exits the bathroom. #Men: 1. #Women: 0.
Person 4 (male) exits the bathroom. #Men: 0. #Women: 0.
Person 36 (female) enters the bathroom. #Men: 0. #Women: 1.
Person 41 (female) enters the bathroom. #Men: 0. #Women: 2.
Person 45 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 41 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 45 (female) exits the bathroom. #Men: 0. #Women: 1.
Person 36 (female) exits the bathroom. #Men: 0. #Women: 0.
Person 31 (female) enters the bathroom. #Men: 0. #Women: 1.
Person 33 (female) enters the bathroom. #Men: 0. #Women: 2.
Person 38 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 31 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 33 (female) exits the bathroom. #Men: 0. #Women: 1.
Person 38 (female) exits the bathroom. #Men: 0. #Women: 0.
Person 28 (male) enters the bathroom. #Men: 1. #Women: 0.
Person 22 (male) enters the bathroom. #Men: 2. #Women: 0.
Person 3 (male) enters the bathroom. #Men: 3. #Women: 0.
Person 22 (male) exits the bathroom. #Men: 2. #Women: 0.
Person 28 (male) exits the bathroom. #Men: 1. #Women: 0.
Person 3 (male) exits the bathroom. #Men: 0. #Women: 0.
Person 26 (male) enters the bathroom. #Men: 1. #Women: 0.
Person 49 (male) enters the bathroom. #Men: 2. #Women: 0.
Person 49 (male) exits the bathroom. #Men: 1. #Women: 0.
Person 26 (male) exits the bathroom. #Men: 0. #Women: 0.
Person 23 (female) enters the bathroom. #Men: 0. #Women: 1.
Person 29 (female) enters the bathroom. #Men: 0. #Women: 2.
Person 37 (female) enters the bathroom. #Men: 0. #Women: 3.
Person 23 (female) exits the bathroom. #Men: 0. #Women: 2.
Person 37 (female) exits the bathroom. #Men: 0. #Women: 1.
Person 29 (female) exits the bathroom. #Men: 0. #Women: 0.


# **Producer and Consumer Problem**

File: producerConsumer.cpp

Compilation: g++ -o producerConsumer producerConsumer.cpp -pthread -std=c++11
This ensures that there is compatibility with C++11 thread features

Execution: ./producerConsumer <Buffersize> <NumofIterations>

Explanation: This code addresses the producer and consumer problem by reading user inputs, bufferSize and numofIters to begin the code. Initalizing the buffer as a vector size of bufferSize, then initializing the semaphores accordingly, empty = bufferSize, full = 0, and mutex = 1. Following that, we create 3 producer and 3 consumer threads in the main thread, the corresponding threads then run through their respective fields(producer/consumer). Lastly, clean up the semaphores before exiting.

Example Output: 
./producerConsumer 10 5
Produced 0 produced 0 at index 0
Produced 1 produced 0 at index 1
Produced 2 produced 0 at index 2
Consumer 1 consumed 0 from index 0
Consumer 0 consumed 0 from index 1
Consumer 2 consumed 0 from index 2
Produced 1 produced 1 at index 3
Produced 0 produced 1 at index 4
Produced 2 produced 1 at index 5
Consumer 0 consumed 1 from index 3
Consumer 2 consumed 1 from index 4
Consumer 1 consumed 1 from index 5
Produced 0 produced 2 at index 6
Produced 1 produced 2 at index 7
Produced 2 produced 2 at index 8
Consumer 0 consumed 2 from index 6
Consumer 1 consumed 2 from index 7
Consumer 2 consumed 2 from index 8
Produced 2 produced 3 at index 9
Produced 1 produced 3 at index 0
Produced 0 produced 3 at index 1
Produced 0 produced 4 at index 2
Produced 1 produced 4 at index 3
Produced 2 produced 4 at index 4
Consumer 0 consumed 3 from index 9
Consumer 2 consumed 3 from index 0
Consumer 1 consumed 3 from index 1
Consumer 1 consumed 4 from index 2
Consumer 2 consumed 4 from index 3
Consumer 0 consumed 4 from index 4
Consumer 0 total: 10
Consumer 2 total: 10
Consumer 1 total: 10


# **Savings Account Problem**

## **Part c:**

Compliation: g++ -o savingsAccountC savingsAccountC.cpp -std=c++17 -pthread
This ensures C++ 17 features are enabled

Execution: ./savingsAccountC

Explanation: The bankAccount class represernts a simple bank account where multiple threads can deposit and withdraw money. The deposit method locks the mutex and increases the balance while the withdraw method also locks the mutex while deducting the amount frombalance. The getBalance then returns the current balance. The customer function creates the customer threads that will either desposit or withdraw a random amount between (50-300). The runTest function hadnles a variety of test cases, creating threads for customer actions. Finally the main simply asks the user for a test case (1-5) and runs it.

## **Part d:**

Compliation: g++ -o savingsAccountD savingsAccountD.cpp -std=c++17 -pthread
This ensures c++17 features are enabled

Execution: ./savingsAccountD

Explanation: Similary to partC, the BankAccount class contains the deposit, withdraw, and getBalance functions. The main difference is the use of a queue with stores withdrawal requests in order. The deposit function now notofies the first request in the queue if there is sufficient funds in the bank account. The withdrawal function creates a condition variable for the withdrawal and pushes the request into the wait_queue. The request will wait in the queue if it is not first or the balance is insufficient. The customer function generates a random number and randomly chooses to deposit or withdraw. Finally, the runTest function declares the test caes and the main calls upon them based on user input.
