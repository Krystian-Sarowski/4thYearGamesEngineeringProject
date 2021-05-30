#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	std::cout << std::thread::hardware_concurrency() << std::endl;
	int numThreads = 10;

	for (int i = 0; i < numThreads; i++)
	{
		m_threadPool.push_back(std::thread(infiniteSpin, std::ref(*this)));
	}
}

ThreadPool::~ThreadPool()
{
    m_terminatePool = true; // use this flag in condition.wait

    m_tasksCondition.notify_all(); // wake up all threads.

    // Join all threads.
    for(std::thread &everyThread : m_threadPool)
    {   
		everyThread.join();
	}

	while (!m_tasks.empty())
	{
		m_tasks.pop();
	}

    m_threadPool.clear();  
}

void ThreadPool::infiniteSpin(ThreadPool& t_threadPool)
{
	while (true)
	{
		std::function<void()> task = std::function<void()>();
		bool gotTask = false;

		std::unique_lock<std::mutex> lock(t_threadPool.m_poolMutex);
		t_threadPool.m_tasksCondition.wait(lock, [&] {return !t_threadPool.m_tasks.empty() || t_threadPool.m_terminatePool; });

		if (!t_threadPool.m_terminatePool && !t_threadPool.m_tasks.empty())
		{
			task = t_threadPool.m_tasks.front();
			t_threadPool.m_tasks.pop();
			gotTask = true;
			t_threadPool.m_workingThreads++;
		}
		lock.unlock();

		if (gotTask)
		{
			task();
		}

		lock.lock();
		t_threadPool.m_workingThreads--;
		lock.unlock();
	}
}

void ThreadPool::addTask(std::function<void()> t_newTask)
{
	std::unique_lock<std::mutex> lock(m_poolMutex);
	m_tasks.push(t_newTask);
	lock.unlock();

	m_tasksCondition.notify_one();
}

void ThreadPool::cancelAll()
{
	std::unique_lock<std::mutex> lock(m_poolMutex);
	while (!m_tasks.empty())
	{
		m_tasks.pop();
	}
}

bool ThreadPool::getIsEmpty()
{
	std::unique_lock<std::mutex> lock(m_poolMutex);
	return m_tasks.size() == 0;
}

int ThreadPool::getWorkingThreads()
{
	std::unique_lock<std::mutex> lock(m_poolMutex);
	return m_workingThreads;
}
