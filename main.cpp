#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Task2.pb.h"
/*Создать класс StudentsGroup, который реализует интерфейсы:
class IRepository {
    virtual void Open() = 0; // бинарная десериализация в файл
    virtual void Save() = 0; // бинарная сериализация в файл
};


class IMethods {
    virtual double GetAverageScore(const FullName& name) = 0;
    virtual string GetAllInfo(const FullName& name) = 0;
    virtual string GetAllInfo() = 0;
};*/
class IRepository {
    virtual void Open() = 0; // бинарная десериализация в файл
    virtual void Save() = 0; // бинарная сериализация в файл
};
namespace my_class {
class IMethods {
    virtual double GetAverageScore(const University::FullName& name) = 0;
    virtual std::string GetAllInfo(const University::FullName& name) = 0;
    virtual std::string GetAllInfo() = 0;
};

class StudentsGroup : public IMethods, IRepository {
	University::StudentsGroup m_Group;
	
	public :
	StudentsGroup () {}///////////////////////////////////////////////////////////////////////////////
	StudentsGroup (const University::StudentsGroup& Group) {/////////////////////////////////////////////////////////
		m_Group.CopyFrom(Group);
	}
	double GetAverageScore(const University::FullName& name) override {//////////////////////////////////////////////////////////
		University::Student a_student;
		for (int i = 0; i < m_Group.m_group_size(); i++) {
			a_student = m_Group.m_group(i);
			University::FullName* N = a_student.mutable_m_fullname();
		if (N -> m_name() == name.m_name()||N -> m_middle_name() == name.m_middle_name()||N -> m_last_name() == name.m_last_name()) return a_student.m_medium_score();
		}
		std::cout << "Student is not find" << std::endl;
		return 0;
	}
	std::string GetAllInfo(const University::FullName& name) override {//////////////////////////////////////////////////////
		University::Student a_student;
		for (int i = 0; i < m_Group.m_group_size(); i++) {
			a_student = m_Group.m_group(i);
			University::FullName* N = a_student.mutable_m_fullname();
		if (N -> m_name() == name.m_name()||N -> m_middle_name() == name.m_middle_name()||N -> m_last_name() == name.m_last_name()) return a_student.DebugString();
		}
		return "";
	}
	std::string GetAllInfo() override {///////////////////////////////////////////////////////////////////////////
		return m_Group.DebugString();
	} 
	void Save () override {////////////////////////////////////////////////////////////////////////////////////////////
		std::fstream fout("test.txt", std::ios::out | std::ios::trunc | std::ios::binary);
		m_Group.SerializeToOstream(&fout);
	}
	void Open () override {/////////////////////////////////////////////////////////////////////////////////////////////
		std::fstream finp("test.txt", std::ios::in | std::ios::binary);
		m_Group.ParseFromIstream(&finp);
	}
};
}
using namespace University;
using std::begin;
using std::end;
int main () {
/*Создаю первого студента*/
	FullName children;
	children.set_m_name("Aleksandr");
	children.set_m_middle_name ("Yaroslavovich");
	children.set_m_last_name ("Nevskiy"); 
	Student st;
	st.add_m_scores(5);
	FullName* f = st.mutable_m_fullname();
	f -> CopyFrom(children);
	st.set_m_medium_score (5.0);
	StudentsGroup G;
	Student* S;
	S = G.add_m_group();
	*S = st;
/*Создаю второго студента*/
	children.set_m_name ("Igor");
	children.set_m_middle_name ("Ivanovich");
	children.set_m_last_name ("Boreyko");
	f -> CopyFrom (children);
	st.add_m_scores (5);
	st.add_m_scores (4);
	st.set_m_medium_score (5.0);
	S = G.add_m_group();
	*S = st;
/*Создаю экземпляр класса my_class::StudentsGroup, содержащий созданных студентов*/
	my_class::StudentsGroup Gr (G);
	std::cout << Gr.GetAverageScore (*f) << std::endl;// выводим среднюю оценку у Борейко, он создавался вторым
	std::cout << Gr.GetAllInfo(*f);// выводим полную информацию о Борейко
	Gr.Save();
	my_class::StudentsGroup Group;
	Group.Open();
	std::cout<< Group.GetAllInfo() << std::endl;
	google::protobuf::ShutdownProtobufLibrary();
	std::cout << "Final" << std::endl;// все четко, все присутствует
	return 0;
}


