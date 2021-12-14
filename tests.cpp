#include "whattotest.cpp"
#include <gtest/gtest.h>
TEST (Task1Test, OptionalMiddleName) {//проверка установки значения отчества в nullopt при установке соответствующего флага
	Person person ("Ivan" , "Ivanov", false);
	ASSERT_TRUE(person.m_Middle_name == std::nullopt);//проверка возможности сравнения двух записей с nullopt
	Person person2 ("Ivan" , "Ivanov", false);
	ASSERT_TRUE (person2 == person);
}

TEST (Task1Test, Compare_operators_test) {//проверка операторов сравнения
	Person person1 ("Ivan", "Ivanov", true, "Ivanovich");//запись по алфавиту находится раньше
	Person person2 ("Sergy", "Sergeev", true, "Sergeevich");//запись по алфавиту находится позже
	Person person3 ("Sergy", "Sergeev", false);//запись по алфавиту по прежнему находится позже, чем person 1
	ASSERT_TRUE (person1 < person2);
	ASSERT_FALSE (person2 < person1);
	ASSERT_TRUE (person1 < person3);
}
TEST (Task2Test, Output) {// проверка верной формы оператора вывода
	PhoneNumber phone1 (7, 902, "5091605", std::nullopt);// создам два телефонных номера phone1 и phone2 и помещу их в файл 
	std::ofstream Test_ostream ("Test2_output");
	Test_ostream << phone1 << std::endl;
	PhoneNumber phone2 (7, 902, "5091605", 6);
	Test_ostream << phone2 << std::endl;
	Test_ostream.close();
	std::ifstream Test_istream ("Test2_output");
	std::string Test_string;
	std::getline (Test_istream, Test_string);//читаю из файла phone 1
	size_t number_of = static_cast<size_t>(Test_string.end() - Test_string.begin());
	char* s = new char [number_of];
	for (size_t i = 0; i < number_of; i++) s[i] = Test_string[i];
	EXPECT_STREQ ("+7(902)5091605", s);// смотрю, что он удовлетворяет условию
	Test_string.clear();
	std::getline (Test_istream, Test_string);//читаю из файла phone2
	number_of = static_cast<size_t>(Test_string.end() - Test_string.begin());
	s = new char [number_of];
	for (size_t i = 0; i < number_of; i++) s[i] = Test_string[i];
	EXPECT_STREQ ("+7(902)5091605 6", s);// смотрю, что он удовлетворяет условию
	Test_istream.close();
	delete s;
	
}
TEST (Task2Test, Compare) {// операторы сравнения для phonenumber
{
	PhoneNumber phone1(7, 982, "5091605", std::nullopt);
	PhoneNumber phone2(7, 981, "5091605", 6);
	ASSERT_TRUE (phone2 < phone1);
	ASSERT_FALSE (phone2 == phone1);
	ASSERT_FALSE (phone1 < phone2);
}
{
	PhoneNumber phone1(7, 982, "5091605", std::nullopt);
	PhoneNumber phone2(7, 982, "5091605", std::nullopt);
	ASSERT_TRUE (phone1 == phone2);
}
{
	PhoneNumber phone1(7, 982, "5091605", 10);
	PhoneNumber phone2(7, 982, "5091605", 10);
	ASSERT_TRUE (phone1 == phone2);
}
}
TEST (Task3Test, GetPhone_test) {//тест для функции GetPhoneNumber
	std::ifstream fin("PhoneBook.txt");
	PhoneBook book (fin);
	std::tuple <std::string, std::optional <PhoneNumber>> w = book.GetPhoneNumber ("Ivanov");
	if (!(std::get<0>(w).empty())) FAIL ();//если не найден или не один - крах теста
	PhoneNumber phone (7, 366, "7508887", std::nullopt);//заданный телефон Иванова в PhoneBook
	EXPECT_TRUE (std::get<1>(w) == phone);// должен совпасть
	w = book.GetPhoneNumber ("Petrov");//Петрова нет
	std::string s = "Not found";
	EXPECT_TRUE (std::get<0>(w) == s);//должны получить, что таковой не найден
	fin.close();
}
TEST (Task3Test, ChangePhoneNumber_test) {//проверка замены телефона
	std::ifstream fin("PhoneBook.txt");
	PhoneBook book (fin);
	PhoneNumber num (1, 1, "1111", std::nullopt);
	Person Kotov ("Vasilii", "Kotov", true, "Eliseevich");
	book.ChangePhoneNumber (Kotov, num);//меняю
	std::tuple <std::string, std::optional <PhoneNumber>> w = book.GetPhoneNumber ("Kotov");//читаю
	if (!(std::get<0>(w).empty())) FAIL();//если не найден, то фэйл
	EXPECT_TRUE (std::get<1>(w) == num);//должен совпасть с измененным
}


int main() {
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}


