#include "Timer.h"

Timer::Timer()
{
	this->time_start = 0;
	this->time_end= 0;
};

void Timer::initializer()
{
	this->time_start = (clock() / 1000);
};

void Timer::increase(int time)
{
	this->time_end = this->time_end + time;
};

void Timer::start(int time)
{
	this->initializer();
	this->time_end = this->time_start + time;
};

void Timer::stop()
{
	this->time_end = 0;
};

int Timer::get_sec_to_end()
{
	this->current_time = (clock() / 1000);
	int sec_to_end = this->time_end - this->current_time;
	if (sec_to_end <= 0)
	{
		return 0;
	}
	else
	{
		return sec_to_end;
	}
};

int Timer::get_sec_from_start()
{
	this->current_time = (clock() / 1000);
	int sec_from_start = this->current_time - this->time_start;
	return sec_from_start;
};

int Timer::get_time()
{
	return (this->time_end - this->time_start);
}

void Sleep(BYTE time)
{
	Sleep((DWORD)time * 1000);
	return;
};