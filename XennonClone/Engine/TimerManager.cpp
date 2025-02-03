#include "TimerManager.h"
#include <mutex>

std::vector<TimerHandle*> TimerManager::execution_row_;
std::vector<TimerHandle*> TimerManager::created_handles_;
ThreadPool* TimerManager::thread_pool_ = nullptr;

static std::mutex m_HandlesMutex;

void TimerManager::execute_handles()
{
	std::lock_guard<std::mutex> lock(m_HandlesMutex);
	for (int i = 0; i < execution_row_.size(); ++i) {
		auto* handle = execution_row_[i];
		
		if (handle->get_is_active()) {
			handle->execute();
		} else {
			__InternalRemoveHandle(handle);
			delete handle;
		}
		
		execution_row_.erase(execution_row_.begin() + i);
	}
}

void TimerManager::add_handle_to_execution(TimerHandle* handle)
{
	std::lock_guard<std::mutex> lock(m_HandlesMutex);
	if (handle) {
		execution_row_.push_back(handle);
	}
}

void TimerManager::__InternalRemoveHandle(TimerHandle* handle)
{
	if (!handle) return;
	
	for (int i = 0; i < created_handles_.size(); ++i) {
		if (created_handles_[i] == handle) {
			created_handles_.erase(created_handles_.begin() + i);
			return;
		}
	}
}
