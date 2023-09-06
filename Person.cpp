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
	os << std::setw(15) << std::left << this->get_name() << std::setw(15) << this->get_surname() << std::setw(3) << this->get_age() << std::endl;
}

void Person::show_list(const std::vector<Person>& list) const {
	std::cout << std::setw(15) << std::left << "Name" << std::setw(15) << "Surname" << std::setw(3) << "Age\n";
	for (auto& person : list)
			std::cout << person;
}