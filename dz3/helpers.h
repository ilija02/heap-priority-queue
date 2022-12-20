#pragma once
#include<iostream>
#include "PriorityQueue.h"

namespace helpers {
	int getSelectedMenuOption(int menu_nr);
	void mainLoop();
	void heapLoop();
	void queueLoop();
	bool nullCheckAndError(Heap* b);
}
