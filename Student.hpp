#pragma once
#include <string>
#include <fstream>
#include "Functions.hpp"
#include "Person.hpp"


class Student : public Person{
private:
	std::string group;
public:
	Student() = default;
	Student(std::string, std::string, int, std::string);
	Student(const Student&);
	void set_group(std::string);
	bool operator==(const Person*) const;
	//void input_data_about_student(Student&);
    void print(std::ostream& os) const override;
	void show_list() const override;
	void init() override;
	std::string get_group() const override;
	std::string get_subject() const override;
};

void launch_students_menu();
enum class Students_menu { Show = 1, Add, Find, Delete, Group };