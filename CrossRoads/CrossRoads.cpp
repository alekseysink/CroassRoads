#include "CrossRoads.h"
#include <iostream>
#include <conio.h>

const string STATE[4] = { "BLINKING_YELLOW", "RED            ", "YELLOW         ", "GREEN          " };
const int BLINKING_YELLOW = 0, RED = 1, YELLOW = 2, GREEN = 3;


void CrossRoads::show()
{
	while (true)
	{
		system("cls");
		string result = "NS State: " + STATE[this->NS.state] + " Stream: " + to_string(this->NS.stream) + " Time to next color: " + to_string(this->NS.time.get_sec_to_end()) + "\n";
		result = result + "SW State: " + STATE[this->SW.state] + " Stream: " + to_string(this->SW.stream) + " Time to next color: " + to_string(this->SW.time.get_sec_to_end()) + "\n";
		cout << result;
		Sleep((BYTE)1);
	}
}
CrossRoads::CrossRoads()
{
	this->NS.state = BLINKING_YELLOW;
	this->SW.state = BLINKING_YELLOW;
	this->NS.stream = 0;
	this->SW.stream = 0;
	this->state = false;
}
void CrossRoads::key()
{
	int key = 0;
	while (true){
		key = _getch();
		if (key == 32)
		{
			this->state = !this->state;
		}
		else if (key == 72)
		{
			this->NS.stream = !this->NS.stream;
		}
		else if (key == 80)
		{
			this->SW.stream = !this->SW.stream;
		}
	}
}
void CrossRoads::processNS()
{
	while (true)
	{ 
		if (this->state)
		{
			if (this->NS.time.get_sec_to_end() == 0){
				if (this->NS.state == RED)
				{
					this->NS.state = YELLOW;
					this->NS.previous_state = RED;
					this->NS.time.start(2);
				}
				else if (this->NS.state == GREEN)
				{
					this->NS.stream = false;
					this->NS.state = YELLOW;
					this->NS.previous_state = GREEN;
					this->NS.time.start(2);
				}
				else if (this->NS.state == YELLOW && this->NS.previous_state == RED)
				{
					this->NS.state = GREEN;
					this->NS.previous_state = YELLOW;
					this->NS.time.start(15);
				}
				else if (this->NS.state == YELLOW && this->NS.previous_state == GREEN)
				{
					this->NS.state = RED;
					this->NS.previous_state = YELLOW;
					this->NS.time.start(19);
				}
				else if (this->NS.state == BLINKING_YELLOW)
				{
					this->NS.state = RED;
					this->NS.previous_state = BLINKING_YELLOW;
					this->NS.time.start(17);
				}
			}
		} else
		{
			this->NS.state = BLINKING_YELLOW;
			this->NS.stream = false;
			this->NS.time.stop();
		}
		Sleep((BYTE)0.5);
	};
}
void CrossRoads::processSW()
{
	while (true)
	{
		if (this->state)
		{
			if (this->SW.time.get_sec_to_end() == 0){
				if (this->SW.state == GREEN)
				{
					this->SW.stream = false;
					this->SW.state = YELLOW;
					this->SW.previous_state = GREEN;
					this->SW.time.start(2);
				}
				else if (this->SW.state == RED)
				{
					this->SW.state = YELLOW;
					this->SW.previous_state = RED;
					this->SW.time.start(2);
				}
				else if (this->SW.state == YELLOW && this->SW.previous_state == GREEN)
				{
					this->SW.state = RED;
					this->SW.previous_state = YELLOW;
					this->SW.time.start(19);
				}
				else if (this->SW.state == YELLOW && this->SW.previous_state == RED)
				{
					this->SW.state = GREEN;
					this->SW.previous_state = YELLOW;
					this->SW.time.start(15);
				}
				else if (this->SW.state == BLINKING_YELLOW)
				{
					this->SW.state = GREEN;
					this->SW.previous_state = BLINKING_YELLOW;
					this->SW.time.start(15);
				}
			}

		}
		else
		{
			this->SW.state = BLINKING_YELLOW;
			this->SW.stream = false;
			this->SW.time.stop();
		}
		Sleep((BYTE)0.5);
	};
}
void CrossRoads::controller()
{
	while (true)
	{
		if ((this->NS.state == RED && this->SW.state == GREEN) || (this->SW.state == RED && this->NS.state == GREEN))
		{
			if (this->NS.stream && this->NS.state == GREEN && this->NS.time.get_sec_to_end() < 5)
			{
				this->NS.time.increase(5);
				this->SW.time.increase(5);
				Sleep((BYTE)5);
				this->NS.stream = false;
			}
			if (this->SW.stream && this->SW.state == GREEN && this->SW.time.get_sec_to_end() < 5)
			{
				this->NS.time.increase(5);
				this->SW.time.increase(5);
				Sleep((BYTE)5);
				this->SW.stream = false;
			}
			if (this->NS.stream && this->NS.state == GREEN && this->NS.time.get_sec_to_end() > 5)
			{
				Sleep((BYTE)5);
				this->NS.stream = false;
			}
			if (this->SW.stream && this->SW.state == GREEN && this->SW.time.get_sec_to_end() > 5)
			{
				Sleep((BYTE)5);
				this->SW.stream = false;
			}
			if (this->NS.stream && this->NS.state == RED && !this->SW.stream && this->NS.time.get_sec_from_start() <= 15)
			{
				this->SW.time.stop();
				Sleep((BYTE)2);
				this->NS.time.stop();
				Sleep((BYTE)7);
				this->NS.stream = false;
			}
			if (this->SW.stream && this->SW.state == RED && !this->NS.stream && this->SW.time.get_sec_from_start() <= 15)
			{
				this->NS.time.stop();
				Sleep((BYTE)2);
				this->SW.time.stop();
				Sleep((BYTE)7);
				this->SW.stream = false;
			}
		};
		Sleep((BYTE)0.5);
	}
};