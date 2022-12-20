#include "Benchmark.h"
int Benchmark::a = 0;
int Benchmark::b = INT_MAX;
std::vector<int> Benchmark::m_arr = { 2,4,8 };
std::vector<int> Benchmark::count_arr = { 100,1000,10000,100000 };
std::vector<Benchmark::row> Benchmark::result;
void Benchmark::Run() {
	using namespace std::chrono;
	for (int count : count_arr) {
		for (int m : m_arr) {
			int ins_steps, del_steps = 0, del;
			PriorityQueue pq(m);
			auto start = high_resolution_clock::now();
			pq.load_random(count, a, b, ins_steps);
			//std::string fname = "test_" + std::to_string(count) + ".txt";
			//pq.load_from_file(fname, ins_steps);
			auto end = high_resolution_clock::now();
			duration<double, std::milli> ins_t = end - start;
			start = high_resolution_clock::now();
			while (!pq.empty()) {
				pq.remove(del);
				del_steps += del;
			}
			end = high_resolution_clock::now();
			duration<double, std::milli> del_t = end - start;
			result.push_back({ m, count, ins_steps,del_steps, ins_t.count(), del_t.count() });
		}
	}
}

void Benchmark::Print() {
	using namespace std;
	cout << left << setw(12) << "Item count" << setw(3) << "M" <<
		setw(12) << "Ins. time" << setw(13) << "Ins. steps" << setw(12) << "Del. time" << setw(13) << "Del. steps" << std::endl;
	cout << left << setw(13) << "---------" << setw(3) << "-" <<
		setw(12) << "---------" << setw(13) << "----------" << setw(12) << "---------" << setw(13) << "----------" << std::endl;
	for (row r : result) {

		cout << fixed<<setprecision(2) << setw(13) << r.count << setw(3) << r.m <<
			setw(12) << r.ins_t << setw(13) << r.ins_steps
			<< setw(12) << r.del_t << setw(13) << r.del_steps << std::endl;
	}
}