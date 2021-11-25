#include <iostream>




class IT {
	int* m_mass;
	int m_size;
	public:
	IT ( int* mass,int size) {
		m_size = size;
		m_mass = mass;
	}
	int* begin () {return m_mass;}
	int* end () {return m_mass + m_size;} 
	~IT () {}
};

int main (void) {
	int M[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	IT it (M, 10);
	for (auto n : it) {
		std::cout<<n<<' ';
	}

}
