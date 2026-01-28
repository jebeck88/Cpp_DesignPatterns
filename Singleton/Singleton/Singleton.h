#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H


/// <summary>
/// Template for a singleton 
/// </summary>
/// <typeparam name="T">The singleton type</typeparam>
template<typename T>
class Singleton
{
public:
	static T& getInstance()
	{
		static T s_myInstance;

		return s_myInstance;
	}

private:
	// No instances
	Singleton() = delete;

};

#endif

