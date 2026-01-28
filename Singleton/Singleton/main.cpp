// Singleton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ThreadSafeBuffer.h"

void producerFunction(std::string name)
{
    int count = 0;
    while (count++ < 3)
    {
        const std::string item = name + "_item_" + std::to_string(count);
        auto& b = ThreadSafeBuffer::getInstance();
        b.push(name, item);

        auto sleepSeconds = (std::rand() % 6) + 1;
        std::this_thread::sleep_for(std::chrono::seconds(sleepSeconds));
    }
}

void consumerFunction(std::string name)
{
    int count = 0;
    while (count++ < 3)
    {
        auto& b = ThreadSafeBuffer::getInstance();
        auto item = b.pop(name);

        auto sleepSeconds = (std::rand() % 6) + 1;
        std::this_thread::sleep_for(std::chrono::seconds(sleepSeconds));
    }
}


int main()
{
    auto& b = ThreadSafeBuffer::getInstance();
    std::cout << "Starting: " << b.toString() << std::endl;

    std::vector<std::thread> workers;

    // Create some producers
    for (int i = 0; i < 3; ++i)
    {
        std::string name = "Cook-" + std::to_string(i);
        workers.emplace_back(producerFunction, name);
    }

    // Create some consumers
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

