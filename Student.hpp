#pragma once
#include <string>

class Student {
private:
	std::string name;
	std::string surname;
	std::string group;
	int age;
public:
	std::string get_name() const {
		return name;
	}
	void set_name(std::string name) {
		this->name = name;
	}
	std::string get_surname() const {
		return surname;
	}
	void set_surname(std::string surname) {
		this->surname = surname;
	}
	std::string get_group() const {
		return group;
	}
	void set_group(std::string group) {
		this->group = group;
	}
	int get_age() const {
		return age;
	}
	void set_age(int age) {
		this->age = age;
	}
	Student() = default;
	Student(std::string name, std::string surname, std::string group, int age)
		:name{ name }, surname{ surname }, group{ group }, age{ age } {
	}
	Student(const Student& source) :Student(source.name, source.surname, source.group, source.age) {
	}
	bool operator==(const Student rhs) const;
	friend std::ostream &operator<<(std::ostream& os, const Student rhs);
};