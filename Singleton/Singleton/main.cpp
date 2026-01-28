// Singleton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ThreadSafeBuffer.h"

void producerFunction(std::string name)
{
    auto& b = ThreadSafeBuffer::getInstance();
    int count = 0;
    while (count++ < 3)
    {
        // Create and push an item
        const std::string item = name + "_item_" + std::to_string(count);
        b.push(name, item);

        // Sleep for 1-6 seconds
        auto sleepSeconds = (std::rand() % 6) + 1;
        std::this_thread::sleep_for(std::chrono::seconds(sleepSeconds));
    }
}

void consumerFunction(std::string name)
{
    auto& b = ThreadSafeBuffer::getInstance();
    int count = 0;
    while (count++ < 3)
    {
        // Retrieve an item
        auto item = b.pop(name);

        // Sleep for 1-6 seconds
        auto sleepSeconds = (std::rand() % 6) + 1;
        std::this_thread::sleep_for(std::chrono::seconds(sleepSeconds));
    }
}


int main()
{
    auto& b = ThreadSafeBuffer::getInstance();
    std::cout << "Starting: " << b.toString() << std::endl;

    std::vector<std::thread> workers;

    // Create some producer threads
    for (int i = 0; i < 3; ++i)
    {
        std::string name = "Cook-" + std::to_string(i);
        workers.emplace_back(producerFunction, name);
    }

    // Create some consumer threads
    for (int i = 0; i < 3; ++i)
    {
        std::string name = "Eater-" + std::to_string(i);
        workers.emplace_back(consumerFunction, name);
    }

    // Join all threads
    for (auto& t : workers)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    std::cout << "Finished: " << b.toString() << std::endl;
}

