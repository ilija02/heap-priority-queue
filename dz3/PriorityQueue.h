#pragma once
#include<random>
#include<fstream>
#include "Heap.h"

class PriorityQueue {
	friend class Benchmark;
private:
	Heap h;
	void changeOrder(int new_m) { h.convert(new_m); }
public:
	PriorityQueue(int m = 2) :h(m) {}
	bool empty() { return h.size == 0; }
	/// <summary>
	/// Removes the element at the front of the queue
	/// </summary>
	/// <param name="steps"></param>
	/// <returns>Fron of the queue</returns>
	int poll(int& steps) { return h.remove(steps); }
	/// <summary>
	/// Removes the element at the front of the queue without returning it
	/// </summary>
	/// <param name="steps">Number of steps that took for operation to finish</param>
	void remove(int& steps) { h.remove(steps); }
	int peek() { return h.peek(); }
	void add(int item, int& steps) { h.add(item, steps); }
	void load_from_file(const char* filename, int& steps);
	void load_random(int count, int a, int b, int& steps);
};

