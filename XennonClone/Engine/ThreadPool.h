#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
private:
	std::vector<std::thread> workers_;
	std::queue<std::function<void()>> tasks_;

	std::mutex queue_mutex_;
	std::condition_variable condition_;
	bool stop_ = false;

public:
	explicit ThreadPool(size_t threads = std::thread::hardware_concurrency());
	~ThreadPool();

	// Delete copy constructor and assignment operator
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;

	template<class F>
	void enqueue_task(F&& f) {
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			tasks_.emplace(std::forward<F>(f));
		}
		condition_.notify_one();
	}
};
