#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Functions.hpp"
#include "Person.hpp"

class Teacher : public Person{
private:
	std::string subject;
	double salary{};
public:
	Teacher() = default;
	Teacher(std::string name, std::string surname, int age, std::string subject, double salary);
	Teacher(const Teacher& source);
	std::string get_subject() const;
	double get_salary() const;
	void set_subject(std::string);
	void set_salary(double);
	virtual void print(std::ostream& os) const override;
	virtual void show_list() const override;
	virtual void init() override;
	std::string get_group() const override;
	bool operator==(const Person* rhs) const;
};

const int NUMBER_OF_OPTIONS_TEACHERS_MENU{ 5 };
const std::string TEACHER_LIST{ "Teachers.txt" };
void launch_teachers_menu();
enum class Teachers_menu { Show = 1, Add, Find, Delete };
std::vector<std::shared_ptr<Person>> get_teacher_list(std::ifstream& ifile);
void add_teacher(std::ofstream& ofile);