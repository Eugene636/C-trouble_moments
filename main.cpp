#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <set>
#include <list>
#include <deque>
#include <map>

/*Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, и выводящую в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз). Продемонстрировать работу функции, передав итераторы различных типов.*/
template <typename It>
void print_unique (It bn, It end) {
	std::set <std::string> Set ;
	while (bn != end) {
		Set.insert(*bn);
		bn++;
	}
	copy (Set.begin(), Set.end(), std::ostream_iterator<std::string> (std::cout, " "));
}

void Task1_test () {
	std::vector <std::string> STR;
	while (!std::cin.eof()) {
		std::string s;
		std::cin >> s;
		STR.push_back (s);
	}
	std::cout << std::endl;
	std::vector <std::string> ::iterator it1, it2;
	it1 = STR.begin();
	it2 = STR.end();
	print_unique (it1, it2);
	std::list<std::string> :: iterator it3, it4;
	std::list <std::string> STR_List;
	std::copy (STR.begin(), STR.end(), back_inserter(STR_List));
	it3 = STR_List.begin();
	it4 = STR_List.end();
	print_unique (it3, it4);
	std::deque <std::string> ::iterator it5, it6;
	std::deque <std::string> STR_DEQUE; 
	std::copy (STR.begin(), STR.end(), back_inserter(STR_DEQUE));
	it5 = STR_DEQUE.begin ();
	it6 = STR_DEQUE.end ();
	print_unique (it5, it6);
	std::string M[STR.size()];
	for (int i = 0; i < STR.size(); i++) M[i] = STR[i];
	print_unique(M, (M + STR.size()));
}

void Task2 () {
	std::multimap<int, std::string> Sentences;
	std::string inp_str;
	std::string sentence;
	int count = 0;
	bool end_string_flag = false;
	while (std::cin) {
		std::getline(std::cin, inp_str);
		sentence.clear();
		count = 0;
		for (auto c : inp_str) {
			if (c == ' ') count++;
			if ((c != '.')||(c != '!')||(c != '?')) sentence += c;
			else {
				count++;
				Sentences.insert({count, sentence}); 
				sentence.clear();
				count = 0;
			}
		}
		if (!sentence.empty()){
		count++;
		Sentences.insert({count, sentence}); 
		}
	}
	for (auto S: Sentences) {
		std::cout << S.second<< std::endl;
}
}




int main () {
//	Task1_test ();
	Task2 ();


	
	return 0;
}

