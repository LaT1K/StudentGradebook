#pragma once
#include <string>
#include <fstream>
#include "Functions.hpp"

class Student {
private:
	std::string name;
	std::string surname;
	std::string group;
	int age;
public:
	Student();
	Student(std::string, std::string, std::string, int);
	Student(const Student&);
	std::string get_name() const;
	std::string get_surname() const;
	std::string get_group() const;
	int get_age() const;
	void set_name(std::string);
	void set_surname(std::string);
	void set_group(std::string);
	void set_age(int age);
	bool operator==(const Student) const;
	friend std::ostream &operator<<(std::ostream&, const Student);
	friend void input_data_about_student(Student&);
	friend void show_students(const std::vector<Student>&);
	friend void show_students(const std::vector<Student>&, std::string);
	friend bool does_already_exist(const Student, std::ifstream&);
	friend void add_student(std::ofstream&, std::ifstream&);
	friend void rewrite_data_to_file(std::vector<Student>, std::ofstream&);
	friend bool does_group_exist(std::vector<Student>&, std::ifstream&, std::string);
};