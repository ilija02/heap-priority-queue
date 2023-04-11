#include "helpers.h"


int helpers::getSelectedMenuOption(int menu_nr)
{

	int selectedOption;
	switch (menu_nr) {
	case 1:
			std::cout <<
"+---------------------------------------------------------------------+\n\
|                                 Heap                                |\n\
+---------------------------------------------------------------------+\n";
			std::cout << "\t1) New heap of order m\n\
	2) Add new element\n\
	3) Get min element\n\
	4) Delete min element\n\
	5) Change heap order\n\
	6) Add one heap to another heap\n\
	7) Print heap\n\
	8) Delete heap\n\
	9) Delete arbitrary key\n\
	0) Main menu\n";
			std::cout << "-----------------------------------------------------------------------\n";
			break;
	case 2:
		std::cout <<
"+---------------------------------------------------------------------+\n\
|                           Priority Queue                            |\n\
+---------------------------------------------------------------------+\n";
		std::cout << "\t1) New empty queue\n\
	2) Test if queue is empty\n\
	3) Get first element\n\
	4) Delete first element\n\
	5) Add new element\n\
	6) Load from file\n\
	7) Load using random numbers\n\
	8) Benchmark\n\
	0) Main menu\n";
	}
	
	std::cout << "\033[1;33mInput: \033[0m";
	std::cin >> selectedOption;
	return selectedOption;

}

void helpers::mainLoop()
{
	int option=-1;
	while (option!=0) {
		std::cout <<
"+---------------------------------------------------------------------+\n\
|                               Main menu                             |\n\
+---------------------------------------------------------------------+\n\
	1) Heap\n\
	2) Priority Queue\n\
	0) Exit\n";
		std::cout << "\033[1;33mUnos: \033[0m";
		std::cin >> option;
		switch (option) {
		case 1: heapLoop(); break;
		case 2: queueLoop(); break;
		case 0: return;
		default:
			std::cout << "Error, invalid option.\n";
		}
	}
}

void helpers::heapLoop() {
	int selectedOption;
	Heap* h = nullptr;
	while (selectedOption = getSelectedMenuOption(1)) {
		switch (selectedOption) {
		case 0: {
			delete h;
			return;
		}
		case 1: {
			int m;
			if (h) delete h;
			std::cout << "\tHeap order: ";
			std::cin >> m;
			h = new Heap(m);
			break;
		}
		case 2: {
			if (!nullCheckAndError(h)) continue;
			int x, steps=0;
			std::cout << "\tElement to add: ";
			std::cin >> x;
			h->add(x, steps);
			std::cout << "\tAdding took " << steps << " steps.\n";
			break;
		}
		case 3: {
			try {
				if (!nullCheckAndError(h)) continue;
				std::cout << "\t Minimal element is: " << h->peek() << ".\n";
			}
			catch (std::string ex){
				std::cout << "\Error: " << ex << std::endl;
			}
			break;
		}
		case 4: {
			if (!nullCheckAndError(h)) continue;
			try {
				int steps = 0;
				std::cout << "\tMinimal element is: " << h->remove(steps) << "; Deletion took: " << steps << " steps.\n";
			}
			catch (std::string ex) {
				std::cout << "\tError: " << ex<<std::endl;
			}
			break;
		}
		case 5: {
			if (!nullCheckAndError(h)) continue;
			int m;
			std::cout << "\tNew heap order: ";
			std::cin >> m;
			h->convert(m);
			break;
		}
		case 6: {
			if (!nullCheckAndError(h)) continue;
			int steps;
			Heap h2(2);
			h2.add(9, steps);
			h2.add(19, steps);
			h2.add(23, steps);
			h2.add(2, steps);
			std::cout << "Adding heap h2: \n" << h2 << "to heap h: \n" << *h;
			h->merge(h2, steps);
			std::cout << "Resulting heap: \n" << *h;
			break;
		}
		case 7: {
			if (!nullCheckAndError(h)) continue;
			std::cout << *h;
			break;
		}
		case 8: {
			delete h;
			h = nullptr;
			break;
		}
		case 9: {
			if (!nullCheckAndError(h)) continue;
			int x, steps;
			std::cout << "\tValue to delete: ";
			std::cin >> x;
			try {
				h->remove(x, steps);
				std::cout<<"\tDeletion took: " << steps << " steps.\n";
			}
			catch (std::string e) {
				std::cout << e<<std::endl;
			}
			break;
		}
		default:
			std::cout << "Invalid input, try again or enter 0 to exit.\n";
			break;
		}
	}
}

void helpers::queueLoop(){
	int selectedOption;
	PriorityQueue pq;
	while (selectedOption = getSelectedMenuOption(2)) {
		switch (selectedOption) {
		case 1: break;
		case 2: {
			std::cout << "\tQueue" << (pq.empty() ? "is " : "isn't ") << "empty\n";
			break;
		}
		case 3: {
			try {
				std::cout << "\t Minimal element is: " << pq.peek() << ".\n";
			}
			catch (std::string ex) {
				std::cout << "\t: " << ex << std::endl;
			}
			break;
		}
		case 4: {
			try {
				int steps = 0;
				std::cout << "\Minimal element is: " << pq.poll(steps) << "; Deletion took: " << steps << " koraka.\n";
			}
			catch (std::string ex) {
				std::cout << "\tError: " << ex << std::endl;
			}
			break;
		}
		case 5: {
			int x, steps = 0;
			std::cout << "\tElement to add: ";
			std::cin >> x;
			pq.add(x, steps);
			std::cout << "\tAdding took " << steps << " steps.\n";
			break;
		}
		case 6: {
			std::string filename;
			int steps;
			bool flag = true;
			while (flag) {
				std::ifstream in;
				std::cout << "\tFilename (filepath): ";
				std::cin >> filename;
				in.open(filename);
				if (!in) std::cout << "\033[1;31m\tError, no such file\033[0m" << std::endl;
				else flag = false;
				in.close();
			}
			pq.load_from_file(filename, steps);
			std::cout << "\tLoading from file took " << steps << " steps.\n";
			break;
		}
		case 7: {
			int count, a, b, steps;
			std::cout << "\tNumber of random values: ";
			std::cin >> count;
			std::cout << "\tLower bound: ";
			std::cin >> a;
			std::cout << "\tUpper bound: ";
			std::cin >> b;
			pq.load_random(count, a, b, steps);
			std::cout << "\tLoading random values took " << steps << " steps.\n";
			break;
		}
		case 8: {
			Benchmark::Run();
			Benchmark::Print();
			break;
		}
		default:
			std::cout << "\033[1;31 Invalid input, try again or enter 0 to exit\033[0m\n";
			break;
		}
	}
}


bool helpers::nullCheckAndError(Heap* h)
{
	if (h == nullptr) {
		std::cout << "\033[1;31mGreska, morate prvo inicijalizovati heap\033[0m" << std::endl;
		return false;
	}
	return true;
}

