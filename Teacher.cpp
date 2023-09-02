#include "Teacher.hpp"

Teacher::Teacher(){
	this->name = "Unknown";
	this->surname = "Unknown";
	this->subject = "Unknown";
	this->age = 0;
	this->salary = 0.0;
}

Teacher::Teacher(std::string name, std::string surname, std::string subject, int age, double salary)
	:name{ name }, surname{ surname }, subject{ subject }, age{ age }, salary{ salary } {
}

Teacher::Teacher(const Teacher& source)
:Teacher(source.name, source.surname, source.subject, source.age, source.salary){
}

std::string Teacher::get_name() const{
	return this->name;
}

std::string Teacher::get_surname() const {
	return this->surname;
}

std::string Teacher::get_subject() const {
	return this->subject;
}

int Teacher::get_age() const {
	return this->age;
}

double Teacher::get_salary() const {
	return this->salary;
}