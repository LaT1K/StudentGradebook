#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "Student.hpp"

enum class Choice { Show = 1, Add, Find, Delete };

void menu() {
    std::cout << "Choose the option\n";
    std::cout << "1 - Show table of students\n";
    std::cout << "2 - Add student\n";
    std::cout << "3 - Find student by surname\n";
    std::cout << "4 - Delete student\n";
    std::cout << "5 - Quit\n";
}

void show_students(const std::vector<Student>& student_list) {
    std::cout << std::setw(15) << std::left<< "Name" << std::setw(15) << "Surname" << std::setw(10) << "Group" << std::setw(3) << "Age\n";
    for (auto &elem : student_list)
        std::cout << elem;
}

bool find_student(const std::vector<Student> &student_list, std::string surname){
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

std::vector<Student> get_student_list(std::ifstream &ifile) {
    std::string line;
    std::string name, surname, group;
    int age;
    std::vector<Student> student_list;
    while (std::getline(ifile, line)){
        std::stringstream ss{ line };
        ss >> name >> surname >> group >> age;
        student_list.push_back({ name, surname, group, age });
    }
    return student_list;
}

bool is_already_exist(const Student student, std::ifstream& ifile) {
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
void add_student(std::ofstream &ofile, std::ifstream &ifile) {
    std::string name, surname, group;
    int age;
    std::cout << "Enter student's name: ";
    std::cin >> name;
    std::cout << "Enter student's surname: ";
    std::cin >> surname;
    std::cout << "Enter student's group: ";
    std::cin >> group;
    std::cout << "Enter student's age: ";
    std::cin >> age;
    if (!is_already_exist(Student{ name, surname, group, age }, ifile)) {
    ofile << Student{ name, surname, group, age };
    std::cout << "=========================================\n";
    std::cout << "Student [ " << surname << " " << name << " ]" << " was added to " << group << std::endl;
    std::cout << "=========================================\n";
    }
    else {
        std::cout << "=========================================\n";
        std::cout << "Student [ " << surname << " " << name << " ]" << " is already exists in the list\n";
        std::cout << "=========================================\n";
    }
}

void rewrite_data_to_file(std::vector<Student> student_list, std::ofstream &ofile) {
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

int main() {
    std::underlying_type_t<Choice> user_input;
    std::vector<Student> student_list;
    std::string name, surname, group;
    int age;
    std::ifstream ifile;
    std::ofstream ofile;;
    do{
        menu();
        std::cin >> user_input;
        switch (Choice(user_input))
        {
        case Choice::Show:
            ifile.open("list.txt");
            if (!ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return 1;
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
        case Choice::Add:
            ofile.open("list.txt", std::ios::app);
            if (!ofile.is_open()) {
                std::cout << "Can not open the file\n";
                return 1;
            }
            add_student(ofile, ifile);
            ofile.close();
            break;
        case Choice::Find:
            std::cout << "Enter student's surname to search\n";
            std::cin >> surname;
            if (find_student(student_list, surname))
                break;
            else
                std::cout << "Student [ " << surname << " ] " << " was not found\n";
            break;
        case Choice::Delete:
            
            std::cout << "Enter information about student to delete\n";
            std::cout << "Enter student's name: ";
            std::cin >> name;
            std::cout << "Enter student's surname: ";
            std::cin >> surname;
            std::cout << "Enter student's group: ";
            std::cin >> group;
            std::cout << "Enter student's age: ";
            std::cin >> age;
            if (delete_student(student_list, { name, surname, group, age })) {
                rewrite_data_to_file(student_list, ofile);
                std::cout << "Student [ " << surname << " ] was deleted from the list\n";
            }
            else
                std::cout << "Student [ " << surname << " ] " << " was not found\n";
            break;
        default:
            break;
        }
    } while (user_input != 5);
}