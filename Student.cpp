#include <iostream>
#include <iomanip>
#include "Student.hpp"

std::ostream& operator<<(std::ostream& os, const Student rhs){
	os << std::setw(15) << std::left << rhs.name << std::setw(15) << rhs.surname << std::setw(10) << rhs.group << std::setw(3) << rhs.age << std::endl;
	return os;
}

bool Student::operator==(const Student rhs)const {
	return this->name == rhs.name && this->surname == rhs.surname && this->group == rhs.group && this->age == rhs.age;
}