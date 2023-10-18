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

void Person::init() {
    bool is_correct = false;
    do {
        std::cout << "Enter name: ";
        std::cin >> this->name;
        if (is_available_input_for_word(name)) {
            is_correct = true;
            this->set_name(name);
        }
        else {
            std::cout << "Name can contain only letters\n";
            is_correct = false;
        }
    } while (!is_correct);

    do {
        std::cout << "Enter surname: ";
        std::cin >> this->surname;
        if (is_available_input_for_word(surname)) {
            is_correct = true;
            this->set_surname(surname);
        }
        else {
            std::cout << "Surname can contain only letters\n";
            is_correct = false;
        }
    } while (!is_correct);

    do {
        std::string is_age;
        std::cout << "Enter age: ";
        std::cin >> is_age;
        if (is_available_input_for_number(is_age)){
            std::stringstream ss{ is_age };
            is_correct = true;
            ss >> this->age;
            this->set_age(age);
        }
        else {
            std::cout << "Age can contain only numbers\n";
            is_correct = false;
        }
    } while (!is_correct);
}