#include <string>
#include "Timer.h"

struct TrafficLight
{
	int state;
	int previous_state;
	bool stream;
	Timer time;
};

class CrossRoads
{
public:
	TrafficLight NS, SW;
	bool state;
	CrossRoads();
	void show();
	void key();
	void processNS();
	void processSW();
	void controller();

};