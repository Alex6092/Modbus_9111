#pragma once

#include <Windows.h>
#include <queue>

template<typename T>
class ThreadSafeQueue
{
	HANDLE mutex;
	std::queue<T> queue;

public:
	ThreadSafeQueue();
	~ThreadSafeQueue();

	void Add(T elem);
	T Get();
	size_t Size();
};

template<typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
{
	mutex = CreateMutex(NULL, FALSE, NULL);
}

template<typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue()
{
	ReleaseMutex(mutex);
}

template<typename T>
void ThreadSafeQueue<T>::Add(T elem)
{
	WaitForSingleObject(mutex, INFINITE);
	queue.push(elem);
	ReleaseMutex(mutex);
}

template<typename T>
T ThreadSafeQueue<T>::Get()
{
	T res;

	WaitForSingleObject(mutex, INFINITE);

	if (queue.size() == 0)
	{
		ReleaseMutex(mutex);
		throw std::exception("Empty queue");
	}

	res = queue.front();
	queue.pop();

	ReleaseMutex(mutex);

	return res;
}

template<typename T>
size_t ThreadSafeQueue<T>::Size()
{
	size_t size;
	WaitForSingleObject(mutex, INFINITE);
	size = queue.size();
	ReleaseMutex(mutex);
	return size;
}