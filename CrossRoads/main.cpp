#include <iostream>
#include "CrossRoads.h"

using namespace std;

int main()
{
	CrossRoads a;
	thread showing(&CrossRoads::show, &a);
	showing.detach();
	thread processNS(&CrossRoads::processNS, &a);
	processNS.detach();
	thread processSW(&CrossRoads::processSW, &a);
	processSW.detach();
	thread controller(&CrossRoads::controller, &a);
	controller.detach();
	a.key();
	return 0;
}