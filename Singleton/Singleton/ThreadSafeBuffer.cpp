#include "ThreadSafeBuffer.h"

#include <exception>
#include <iostream>
#include <string>
#include <sstream>

ThreadSafeBuffer& ThreadSafeBuffer::getInstance()
{
	// static instance created in a thread-safe way
	static ThreadSafeBuffer s_instance;
	return s_instance;
}

void ThreadSafeBuffer::push(std::string& name, std::string item)
{
	m_slotsSemaphore.acquire();
	std::lock_guard<std::mutex> guard(m_mutex);
	m_buffer.push(item);
	m_itemsSemaphore.release();

	std::cout << "\"" << name << "\" cooked item \"" << item << "\"" << std::endl;
}

std::string ThreadSafeBuffer::pop(std::string& name)
{
	m_itemsSemaphore.acquire();
	std::lock_guard<std::mutex> guard(m_mutex);
	std::string item = m_buffer.front();
	m_buffer.pop();
	m_slotsSemaphore.release();

	std::cout << "   \"" << name << "\" ate item \"" << item << "\"" << std::endl;

	return item;
}

int ThreadSafeBuffer::count() const
{
	std::lock_guard<std::mutex> guard(m_mutex);

	return static_cast<int>(m_buffer.size());
}

std::string ThreadSafeBuffer::toString() const
{
	std::lock_guard<std::mutex> guard(m_mutex);

	auto bufferCopy = m_buffer;

	std::ostringstream oss;
	oss << "[";
	while (!bufferCopy.empty())
	{
		oss << bufferCopy.front();
		bufferCopy.pop();
		if (!bufferCopy.empty())
		{
			oss << ", ";
		}
	}
	oss << "]";
	return oss.str();
}
