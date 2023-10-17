#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "I_Printable.hpp"
#include "Functions.hpp"

class Person :public I_Printable{
private:
	std::string name;
	std::string surname;
	int age;
public:
	Person();
	Person(std::string, std::string, int);
	Person(const Person& source);
	std::string get_name() const;
	std::string get_surname() const;
	int get_age() const;

	void set_name(std::string);
	void set_surname(std::string);
	void set_age(int);

	virtual void init();
	virtual void print(std::ostream& os) const;
	virtual void show_list() const;
	virtual std::string get_group() const = 0;
	virtual std::string get_subject() const = 0;
};
