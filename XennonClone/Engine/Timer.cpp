#include "Timer.h"
#include "TimerManager.h"
#include <chrono>

TimerHandle::~TimerHandle()
{
	delete del_;
}

void TimerHandle::stop()
{
	is_active_ = false;
}

void TimerHandle::start(float Delay /*Time in seconds*/, bool bRepeating)
{
	if (is_active_) return;

	delay_time_ = MathHelper::absolute_value(Delay);
	is_active_ = true;
	should_repeat_ = bRepeating;

	// Use thread pool instead of creating new thread
	TimerManager::enqueue_task([this]() {
		delay_task();
	});
}

void TimerHandle::delay_task()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(delay_time_ * 1000)));
	TimerManager::add_handle_to_execution(this);
}

void TimerHandle::execute()
{
	if (del_) {
		del_->Execute();
	}
	
	is_active_ = should_repeat_;
	
	if (is_active_) {
		// Use thread pool for repeating tasks
		TimerManager::enqueue_task([this]() {
			delay_task();
		});
	}
	else {
		delete this;
	}
}

