#include "Heap.h"

void Heap::init(int m)
{
	this->capacity = INITIAL_CAP;
	this->m = m;
	this->items = new int[capacity];
}

void Heap::destroy() {
	delete[]items;
	size = 0;
	capacity = INITIAL_CAP;
	items = nullptr;
}
//slower but more readable
//int Heap::min_child_idx(int father_idx, int& steps)
//{
//	int min_idx = get_child_idx(father_idx, 1);
//	int min_child = this->items[min_idx];
//	int child_nr = 2;
//	while (has_child(father_idx, child_nr)) {
//		int child = get_child(father_idx, child_nr);
//		if (child < min_child) {
//			min_child = child;
//			min_idx = get_child_idx(father_idx, child_nr);
//		}
//		child_nr++;
//		steps++;
//	}
//	return min_idx;
//}

int Heap::min_child_idx(int father_idx, int& steps)
{
	int min_idx = get_child_idx(father_idx, 1);
	int min_child = this->items[min_idx];
	int child_nr = 2;
	int idx = father_idx * m + 2;
	while (idx < size && child_nr <= m) {
		if (items[idx] < min_child) {
			min_child = items[idx];
			min_idx = idx;
		}
		child_nr++;
		idx++;
		steps++;
	}
	return min_idx;
}


int Heap::get_child(int father_idx, int child_nr) {
	if (!has_child(father_idx, child_nr)) throw std::string("Illegal index");
	return items[get_child_idx(father_idx, child_nr)];
}

int Heap::get_parent(int child_idx) {
	if (!has_parent(child_idx)) throw std::string("No father for node with index " + child_idx);
	return items[get_parent_idx(child_idx)];
}

void Heap::resize_if_needed() {
	if (size > capacity) throw std::string("Illegal size");
	if (size == capacity) {
		this->capacity = this->capacity * SCALE_FACTOR;

		//else if (size < capacity / m) this->capacity = std::max(this->capacity / m, m);
		int* old = this->items;
		this->items = new int[this->capacity];
		std::copy(old, old + this->size, this->items); //copy old aray into the new aray
		//for (int i = 0; i < this->size; i++) this->items[i] = old[i];
		delete[] old;
	}
}
//slower but more readable
//void Heap::heapify_down(int& steps, int start_idx = 0) {
//	steps++;
//	int curr_idx = start_idx;
//	while (has_child(curr_idx, 1)) {
//		int min_idx = min_child_idx(curr_idx, steps);
//		int min = this->items[min_idx];
//		if (min > items[curr_idx]) break; //end the propagation 
//		std::swap(items[curr_idx], items[min_idx]);
//		curr_idx = min_idx;
//		steps += 1; // 1 swap, steps incremented additionally in min_child_idx
//	}
//}
void Heap::heapify_down(int& steps, int start_idx = 0) {
	steps++;
	int curr_idx = start_idx;
	while (curr_idx * m + 1 < size) {
		int min_idx = min_child_idx(curr_idx, steps);
		int min = this->items[min_idx];
		if (min > items[curr_idx]) break; //end the propagation 
		std::swap(items[curr_idx], items[min_idx]);
		curr_idx = min_idx;
		steps += 1; // 1 swap, steps incremented additionally in min_child_idx
	}
}
//slower but more readable
//void Heap::heapify_up(int& steps) {
//	steps++;
//	int curr_idx = this->size - 1;
//	while (has_parent(curr_idx) && get_parent(curr_idx) > items[curr_idx]) {
//		std::swap(items[get_parent_idx(curr_idx)], items[curr_idx]);
//		curr_idx = get_parent_idx(curr_idx);
//		steps += 2; //1 comparison and 1 swap
//	}
//}
void Heap::heapify_up(int& steps) {
	steps++;
	int curr_idx = this->size - 1;
	int parent_idx = (curr_idx - 1) / m;
	while (curr_idx >= 0 && items[parent_idx] > items[curr_idx]) {
		std::swap(items[parent_idx], items[curr_idx]);
		curr_idx = parent_idx;
		parent_idx = (curr_idx - 1) / m;
		steps += 2; //1 comparison and 1 swap
	}
}

Heap::Heap(int m) {
	init(m);
}

Heap::~Heap() {
	destroy();
}

void Heap::add(int item, int& steps) {
	steps = 0;
	resize_if_needed();
	this->items[this->size] = item;
	this->size++;
	heapify_up(steps);
}

int Heap::peek() const {
	if (size == 0) throw std::string("Heap empty");
	return items[0];
}

int Heap::remove(int& steps) {
	if (size == 0) throw std::string("Heap empty");
	steps = 0;
	int item = this->items[0];
	this->items[0] = this->items[this->size - 1];
	this->size--;
	heapify_down(steps);
	resize_if_needed();
	return item;
}

void Heap::remove(int key, int& steps) {
	steps = 0;
	int index = -1;
	for (int i = 0; i < this->size; i++) {
		if (this->items[i] == key) {
			index = i;
			break;
		}
	}
	if (index == -1) throw std::string("Nonexistent key");
	this->items[index] = this->items[this->size - 1];
	this->size--;
	heapify_down(steps, index);
	resize_if_needed();

}

void Heap::convert(int new_m) {
	int* tmp_items = new int[this->size];
	int steps = 0;
	int old_sz = this->size;
	std::copy(this->items, this->items + this->size, tmp_items);
	destroy();
	init(new_m);
	for (int i = 0; i < old_sz; i++) this->add(tmp_items[i], steps);
	delete[] tmp_items;
}

void Heap::merge(Heap& h, int& steps) {
	steps = 0;
	for (int i = 0; i < h.size; i++) {
		int i_steps = 0;
		this->add(h.items[i], i_steps);
		steps += i_steps;
	}
}

std::ostream& operator<<(std::ostream& os, Heap& h) {
	/*for (int i = 0; i < h.size; i++) {
		if (i) os << ", ";
		os << h.items[i];
	}
	os << std::endl;*/
	if (h.size == 0) {
		os << "==EMPTY==\n";
		return os;
	};
	int line_len = h.m * 40;
	int first_skip = line_len, in_between_skip;
	int height = ceil(log(h.size + 1) / log(h.m));
	int prev_idx = 0;
	for (int i = 0; i < height + 1; i++) {
		in_between_skip = first_skip;
		first_skip = (in_between_skip - h.m) / h.m;
		for (int j = 0; j < first_skip; j++) os << ' ';
		int next_idx = prev_idx + pow(h.m, i);
		for (int j = prev_idx; j < next_idx && j < h.size; j++) {
			os << std::setw(2) << std::setfill('0') << h.items[j];
			int offset = (h.m > 2 ? first_skip + 2 : 0);
			for (int k = 0; k < in_between_skip - offset; k++) os << ' ';
		}
		os << "\n\n";
		prev_idx = next_idx;
	}
	os << std::endl;
	return os;
}
