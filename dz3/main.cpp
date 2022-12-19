#include "Heap.h"

int main() {
	int steps;
	Heap h(3);
	h.add(10, steps);
	h.add(25, steps);
	h.add(20, steps);
	h.add(17, steps);
	h.add(15, steps);
	h.add(19, steps);
	h.add(22, steps);
	h.add(21, steps);
	h.add(23, steps);
	h.add(24, steps);
	std::cout << h;
	//Heap h2(2);
	//h2.add(11, steps);
	//h2.add(14, steps);
	//std::cout << h << std::endl;
	//std::cout << h2 << std::endl;
	//h.merge(h2, steps);
	//std::cout << h << std::endl;
	//h.remove(steps);
	//std::cout << h << std::endl;
}