#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Timer.h"
/*Task 1*/
template <typename S> 
void swap_value (S*p1, S*p2) {
	S temp = *p2;
	*p2 = *p1;
	*p1 = temp;
}
/*Task 2*/
template <typename S>
void sort_value (std::vector <S*> Val_pointers) {//тип должен подразумевать операцию разыменования
	for (int i = 0; i < Val_pointers.size() - 1; i++)
		for (int i = 0; i < Val_pointers.size() - 1; i++){
			if (*Val_pointers[i] > *Val_pointers[i + 1]) swap_value (Val_pointers[i], Val_pointers[i + 1]);
		}
}


/*Подсчитайте количество гласных букв в книге “Война и мир”. Для подсчета используйте 4 способа:
○      count_if и find
○      count_if и цикл for
○      цикл for и find
○      2 цикла for
Замерьте время каждого способа подсчета и сделайте выводы.
*/
int e_letter (std::string s) {
	size_t n;
	int count = 0;
	n = s.find ('e');
	if (n == std::string::npos) return count;
	else {
		s = s.substr (n + 1);
		count++;
		count += e_letter(s);
		return count;
	}
}

void Task1_test () {
	int a = 10;
	int b = 20;
	int* p1 = &a;
	int* p2 = &b;
	std::cout << "a = "<< a << "b = " << b << "&a = "<< &a << "&b = " << &b << " p1 = "<<p1<<" p2 = " <<p2<<std::endl;
	swap_value (p1 , p2); 
	std::cout << "a = "<< a << "b = " << b << "&a = "<< &a << "&b = " << &b << " p1 = "<<p1<<" p2 = " <<p2<<std::endl;
	int** p3 = &p1;
	int** p4 = &p2;
	swap_value (p3, p4);
	std::cout << "a = "<< a << "b = " << b << "&a = "<< &a << "&b = " << &b << " p1 = "<<p1<<" p2 = " <<p2<<std::endl;
}
void Task2_test () {
	int mass[50];
	std::vector <int*> Val_pointers;
	for (int i = 0; i < 50; i++)
		mass[i] = std::rand();
	for (int i = 0; i < 50; i++)
		std::cout << mass[i] << ' ';
	for (int i = 0; i < 50; i++)
		Val_pointers.push_back(mass + i);
	sort_value (Val_pointers);
	std::cout << std::endl;
	for (int i = 0; i < 50; i++)
		std::cout << (*Val_pointers[i]/(double)(*Val_pointers[49])) << ' ';
}
void Task3 () {
	std::ifstream fin ("War_and_pease.txt");
	std::string temp_s, new_s;
	for (;!fin.eof();){
		getline (fin, temp_s);
		new_s += temp_s;
	}
	fin.close();
	const std::string Vowels = "aAeEiIoOuUyY";
	size_t count = 0;
	Timer timer ("2 for cycle");
	for (int i = 0; i < 12; i++)
		for (auto n: new_s) {
			if (n == Vowels[i]) count++;
		}
	std::cout << count <<std::endl;
	timer.print();
	count = 0;
	timer.start ("for and if");
	for (auto n: new_s) {
		if ((n == Vowels[0])||(n == Vowels[1])||(n == Vowels[2])||(n == Vowels[3])||(n == Vowels[4])||(n == Vowels[5])||
		(n == Vowels[6])||(n == Vowels[7])||(n == Vowels[8])||(n == Vowels[9])||(n == Vowels[10])||(n == Vowels[11])) count++;
	}
	std::cout << count <<std::endl;
	timer.print ();
	count = 0; 
	timer.start ("for and find");
	for (auto n : new_s) if (Vowels.find(n) != std::string::npos) count++;
	std::cout << count <<std::endl;
	timer.print ();
	count = 0;
	timer.start ("for and count_if");
	count = std::count_if (new_s.begin(), new_s.end(), [Vowels](char c) -> bool {
		for (auto v : Vowels) if (v == c) return true; 
		return false;
	});
	std::cout << count <<std::endl;
	timer.print ();
	count = 0; 
	timer.start("count_if and _find");
	count = std::count_if (new_s.begin(), new_s.end(), [Vowels](char c) -> bool {
		if (Vowels.find(c) != std::string::npos) return true;
		return false;
	});
	std::cout << count <<std::endl;
	timer.print ();
}

int main () {
	Task1_test ();
	Task2_test ();
	std::cout <<std::endl;
	Task3 ();
	return 0;
}
