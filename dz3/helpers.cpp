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
			std::cout << "\t1) Stvaranje novog praznog hipa reda m\n\
	2) Dodavanje elementa u hip\n\
	3) Dohvatanje minimalnog elementa\n\
	4) Brisanje minimalnog elementa\n\
	5) Pretvaranje hipa u hip zadatkog novog reda\n\
	6) Dodavanje jednog hipa drugom\n\
	7) Ispis hipa\n\
	8) Brisanje hipa\n\
	0) Glavni meni\n";
			std::cout << "-----------------------------------------------------------------------\n";
			break;
	case 2:
		std::cout <<
"+---------------------------------------------------------------------+\n\
|                           Priority Queue                            |\n\
+---------------------------------------------------------------------+\n";
		std::cout << "\t1) Stvaranje novog praznog reda\n\
	2) Ispitivanje da li je red prazan\n\
	3) Dohvatanje prvog elementa\n\
	4) Brisanje prvog elementa\n\
	5) Dodavanje elementa\n\
	6) Ucitavanje iz fajla\n\
	7) Ucitavanje pomocu nasumicnih brojeva\n\
	8) Merenje performansi\n\
	0) Glavni meni\n";
	}
	
	std::cout << "\033[1;33mUnos: \033[0m";
	std::cin >> selectedOption;
	return selectedOption;

}

void helpers::mainLoop()
{
	int option=-1;
	while (option!=0) {
		std::cout <<
"+---------------------------------------------------------------------+\n\
|                               Glavni meni                           |\n\
+---------------------------------------------------------------------+\n\
	1) Heap\n\
	2) Priority Queue\n\
	0) Izlaz\n";
		std::cout << "\033[1;33mUnos: \033[0m";
		std::cin >> option;
		switch (option) {
		case 1: heapLoop(); break;
		case 2: queueLoop(); break;
		case 0: return;
		default:
			std::cout << "Greska, nepostojeca opcija.\n";
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
			std::cout << "\tRed hipa: ";
			std::cin >> m;
			h = new Heap(m);
			break;
		}
		case 2: {
			if (!nullCheckAndError(h)) continue;
			int x, steps=0;
			std::cout << "\tElement koji se dodaje: ";
			std::cin >> x;
			h->add(x, steps);
			std::cout << "\tZa dodavanje je bilo potrebno " << steps << " koraka.\n";
			break;
		}
		case 3: {
			try {
				if (!nullCheckAndError(h)) continue;
				std::cout << "\t Minimalni element je: " << h->peek() << ".\n";
			}
			catch (std::string ex){
				std::cout << "\tGreska: " << ex << std::endl;
			}
			break;
		}
		case 4: {
			if (!nullCheckAndError(h)) continue;
			try {
				int steps = 0;
				std::cout << "\tMinimalni element je: " << h->remove(steps) << "; Za brisanje je bilo potrebno: " << steps << " koraka.\n";
			}
			catch (std::string ex) {
				std::cout << "\tGreska: " << ex<<std::endl;
			}
			break;
		}
		case 5: {
			if (!nullCheckAndError(h)) continue;
			int m;
			std::cout << "\tNovi red hipa: ";
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
			std::cout << "\tDodavanje hipa h2: \n" << h2 << "hipu h: \n" << *h;
			h->merge(h2, steps);
			std::cout << "\tRezultujuci hip: \n" << *h;
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
		default:
			std::cout << "\033[1;31 Neispravan unos, pokusajte opet ili unesite 0 za kraj\033[0m\n";
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
			std::cout << "\tRed " << (pq.empty() ? "je " : "nije ") << "prazan\n";
			break;
		}
		case 3: {
			try {
				std::cout << "\t Minimalni element je: " << pq.peek() << ".\n";
			}
			catch (std::string ex) {
				std::cout << "\tGreska: " << ex << std::endl;
			}
			break;
		}
		case 4: {
			try {
				int steps = 0;
				std::cout << "\tMinimalni element je: " << pq.poll(steps) << "; Za brisanje je bilo potrebno: " << steps << " koraka.\n";
			}
			catch (std::string ex) {
				std::cout << "\tGreska: " << ex << std::endl;
			}
			break;
		}
		case 5: {
			int x, steps = 0;
			std::cout << "\tElement koji se dodaje: ";
			std::cin >> x;
			pq.add(x, steps);
			std::cout << "\tZa dodavanje je bilo potrebno " << steps << " koraka.\n";
			break;
		}
		case 6: {
			std::string filename;
			int steps;
			bool flag = true;
			while (flag) {
				std::ifstream in;
				std::cout << "\tIme (putanja) fajla: ";
				std::cin >> filename;
				in.open(filename);
				if (!in) std::cout << "\033[1;31m\tGreska, fajl ne postoji\033[0m" << std::endl;
				else flag = false;
				in.close();
			}
			pq.load_from_file(filename, steps);
			std::cout << "\tZa ucitavanje iz fajla je bilo potrebno " << steps << " koraka.\n";
			break;
		}
		case 7: {
			int count, a, b, steps;
			std::cout << "\tBroj nasumicnih vrednosti: ";
			std::cin >> count;
			std::cout << "\tDonja granica vrednosti: ";
			std::cin >> a;
			std::cout << "\tGornja granica vrednosti: ";
			std::cin >> b;
			pq.load_random(count, a, b, steps);
			std::cout << "\tZa ucitavanje je bilo potrebno " << steps << " koraka.\n";
			break;
		}
		case 8: {
			Benchmark::Run();
			Benchmark::Print();
			break;
		}
		default:
			std::cout << "\033[1;31 Neispravan unos, pokusajte opet ili unesite 0 za kraj\033[0m\n";
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

