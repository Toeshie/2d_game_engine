#pragma once
#include "MulticastDelegate.h"
#include <thread>
#include <windows.h>
#include "MathHelper.h"


class BaseHandle {
public:
	virtual ~BaseHandle() = default;
	virtual void stop() = 0;
	virtual void start(float delay, bool bRepeating) = 0;

	virtual bool get_is_active() = 0;

	virtual void execute() = 0;
};


class TimerHandle : public BaseHandle {
private:
	bool is_active_ = false;
	bool should_repeat_ = false;
	unsigned int delay_time_ = 0;

	std::thread worker_thread_;

	ISimpleDelegateInvoker* del_ = nullptr;
public:
	~TimerHandle() override;

	template<class TObject>
	void set(SimpleDelegateMember<TObject>* del, float timed, bool is_repeating) {
		del_ = del;
		delay_time_ = MathHelper::absolute_value(timed);
		should_repeat_ = is_repeating;
	}

	virtual void stop() override;
	virtual void start(float Delay, bool bRepeating) override;
	virtual bool get_is_active() override { return is_active_; }

	bool get_should_repeat() const noexcept { return should_repeat_; }
	void set_should_repeat(bool val) noexcept { should_repeat_ = val; }

	FORCEINLINE ISimpleDelegateInvoker* get_delegate_invoker() const noexcept { return del_; }

	virtual void execute() override;
protected:
	void delay_task();
};

