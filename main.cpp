#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> 
#include <optional>
#include <tuple>
#include <algorithm>
std::vector<std::string> split (const std::string &s, char delim) {
std::vector<std::string> result;
std::stringstream ss (s);
std::string item;

while (std::getline (ss, item, delim)) {
result.push_back (item);
}
return result;
}
///////////////////////////////////////////////////////
                                                   /*         1 Task            */
struct Person {
	std::string m_Name;
	std::string m_Surname;
	std::optional <std::string> m_Middle_name;
	Person (std::string Name, std::string Surname, bool Middle_name_yes, std::string Middle_name = " "): m_Name {Name}, m_Surname {Surname} {
	if (Middle_name_yes) m_Middle_name = Middle_name;
		else m_Middle_name = std::nullopt;
	} 
	Person () {}
	friend std::ostream& operator << (std::ostream& os, Person& person);
	friend bool operator < (const Person& l, const Person& r);
	friend bool operator == (const Person& l, const Person& r);
};

bool operator < (const Person& l, const Person& r) {
	std::tuple L = std::tie (l.m_Surname, l.m_Name, l.m_Middle_name);
	std::tuple R = std::tie (r.m_Surname, r.m_Name, r.m_Middle_name);
	return L < R;
}
bool operator == (const Person& l, const Person& r) {
	if ( l < r ) return false;
	if ( r < l ) return false;
	return true;
}
std::ostream& operator << (std::ostream& os, const Person& person) {
	os << person.m_Name<<' '<< person.m_Middle_name.value_or("No Middle Name")<<' '<<person.m_Surname;
	return os;
}

////////////////////////////////////////////////////////////////
                                         /*       2 Task               */
struct PhoneNumber {
	int m_country_code;
	int m_City_code;
	std::string m_abonent_num;
	std::optional <int> m_addit_num;
	PhoneNumber (int country_code, int City_code, std::string abonent_num, std::optional <int> addit_num) : m_country_code{country_code}, m_City_code{City_code}, m_abonent_num {abonent_num}, m_addit_num{addit_num} {}
	PhoneNumber() {}
	friend std::ostream& operator << (std::ostream& os, const PhoneNumber& phonenumber); 
	friend bool operator < (const PhoneNumber& l, const PhoneNumber& r);
};

bool operator < (const PhoneNumber& l, const PhoneNumber& r) {
	std::tuple L = std::tie (l.m_country_code, l.m_City_code, l.m_abonent_num, l.m_addit_num);
	std::tuple R = std::tie (r.m_country_code, r.m_City_code, r.m_abonent_num, r.m_addit_num);
	return L < R;
}
bool operator == (const PhoneNumber& l, const PhoneNumber& r) {
	if ( l < r ) return false;
	if ( r < l ) return false;
	return true;
}

std::ostream& operator << (std::ostream& os, const PhoneNumber& phonenumber) {
	os << "+"<<phonenumber.m_country_code<<'('<<phonenumber.m_City_code<<')'<<phonenumber.m_abonent_num;
	if (phonenumber.m_addit_num) os<<' '<<phonenumber.m_addit_num.value();
	return os;
}
///////////////////////////////////////////////////////////////////
                                                          /* Task 3*/
