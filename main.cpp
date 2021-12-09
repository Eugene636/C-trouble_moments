#include <iostream>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include <mutex>
#include <list>
#include <cstdlib>
#include <ctime>
///////////////////////////////////////////////////////*Task1*/
std::mutex mu_out;
std::mutex mu_cons;

template <typename T, template <typename> class C>
void print (C <T>& out) {
	mu_out.lock();
	for (auto n : out) std::cout << n <<' ';
	std::cout << std::endl;
	mu_out.unlock();
}

template <typename T>
void print (T& out) {
	mu_out.lock();
	std::cout << out << std::endl;
	mu_out.unlock();
}

void print (std::string& S) {
	mu_out.lock();
	std::cout << S << std::endl;
	mu_out.unlock();
}

template <typename T>
struct Massive {
	T* m_Massive;
	size_t m_size;
	Massive (T* M, size_t size) : m_Massive {M}, m_size {size} {}
	T* begin () {return m_Massive;}
	T* end () {return m_Massive + m_size;} 
};

void Task1_test () {
	std::vector <int> V = {0, 1, 2, 3, 4};
	int M[5] = {1, 2, 3, 4, 5};
	Massive<int> massive (M, 5);
	std::string S = "Hellow, threads";
	void (*p1)(std::vector<int>&) = print;  
	std::thread th1 (p1, std::ref(V));
	void (*p2) (Massive<int>&) = print;
	std::thread th2 (p2, std::ref(massive));
	void(*p3)(std::string&) = print;
	std::thread th3(p3, std::ref(S));
	th1.join();
	th2.join();
	th3.join();
}

/////////////////////Task2
/*Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863). Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления. */
class Simple { // класс с целью создать возможность обмена информацией между двумя void функциями
	uint32_t m_number_simple;// заданное по счету простое число
	uint64_t m_simple_value;// величина заданного по счету простого числа
	uint32_t m_taken_simple_value;// найденных на данный момент простых чисел
public:
	Simple (uint32_t input) : m_number_simple {input}, m_simple_value {0}, m_taken_simple_value {0} {}
	void set_value () {
		uint64_t simple_value = 2;
		uint64_t  value = 2;
		uint32_t count = 0;
		for (count = 0; count < m_number_simple; simple_value++) {
			for (value = 2; value <= simple_value; value++) if (!(simple_value %value)) break;
		if (value == simple_value) {
			count++;
			m_simple_value = simple_value;	
			m_taken_simple_value = count;
		}
		}
	}
	void print_value () {
		using namespace std::chrono_literals;
		int percent = 0;
		do {	
			percent = 100*(static_cast<float>(m_taken_simple_value)/m_number_simple);
			std::cout <<percent <<' ' << m_number_simple <<' ' <<' ' <<m_taken_simple_value << std::endl;
			std::this_thread::sleep_for(1.5s);
		} while (percent != 100);
		std::cout << m_simple_value << std::endl;
	}
	
};
void Task2 () {
	uint32_t input;
	std::cin >> input;
	Simple simple(input);
	std::thread calculation(&Simple::set_value, &simple);
	std::thread print (&Simple::print_value, &simple);
	calculation.join();
	print.join();
	
}
/*Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор. Хозяин приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду). При этом у каждой вещи есть своя ценность. Вор забирает вещи (функция, которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 секунд), каждый раз забирает вещь с наибольшей ценностью.*/
void Master (std::vector<int>& things) {
	while (!things.empty()) {
	std::srand(std::time(nullptr));
	int i = std::rand()%20000;
	mu_out.lock();
	things.push_back(i);
	mu_out.unlock();
	std::this_thread::sleep_for (std::chrono::seconds(1));
	}
}
void thief (std::vector<int>& things) {
	using namespace std::chrono_literals;
	while (!things.empty()) {
		mu_out.lock();
		int value = *things.begin();
		size_t count = 0;
		for (size_t i = 0; i < things.size(); i++) {
			if (value < things[i]) {
			value = things[i];
			count = i;
			}
		}
		mu_out.unlock();
		things.erase(things.begin() + count);
		std::this_thread::sleep_for (500ms);
	}
}

void printVector (std::vector<int>& things) {
	using namespace std::chrono_literals;
	while (!things.empty()) {
	mu_out.lock();
	for (auto n : things) {std::cout << n << ' ';}
	mu_out.unlock();
	std::cout <<std::endl;
	std::this_thread::sleep_for (1.75s);
	}
}
void Task3 () {
	std::vector <int> things;
	std::srand(std::time(nullptr));
	for (int i = 0; i < 100; i++) {
		int value = rand()%20000;
		things.push_back(value);
	}
	std::thread M (Master, std::ref(things));
	std::thread T (thief, std::ref(things));
	std::thread P (printVector, std::ref(things));
	M.join();
	T.join();
	P.join();
}

int main () { 
	Task1_test();
	Task2 ();
	Task3 ();
	return 0;
}
 
 
 
 


