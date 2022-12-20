#pragma once
#define INITIAL_CAP 8
#define SCALE_FACTOR 2
#include <iostream>
#include<cmath>
#include<cstdio>
#include<iomanip>

class Heap
{
	friend class PriorityQueue;
private:
	#pragma region FIELDS
	int m;
	int capacity;
	int size=0;
	int* items = nullptr;
	#pragma endregion
	#pragma region methods
	void init(int m);
	void destroy();
	int get_child_idx(int father_idx, int child_nr) { return father_idx * m + child_nr; }
	int get_parent_idx(int child_idx) { return (child_idx - 1) / m; }
	bool has_child(int father_idx, int child_nr) { return child_nr <= m && get_child_idx(father_idx, child_nr) < size; }
	bool has_parent(int child_idx) { return child_idx >= 0 && child_idx < size; }
	int min_child_idx(int father_idx, int& steps);
	/// <summary>
	/// Gets the i-th child
	/// </summary>
	/// <param name="father_idx">Index of the father "node"</param>
	/// <param name="child_nr">value between [1-m]</param>
	/// <returns></returns>
	int get_child(int father_idx, int child_nr);
	int get_parent(int child_idx);
	void resize_if_needed();
	void heapify_down(int& steps);
	void heapify_up(int& steps);
	#pragma endregion
public:
	Heap() = default;
	Heap(int m);
	Heap(const Heap&) = delete;
	Heap& operator=(const Heap&) = delete;
	//TODO add Copy, Move constructors and assignment operators
	~Heap();
	#pragma region methods
	void add(int item, int& steps);
	int peek() const;
	int remove(int& steps);
	int remove(int key, int& steps);
	/// <summary>
	/// Changes the degree of the m-ary heap
	/// </summary>
	/// <param name="new_m">The new degree</param>
	void convert(int new_m);
	void merge(Heap& h, int& steps);
	#pragma endregion
	friend std::ostream& operator<<(std::ostream& os, Heap& h);
};

