#pragma once
#include<vector>
#include<thread>
#include<chrono>
#include<string>
#include"PriorityQueue.h"
class Benchmark{
private:
	struct row {
		int m;
		int count;
		int ins_steps;
		int del_steps;
		double ins_t;//insertion time
		double del_t;//deletion time
		row(int m, int count, int ins_steps, int del_steps,  double ins_t, double del_t) {
			this->m = m;
			this->count = count;
			this->ins_steps = ins_steps;
			this->del_steps = del_steps;
			this->ins_t = ins_t;
			this->del_t = del_t;
		}
	};
	static int a;
	static int b;
	static std::vector<int> m_arr;
	static std::vector<int> count_arr;
	static std::vector<row> result;
public:
	Benchmark() = delete;
	static void Run();
	static void Print();
};

