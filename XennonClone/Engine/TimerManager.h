#pragma once
#include <vector>
#include <iostream>
#include "Timer.h"
#include "ThreadPool.h"

class TimerManager
{
private:
	static std::vector<TimerHandle*> created_handles_;
	static std::vector<TimerHandle*> execution_row_;
	static ThreadPool* thread_pool_;

	static void __InternalRemoveHandle(TimerHandle* handle);

public:
	TimerManager() = delete;
	TimerManager(const TimerManager&) = delete;
	TimerManager& operator=(const TimerManager&) = delete;

	static void initialize() {
		thread_pool_ = new ThreadPool();
	}

	static void shutdown() {
		delete thread_pool_;
		thread_pool_ = nullptr;
	}

	template <class T>
	static TimerHandle* create_timer(T* obj, void (T::* method)(), float time, bool binfinite, bool bAutoStart)
	{
		auto* del = new SimpleDelegateMember<T>(obj, method);
		auto* handle = new TimerHandle();
		handle->set(del, time, binfinite);
		
		if (bAutoStart) {
			handle->start(time, binfinite);
		}
		
		created_handles_.push_back(handle);
		return handle;
	}

	static void execute_handles();

	static void add_handle_to_execution(TimerHandle* handle);

	template<class T>
	static void stop_timer_with(T* obj, void (T::* method)());

	static void enqueue_task(std::function<void()> task) {
		if (thread_pool_) {
			thread_pool_->enqueue_task(std::move(task));
		}
	}
};

template<class T>
inline void TimerManager::stop_timer_with(T* obj, void(T::* method)())
{
	for (int i = 0; i < created_handles_.size(); ++i) {
		if (auto* del = created_handles_[i]->get_delegate_invoker()) {
			if (auto* del_casted = dynamic_cast<SimpleDelegateMember<T>*>(del)) {
				if (del_casted->Equals(obj, method)) {
					created_handles_[i]->stop();
				}
			}
		}
	}
}
