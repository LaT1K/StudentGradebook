#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Functions.hpp"

class Teacher{
private:
	std::string name;
	std::string surname;
	std::string subject;
	int age{};
	double salary{};
public:
	Teacher();
	Teacher(std::string name, std::string surname, std::string subject, int age = 0, double salary = 0.0);
	Teacher(const Teacher& source);
	std::string get_name() const;
	std::string get_surname() const;
	std::string get_subject() const;
	int get_age() const;
	double get_salary() const;
	void set_name(std::string);
	void set_surname(std::string);
	void set_subject(std::string);
	void set_salary(double);
	void set_age(int age);
	friend std::ostream& operator<<(std::ostream&, const Teacher);
};

enum class Teachers_menu { Show = 1, Add, Find, Delete };

void launch_teachers_menu();
std::vector<Teacher> get_teacher_list(std::ifstream&);
void show_list(const std::vector<Teacher>&);
void add_teacher(std::ofstream&, std::ifstream&);