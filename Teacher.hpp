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
	Teacher();
	Teacher(std::string name, std::string surname, std::string subject, int age = 0, double salary = 0.0);
	Teacher(const Teacher& source);
	std::string get_subject() const;
	double get_salary() const;
	void set_subject(std::string);
	void set_salary(double);
	virtual void print(std::ostream& os) const override;
	virtual void show_list() const override;
	virtual void init() override;
	std::string get_group() const override;
};

enum class Teachers_menu { Show = 1, Add, Find, Delete };

//void launch_teachers_menu();
//std::vector<Teacher> get_teacher_list(std::ifstream &);
//void add_teacher(std::ofstream&, std::ifstream&);