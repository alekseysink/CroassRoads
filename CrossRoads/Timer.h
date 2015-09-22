#include <windows.h>
#include <thread>
using namespace std;

class Timer
{
private:
	int time_start = 0;
	int time_end = 0;
	int current_time = 0;
public:
	Timer();
	void initializer();
	int get_sec_to_end();
	int get_sec_from_start();
	int get_time();
	void start(int time);
	void stop();
	void increase(int time);
};

void Sleep(BYTE time);