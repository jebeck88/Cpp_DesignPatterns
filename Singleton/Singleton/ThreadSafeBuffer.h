#pragma once
#ifndef THREADSAFEBUFFER_H
#define THREADSAFEBUFFER_H

#include <semaphore>
#include <mutex>
#include <string>
#include <queue>

/// <summary>
/// A thread safe buffer managed as a singleton
/// </summary>
class ThreadSafeBuffer
{

public:
	// Retrieves the singleton instance
	static ThreadSafeBuffer& getInstance();

	// dtor
	~ThreadSafeBuffer() = default;

	// Buffer capacity
	static const std::ptrdiff_t CAPACITY = 3;

public:
	// Append to the buffer, and blocks the caller until a slot is available
	void push(std::string& name, std::string s);

	// Removes from the buffer, and blocks the caller until an item is available
	std::string pop(std::string& name);

	// Returns the item count
	int count() const;

	// toString
	std::string toString() const;

private:
	// no public objects
	ThreadSafeBuffer() = default;

	// no copies
	ThreadSafeBuffer(const ThreadSafeBuffer&) = delete;
	ThreadSafeBuffer& operator=(const ThreadSafeBuffer&) = delete;
	ThreadSafeBuffer(ThreadSafeBuffer&&) = delete;


private:
	// A mutex
	mutable std::mutex m_mutex;

	// Counting semaphors for slots and items
	std::counting_semaphore<CAPACITY> m_slotsSemaphore{ CAPACITY };
	std::counting_semaphore<CAPACITY> m_itemsSemaphore{ 0 };

	// The buffer
	std::queue<std::string> m_buffer;
};

#endif

