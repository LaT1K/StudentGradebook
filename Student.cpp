#include <iostream>
#include <iomanip>
#include "Student.hpp"

std::string Student::get_name() const {
    return name;
}
std::string Student::get_surname() const {
    return surname;
}
std::string Student::get_group() const {
    return group;
}
int Student::get_age() const {
    return age;
}
void Student::set_name(std::string name) {
    this->name = name;
}
void Student::set_surname(std::string surname) {
    this->surname = surname;
}
void Student::set_group(std::string group) {
    this->group = group;
}
void Student::set_age(int age) {
    this->age = age;
}

Student::Student() = default;

Student::Student(std::string name, std::string surname, std::string group, int age)
    :name{ name }, surname{ surname }, group{ group }, age{ age } {
}

Student::Student(const Student& source) :Student(source.name, source.surname, source.group, source.age) {
}

std::ostream& operator<<(std::ostream& os, const Student rhs){
	os << std::setw(15) << std::left << rhs.name << std::setw(15) << rhs.surname << std::setw(10) << rhs.group << std::setw(3) << rhs.age << std::endl;
	return os;
}

bool Student::operator==(const Student rhs)const {
	return this->name == rhs.name && this->surname == rhs.surname && this->group == rhs.group && this->age == rhs.age;
}

void input_data_about_student(Student& student) {
    std::string name, surname, group, age;
    int age_int;
    bool is_correct{ true };
    do {
        std::cout << "Enter student's name: ";
        std::cin >> name;
        if (is_available_input_for_word(name)) {
            is_correct = true;
            student.set_name(name);
        }
        else {
            std::cout << "Name can contain only letters\n";
            is_correct = false;
        }
    } while (!is_correct);

    do {
        std::cout << "Enter student's surname: ";
        std::cin >> surname;
        if (is_available_input_for_word(surname)) {
            is_correct = true;
            student.set_surname(surname);
        }
        else {
            std::cout << "Surname can contain only letters\n";
            is_correct = false;
        }
    } while (!is_correct);

    std::cout << "Enter student's group: ";
    std::cin >> group;
    student.set_group(group);

    do {
        std::cout << "Enter student's age: ";
        std::cin >> age;
        if (is_available_input_for_number(age)) {
            is_correct = true;
            std::stringstream ss{ age };
            ss >> age_int;
            student.set_age(age_int);
        }
        else {
            std::cout << "Age can contain only numbers\n";
            is_correct = false;
        }
    } while (!is_correct);
}
