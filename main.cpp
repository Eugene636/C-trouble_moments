#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <list>
///////////////////////////////////////////////*Task 1*//
void Med_ar (std::list <double> & Input) {
	double out = 0;
	int i = 0;
	for (auto n : Input) {
		out += n;
		i++;
	}
	out /= i;
	Input.push_back(out);

}



///////////////////////////////////////////////////////////////////////////////////// /*Task 2*/
class Matrix {
	int m_col;
	int m_str;
	std::vector<std::vector<double>> m_Matrix;
	
public:
	Matrix () {}
	Matrix (std::vector <std::vector<double>> inp_vect) {
		m_str = inp_vect.size ();
		m_col = inp_vect[0].size ();
		for (int i = 1; i < m_str; i++) {
			if (m_col != inp_vect[i].size()) {
			std::cout << "This table is not a matrix"<< std::endl;
			}
		}
		m_Matrix = inp_vect;
	}
	void print () {
		for (int i = 0; i < m_str; i++){
			for (int j = 0; j < m_col; j++)
				std::cout << m_Matrix[i][j] << ' ';
			std::cout << std::endl;
			}
	}
	double Det(int column = 0) {
		if (m_col == 1 ) return m_Matrix[0][0];
		
		double out = 0;
		for (column = 0; column < m_col; column++) {
		Matrix matrix;
		for (int i = 1; i < m_str; i++) {
			std::vector <double> temp;
			for (int j = 0; j < m_col; j++) {
				if (j != column) temp.push_back(m_Matrix[i][j]);
			}
			matrix.m_Matrix.push_back(temp);
		}
		matrix.m_col = m_col - 1;
		matrix.m_str = m_str - 1;
		out += std::pow (-1, column + 2)*m_Matrix[0][column]*matrix.Det (column);;
		}
		return out;
	}
};

////////////////////////////////////////////////////////////*Task 3*/
class IT {
	int* m_mass;
	int m_size;
public:
	IT (int size) {
		m_size = size;
		m_mass = new int [size];
	}
	int* begin () {return m_mass;}
	int* end () {return m_mass + m_size;} 
	~IT () {
		delete [] m_mass;
	}
};
void Task1_test () {
	std::list <double> Numbers {1, 5, 10, 6, 7, 8};
	for (auto n : Numbers) {
		std::cout << n <<' ';
	}
	std::cout << std::endl;
	Med_ar (Numbers);
	for (auto n : Numbers) {
		std::cout << n <<' ';
	}
	std::cout << std::endl;
}
void Task2_test() {
	IT it (10);
	int k = 0;
	std::cout << std::endl;
	std::for_each (it.begin(), it.end(), [k](int& i)mutable{i = k; k++;});
	for (auto n: it){std::cout << n <<' ';}
}

void Task3_test () {
	std::vector<std::vector<double>> inp_vect= {
	/*{1, 2, 3, 4, 5},
	{1, 2, 3, 4, 5},
	{6, 7, 8, 9, 10},
	{6, 7, 8, 9, 10},
	{11, 12, 13, 14, 15}*/
	{45, 85, 95, 5},
	{15, 11, 78, 4},
	{56, 12, 79, 17},
	{13, 5 , 1, 36}
	};
/*	for (int i = 1; i < 5; i++){
		std::vector <double> temp;
		for (int j = 1; j < 5; j++) temp.push_back(i*j);
		inp_vect.push_back(temp);
	}*/
	Matrix matrix (inp_vect);
	matrix.print();
	std::cout << matrix.Det() << std::endl;
}
int main (void) {
	Task1_test ();
	Task2_test ();
	std::cout <<std::endl;
	Task3_test ();

	return 0;
}
