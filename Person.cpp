#include "Person.hpp"

std::string Person::get_name() const {
	return name;
}

std::string Person::get_surname() const {
	return surname;
}

int Person::get_age() const {
	return age;
}

void Person::set_name(std::string name) {
	this->name = name;
}

void Person::set_surname(std::string surname) {
	this->surname = surname;
}

void Person::set_age(int age) {
	this->age = age;
}

Person::Person(std::string name, std::string surname, int age)
	:name{ name }, surname{ surname }, age{ age } {
}

Person::Person(const Person& source)
:Person(source.name, source.surname, source.age){
}

void Person::print(std::ostream& os) const {
	os << std::setw(15) << std::left << this->get_name() << std::setw(15) << this->get_surname() << std::setw(3) << this->get_age();
}

void Person::show_list() const {
	std::cout << std::setw(15) << std::left << this->get_name() << std::setw(15) << this->get_surname() << std::setw(10) << this->get_age();
}

std::string Person::get_group() const {
	return "";
}
//
//bool Person::operator==(const Person rhs) const {
//	return this->get_name() == rhs.get_name() && this->get_surname() == rhs.get_surname() && this->get_group() == rhs.get_group() && this->get_age() == rhs.get_age();
//
//}

bool operator==(Person* lhs, const Person rhs) {
	return lhs->get_name() == rhs.get_name() && lhs->get_surname() == rhs.get_surname() && lhs->get_group() == rhs.get_group() && lhs->get_age() == rhs.get_age();
}