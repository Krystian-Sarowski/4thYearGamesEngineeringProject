#pragma once
#include <thread>
#include <mutex>
#include <functional>
#include <vector>
#include <queue>
#include <memory>
#include <condition_variable>
#include <iostream>

class ThreadPool
{
public:

	ThreadPool();
	~ThreadPool();

	std::vector<std::thread> m_threadPool;

	void addTask(std::function<void()> t_newTask);
	void cancelAll();
	bool getIsEmpty();
	int getWorkingThreads();

private:

	std::mutex m_poolMutex;						//Mutex used to lock any actions that occur within the threadpool.
	std::queue<std::function<void()>> m_tasks;	//Queue of tasks that need to completed by the threadpool.
	std::condition_variable m_tasksCondition;	//Used to notify threads when a task is aviable.

	bool m_terminatePool{ false };				//Bool for when the pool needs t be terminated.

	int m_workingThreads{ 0 };					//The number of threads that are currently working on a task.

	static void infiniteSpin(ThreadPool& t_threadPool);
};