/*Создайте класс PhoneBook, который будет в контейнере хранить пары: Человек – Номер телефона. Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла. В теле конструктора происходит считывание данных из файла и заполнение контейнера. Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.
В классе PhoneBook реализуйте метод SortByName, который должен сортировать элементы контейнера по фамилии людей в алфавитном порядке. Если фамилии будут одинаковыми, то сортировка должна выполняться по именам, если имена будут одинаковы, то сортировка производится по отчествам. Используйте алгоритмическую функцию sort.
Реализуйте метод SortByPhone, который должен сортировать элементы контейнера по номерам телефонов. Используйте алгоритмическую функцию sort.
Реализуйте метод GetPhoneNumber, который принимает фамилию человека, а возвращает кортеж из строки и PhoneNumber. Строка должна быть пустой, если найден ровно один человек с заданном фамилией в списке. Если не найден ни один человек с заданной фамилией, то в строке должна быть запись «not found», если было найдено больше одного человека, то в строке должно быть «found more than 1». 
Реализуйте метод ChangePhoneNumber, который принимает человека и новый номер телефона и, если находит заданного человека в контейнере, то меняет его номер телефона на новый, иначе ничего не делает. */
enum Fields {Name, Middle_name, Surname, Country_code, City_code, Number, Addition_number};
class PhoneBook {
	std::vector <std::pair <Person, PhoneNumber>> m_Entries; 
	Person Abonent;
	PhoneNumber AbonentNumber;
	public:
	PhoneBook (std::ifstream& fin) {
		std::string input_str;
		while (std::getline(fin, input_str)) {
			std::vector<std::string> members = split (input_str, ' ');
			Abonent.m_Surname = members[0];
			if ((members[2])[0] == '-') {
				Abonent.m_Name = members[1];
				Abonent.m_Middle_name = std::nullopt;
			}
			else {
				Abonent.m_Middle_name = members[2];
				Abonent.m_Name = members[1];
			}
			
			AbonentNumber.m_country_code = std::stoi(members[3]);
			AbonentNumber.m_City_code = std::stoi(members[4]);
			AbonentNumber.m_abonent_num = members[5];
			if (members[6][0] == '-') AbonentNumber.m_addit_num = std::nullopt;
			else AbonentNumber.m_addit_num = std::stoi(members[6]);
			m_Entries.push_back(std::make_pair (Abonent, AbonentNumber));
		}

	//	else std::cout<<"EOF" <<std::endl;


	}
	friend std::ostream& operator << (std::ostream& os, const PhoneBook& phonebook);
	void SortByName();
	void SortByPhone ();
	std::tuple<std::string, std::optional<PhoneNumber>> GetPhoneNumber (const std::string& surname);
	void ChangePhoneNumber (Person& person, PhoneNumber& phonenumber);
	
};
void PhoneBook::SortByName() {
	std::sort (m_Entries.begin(), m_Entries.end(), [](std::pair<Person, PhoneNumber> &lhs, std::pair<Person, PhoneNumber> &rhs) ->
	bool { return lhs.first < rhs.first;});
}

void PhoneBook::SortByPhone() {
		std::sort (m_Entries.begin(), m_Entries.end(), [](std::pair<Person, PhoneNumber> &lhs, std::pair<Person, PhoneNumber> &rhs) ->
	bool { return lhs.second < rhs.second;});
}
std::tuple<std::string, std::optional<PhoneNumber>> PhoneBook::GetPhoneNumber (const std::string& surname) {
	std::pair <Person, PhoneNumber> abonent;
	int count = 0;
	Person person;
	PhoneNumber phonenumber;
	for (const auto &p : m_Entries) {
		person = p.first;
		if ((person.m_Surname == surname) && (count == 0)) {
			count++;
			phonenumber = p.second;
		}
		if ((person.m_Surname == surname) && (count > 0) ) break;
	}
	if (count == 0) return std::tie ("Not found", std::nullopt);
	if (count == 1) {
		std::string t;
		return std::tie (t, phonenumber);
	}
	if (count > 1)  return std::tie ("found more than 1", std::nullopt);
}
void PhoneBook::ChangePhoneNumber (Person& person, PhoneNumber& phonenumber){
	for (auto &p : m_Entries) {
		if (p.first == person) p.second = phonenumber;
	}
}

std::ostream& operator << (std::ostream& os, const PhoneBook& phonebook) {
	for (auto const& n: phonebook.m_Entries) {
		os<<n.first<<n.second << std::endl;
	}
	return os;
}
int main () {

	std::ifstream file("PhoneBook.txt");
	PhoneBook book(file);
       std::cout << book;
 
       std::cout << "------SortByPhone-------" << std::endl;
       book.SortByPhone();
       std::cout << book;
 
       std::cout << "------SortByName--------" << std::endl;
       book.SortByName();
       std::cout << book;
 
       std::cout << "-----GetPhoneNumber-----" << std::endl;
       // лямбда функция, которая принимает фамилию и выводит номер телефона этого        человека, либо строку с ошибкой
       auto print_phone_number = [&book](const std::string& surname) { 
              std::cout << surname << "\t"; 
              auto answer = book.GetPhoneNumber(surname); 
              if (std::get<0>(answer).empty()) 
                     std::cout << (std::get<1>(answer)).value(); 
              else 
                     std::cout << std::get<0>(answer); 
                     std::cout << std::endl; 
       };

       // вызовы лямбды
       print_phone_number("Ivanov");
       print_phone_number("Petrov");
 
       std::cout << "----ChangePhoneNumber----" << std::endl;
       Person Kotov = {"Kotov", "Vasilii", "Eliseevich" };
       PhoneNumber Kotov_ph = {7, 123, "15344458", std::nullopt};
       Person Mironova = { "Mironova", "Margarita", "Vladimirovna" };
       PhoneNumber Mironova_ph = { 16, 465, "9155448", 13 };
       book.ChangePhoneNumber(Kotov, Kotov_ph);
       book.ChangePhoneNumber(Mironova, Mironova_ph);
       std::cout << book;
	return 0;
}
