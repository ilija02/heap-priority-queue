#include "PriorityQueue.h"

void PriorityQueue::load_from_file(std::string& filename, int& steps){
	steps = 0;
	int curr_steps;
	std::ifstream in(filename);
	while (true) {
		int x;
		in >> x;
		if (in.fail()) break;
		this->add(x, curr_steps);
		steps += curr_steps;
	}
}

void PriorityQueue::load_random(int count, int a, int b, int& steps){
	steps=0;
	int curr_steps;
	std::random_device rd;
	std::mt19937 gen(rd());
	// Define the distribution
	std::uniform_int_distribution<> dis(a, b);
	for (int i = 0; i < count; i++) {
		this->add(dis(gen), curr_steps);
		//this->add(1, curr_steps);
		steps += curr_steps;
	}
}
