#include "Heap.h"

void Heap::init(int m)
{
	this->capacity = INITIAL_CAP_MULTIPLIER * m;
	this->m = m;
	this->items = new int[capacity];
}

void Heap::destroy(){
	delete[]items;
	size = 0;
	capacity = m;
	items = nullptr;
}

int Heap::min_child_idx(int father_idx, int& steps)
{
	int min_idx = get_child_idx(father_idx, 1);
	int min_child = this->items[min_idx];
	int child_nr = 2;
	while(has_child(father_idx, child_nr)){
		int child = get_child(father_idx, child_nr);
		if (child < min_child) {
			min_child = child;
			min_idx = get_child_idx(father_idx, child_nr);
		}
		child_nr++;
		steps++;
	}
	return min_idx;
}

int Heap::get_child(int father_idx, int child_nr){
	if (!has_child(father_idx, child_nr)) throw "Illegal index";
	return items[get_child_idx(father_idx, child_nr)];
}

int Heap::get_parent(int child_idx){
	if (!has_parent(child_idx)) throw "No father for node with index " + child_idx;
	return items[get_parent_idx(child_idx)];
}

void Heap::resize_if_needed(){
	if (size > capacity) throw "Illegal size";
	if (size == capacity) this->capacity = this->capacity * m;
	else if (size < capacity / m) this->capacity = std::max(this->capacity / m, m);
	int* old = this->items;
	this->items = new int[this->capacity];
	std::copy(old, old + this->size, this->items); //copy old aray into the new aray
	delete[] old;
}

void Heap::heapify_down(int& steps){
	int curr_idx = 0;
	while (has_child(curr_idx, 1)) {
		int min_idx = min_child_idx(curr_idx, steps);
		int min = this->items[min_idx];
		if (min > items[curr_idx]) break; //end the propagation 
		std::swap(items[curr_idx], items[min_idx]);
		curr_idx = min_idx;
	}
}

void Heap::heapify_up(int& steps){
	int curr_idx = this->size - 1;
	while (has_parent(curr_idx) && get_parent(curr_idx) > items[curr_idx]) {
		std::swap(items[get_parent_idx(curr_idx)], items[curr_idx]);
		curr_idx = get_parent_idx(curr_idx);
		steps += 2; //1 comparison and 1 swap
	}
}

Heap::Heap(int m){
	init(m);
}

Heap::~Heap(){
	destroy();
}

void Heap::add(int item, int& steps){
	steps = 0;
	resize_if_needed();
	this->items[this->size] = item;
	this->size++;
	heapify_up(steps);
}

int Heap::peek() const{
	if (size == 0) throw "Heap empty";
	return items[0];
}

int Heap::remove(int& steps){
	steps = 0;
	int item = this->items[0];
	this->items[0] = this->items[this->size - 1];
	this->size--;
	heapify_down(steps);
	resize_if_needed();
	return item;
}

void Heap::convert(int new_m){
	int* tmp_items = new int[this->size];
	int steps=0;
	int old_sz = this->size;
	std::copy(this->items, this->items + this->size, tmp_items);
	destroy();
	init(new_m);
	for (int i = 0; i < old_sz; i++) this->add(tmp_items[i], steps);
	delete[] tmp_items;
}

void Heap::merge(Heap& h, int& steps){
	steps = 0;
	for (int i = 0; i < h.size; i++) {
		int i_steps = 0;
		this->add(h.items[i], i_steps);
		steps += i_steps;
	}

}

std::ostream& operator<<(std::ostream& os, Heap& h){
	/*for (int i = 0; i < h.size; i++) {
		if (i) os << ", ";
		os << h.items[i];
	}
	os << std::endl;*/
	if (h.size == 0) {
		os << "==EMPTY==";
		return os;
	};
	int line_len = h.m*40;
	int first_skip = line_len, in_between_skip;
	int height = ceil(log(h.size+1) / log(h.m));
	int prev_idx = 0;
	for (int i = 0; i < height+1; i++) {
		in_between_skip = first_skip;
		first_skip = (in_between_skip - h.m) / h.m;
		for (int j = 0; j < first_skip; j++) os<<' ';
		int next_idx = prev_idx + pow(h.m, i);
		for (int j = prev_idx; j < next_idx && j < h.size; j++) {
			os << std::setw(2) << std::setfill('0') << h.items[j];
			int offset = (h.m % 2 == 1 ? first_skip + 2 : 0);
			for (int k = 0; k < in_between_skip-offset; k++) os << ' ';
		}
		os << "\n\n";
		prev_idx = next_idx;
	}
	os << std::endl;
	return os;
}
