﻿#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Student.hpp"
#include "Teacher.hpp"
#include "Functions.hpp"

const int NUMBER_OF_OPTIONS_STUDENTS_MENU{ 6 };
const int NUMBER_OF_OPTIONS_TEACHERS_MENU{ 5 };
const int NUMBER_OF_OPTIONS_MAIN_MENU{ 3 };

enum class Main_menu { Students = 1, Teachers };
enum class Students_menu { Show = 1, Add, Find, Delete, Group };
enum class Teachers_menu{Show = 1, Add, Find, Delete};

std::vector<Student> student_list;
std::string name, surname, group;
int age{}, is_integer{};
std::ifstream ifile;
std::ofstream ofile;
std::string user_input{};
Student student;

std::vector<Student> get_student_list(std::ifstream& ifile) {
    std::string line;
    std::string name, surname, group;
    int age;
    std::vector<Student> student_list;
    while (std::getline(ifile, line)) {
        std::stringstream ss{ line };
        ss >> name >> surname >> group >> age;
        student_list.push_back({ name, surname, group, age });
    }
    return student_list;
}

void show_students(const std::vector<Student>& student_list) {
    std::cout << std::setw(15) << std::left << "Name" << std::setw(15) << "Surname" << std::setw(10) << "Group" << std::setw(3) << "Age\n";
    for (auto& elem : student_list)
        std::cout << elem;
}

void show_students(const std::vector<Student>& student_list, std::string group_name) {
    std::cout << std::setw(15) << std::left << "Name" << std::setw(15) << "Surname" << std::setw(10) << "Group" << std::setw(3) << "Age\n";
    for (auto& student : student_list)
        if (student.get_group() == group_name)
            std::cout << student;
}

bool find_student(const std::vector<Student>& student_list, std::string surname) {
    bool x = false;
    for (const auto elem : student_list) {
        if (elem.get_surname() == surname) {
            std::cout << elem;
            x = true;
        }
    }
    return x;
}

bool delete_student(std::vector<Student>& student_list, const Student& studentToDelete) {
    auto it = std::remove_if(student_list.begin(), student_list.end(),
        [&studentToDelete](const Student& elem) {
            return elem == studentToDelete;
        });

    if (it != student_list.end()) {
        student_list.erase(it, student_list.end());
        return true;
    }

    return false;
}

bool does_already_exist(const Student student, std::ifstream& ifile) {
    ifile.open("list.txt");
    if (!ifile.is_open()) {
        std::cout << "Can not open the file\n";
        return false;
    }
    std::string line{};
    std::stringstream ss{ line };
    std::string name, surname, group;
    int age;
    while (!ifile.eof()) {
        ifile >> name >> surname >> group >> age;
        if (name == student.get_name() && surname == student.get_surname() && group == student.get_group() && age == student.get_age()) {
            ifile.close();
            return true;
        }
    }

    ifile.close();
    return false;
}
void add_student(std::ofstream& ofile, std::ifstream& ifile) {
    Student student;
    input_data_about_student(student);
    if (!does_already_exist(student, ifile)) {
        ofile << student;
        std::cout << "=========================================\n";
        std::cout << "Student [ " << student.get_surname() << " " << student.get_name() << " ]" << " was added to " << student.get_group() << std::endl;
        std::cout << "=========================================\n";
    }
    else {
        std::cout << "=========================================\n";
        std::cout << "Student [ " << student.get_surname() << " " << student.get_name() << " ]" << " is already exists in the list\n";
        std::cout << "=========================================\n";
    }
}

void rewrite_data_to_file(std::vector<Student> student_list, std::ofstream& ofile) {
    ofile.open("list.txt");
    if (!ofile.is_open()) {
        std::cout << "Can not open the file\n";
        return;
    }

    for (auto& elem : student_list) {
        ofile << elem;
    }
    ofile.close();
}

bool does_group_exist(std::vector<Student>& student_list, std::ifstream& ifile, std::string group_name) {
    student_list = get_student_list(ifile);
    for (auto& student : student_list) {
        if (student.get_group() == group_name)
            return true;
    }
    return false;
}

void launch_students_menu() {
    do {
        show_students_menu();
        std::cin >> user_input;
        std::stringstream ss{ user_input };
        if (!(ss >> is_integer) || is_integer <1 || is_integer >NUMBER_OF_OPTIONS_STUDENTS_MENU) {
            std::cout << "You can only choose 1 - 2\n";
            continue;
        }
        switch (Students_menu(is_integer))
        {
        case Students_menu::Show:
            ifile.open("list.txt");
            if (!ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            student_list = get_student_list(ifile);
            ifile.clear();
            ifile.seekg(0, std::ios::beg);
            ifile.close();
            if (!student_list.empty())
                show_students(student_list);
            else
                std::cout << "The list is empty\n";
            break;
        case Students_menu::Add:
            ofile.open("list.txt", std::ios::app);
            if (!ofile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            add_student(ofile, ifile);
            ofile.close();
            break;
        case Students_menu::Find:
            std::cout << "Enter student's surname to search\n";
            std::cin >> surname;
            if (find_student(student_list, surname))
                break;
            else
                std::cout << "Student [ " << surname << " ] " << " was not found\n";
            break;
        case Students_menu::Delete:
            std::cout << "Enter information about student to delete\n";
            input_data_about_student(student);
            if (delete_student(student_list, student)) {
                rewrite_data_to_file(student_list, ofile);
                std::cout << "Student [ " << student.get_surname() << " ] was deleted from the list\n";
            }
            else
                std::cout << "Student [ " << student.get_surname() << " ] " << " was not found\n";
            break;
        case Students_menu::Group:
            std::cout << "Enter name of the group: ";
            std::cin >> group;
            ifile.open("list.txt");
            if (!ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            if (does_group_exist(student_list, ifile, group)) {
                show_students(student_list, group);
            }
            else {
                std::cout << "No one studies in group " << group << std::endl;
            }
            ifile.close();
        default:
            break;
        }
    } while (is_integer != NUMBER_OF_OPTIONS_STUDENTS_MENU);
}

int main() {
    do{
        show_main_menu();
        std::cin >> user_input;
        std::stringstream ss{user_input};
        if (!(ss >> is_integer) || is_integer <1 || is_integer >NUMBER_OF_OPTIONS_MAIN_MENU) {
            std::cout << "You can only choose 1 - 3\n";
            continue;
        }
        switch (Main_menu(is_integer)){
        case Main_menu::Students:
            launch_students_menu();
            break;
        case Main_menu::Teachers:
            break;
        default:
            break;
        }
    } while (is_integer != NUMBER_OF_OPTIONS_MAIN_MENU);
}