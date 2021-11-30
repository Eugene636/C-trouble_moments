#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <climits>
#include <ctime>
#include <deque>
#include <list>
///////////////////////////////////////////////////////////////////Task1
/*Имеется отсортированный массив целых чисел. Необходимо разработать функцию insert_sorted, которая принимает вектор и новое число и вставляет новое число в определенную позицию в векторе, чтобы упорядоченность контейнера сохранялась. Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым контейнером, содержащим любой тип значения. */
template <typename T, template<typename> class   C>
void insert_sorted (C <T>& Vector1, const T & insert_value) {
	if (*Vector1.begin() <= *(Vector1.end() - 1)) {
		auto it = std::lower_bound(Vector1.begin(), Vector1.end(), insert_value);
		Vector1.insert (it, insert_value);
	}
	else {
		auto it = std::lower_bound(Vector1.rbegin(), Vector1.rend(), insert_value);
		size_t difference = static_cast <size_t> (it - Vector1.rbegin());
		Vector1.insert(Vector1.end() - difference, insert_value);
	//	std::cout << *it <<std::endl;
	}
}

/*template <typename T>
void insert_sorted (C <T>& Vector1, const T & insert_value) {
	auto it = std::lower_bound(Vector1.begin(), Vector1.end(), insert_value);
	Vector1.insert (it, insert_value);
}*/





/////////////////////////////////////////////////////Task2


/*я сделал это задание интересней. Посчитаю, каково среднеквадратичное отклонение при разворачивании сигнала на 1/10 возможного диапазона (вполне реалистичная ситуация) и оцифровании в 8, 16, и 24 бит. Возможный диапазон сигнала +/- 1,6 В*/
/*функция dig_signal распечатывает среднюю величину погрешности оцифровывания при передаче в нее соответствующего значения 
number_of_bits*/
double dig_signal (unsigned int number_of_bits, unsigned int N) {
	unsigned int bit_capacity = (1 << number_of_bits) - 1;
	std::srand(std::time(nullptr));
	std::vector <double> true_values (N);
	for_each (true_values.begin(), true_values.end(), [](double &value){
	value = (rand()%3200000 - 1600000)/10000000.0;//сигнал амплитудой 0.32 В со смещением 0,16 В. большие числа int для 6 знаков после
							//запятой
	});
	
	std::vector <int> digitized (N);
	int i = 0;
	for_each (digitized.begin(), digitized.end(), [true_values, &i, bit_capacity](int &dig) {
	dig = static_cast<int>((true_values[i]/3.2)*bit_capacity);//оцифрованный сигнал. нулевому значению соотвествует 0, минимальному
								//значению -255/2, максимальному значению 255/2
	i++;
	});
	std::vector <double> measured_values (N);
	i = 0;
	for_each (measured_values.begin(), measured_values.end(), [&i, digitized, bit_capacity](double &value) {
	value = (digitized[i])*3.2/bit_capacity;//обратное преобразование, с искажениями сигнала оцифровкой
	i++;
	});
	i = 0;
	for_each (true_values.begin(), true_values.end(), [measured_values, &i] (double &value) {
	value -= measured_values[i];
	value *=value; 
	i++;
	});
	std::sort (true_values.begin(), true_values.end());
	double maximum = std::sqrt(*(true_values.end() - 1));
	std::cout << number_of_bits << ' ' << maximum <<std::endl;// вывожу на печать максимальное полученное отклонение от истинного
								//значения
	double result = std::accumulate (true_values.begin(), true_values.end(), 0.0);
	result /= N;
	result = std::sqrt (result);
	return result;
}
void Task2 () {
	double eight_bits, sixteen_bits, twenty_four_bits;
	eight_bits = 0;
	sixteen_bits = 0;
	twenty_four_bits = 0;
	for (int i = 0; i < 10; i++){
		eight_bits += dig_signal (8, 100000);
		sixteen_bits += dig_signal (16, 100000);
		twenty_four_bits += dig_signal (24, 100000);
	}
	std::cout << "Eight_bits : " << (eight_bits/10) << std::endl;
	std::cout << "Sixteen_bits : " << (sixteen_bits/10) << std::endl;
	std::cout << "Twenty_four_bits : " << (twenty_four_bits/10) << std::endl;
}


void Task1_test () {
	
	std::deque <double> V1 (10);
	std::srand(std::time(nullptr));
	for_each (V1.begin(), V1.end(), [](double &value){
	value = rand()%100;
	value += static_cast <double>(rand()%100)/100; 
	return value;
	});
	std::sort (V1.begin(), V1.end(), [](int x, int y){return y <= x;});
	for_each (V1.begin(), V1.end(), [](double value) {
	std::cout << value <<' ';
	});
	std::cout << std::endl;
	insert_sorted (V1, 50.325);
	for_each (V1.begin(), V1.end(), [](double value) {
	std::cout << value <<' ';
	});
	std::cout << std::endl;
}
int main () {
	Task1_test ();
//	Task2 ();
	
    
	return 0;
}
