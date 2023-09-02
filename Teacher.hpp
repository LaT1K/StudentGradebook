#pragma once
#include <iostream>
#include <string>

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
};