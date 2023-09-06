#pragma once
#include <iostream>
#include <string>
#include "I_Printable.hpp"
#include "Student.hpp"

class Person :public I_Printable{
private:
	std::string name;
	std::string surname;
	int age;
public:
	Person() = default;
	Person(std::string, std::string, int);
	Person(const Person& source);
	std::string get_name() const;
	std::string get_surname() const;
	int get_age() const;

	void set_name(std::string);
	void set_surname(std::string);
	void set_age(int);

	virtual void print(std::ostream& os) const;
	virtual void show_list(const std::vector<Person>&) const;
};
