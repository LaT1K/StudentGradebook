#pragma once
#include <string>
#include <fstream>
#include "Functions.hpp"
#include "Person.hpp"
#include "I_Printable.hpp"
class Student : public Person{
private:
	std::string group;
public:
	Student() = default;
	Student(std::string, std::string, std::string, int);
	Student(const Student&);
	std::string get_group() const override;
	void set_group(std::string);
	bool operator==(const Student) const;
	void input_data_about_student(Student&);
	virtual void print(std::ostream& os) const override;
	virtual void show_list() const override;
};

//std::vector<Person*> get_student_list(std::ifstream&);
//void launch_students_menu();
//bool does_group_exist(std::vector<Student>&, std::ifstream&, std::string);
//void rewrite_data_to_file(std::vector<Student>, std::ofstream&);
//void add_student(std::ofstream&, std::ifstream&);
//bool does_already_exist(const Student, std::ifstream&);
//bool delete_student(std::vector<Student>&, const Student&);
//bool find_student(const std::vector<Student>&, std::string);

void launch_students_menu();
enum class Students_menu { Show = 1, Add, Find, Delete, Group };


