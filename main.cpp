#include <iostream>
#include "Student.hpp"
#include <vector>
#include <iomanip>

enum class Choice { Show = 1, Add, Find, Delete };

void menu() {
    std::cout << "Choose the option\n";
    std::cout << "1 - Show table of students\n";
    std::cout << "2 - Add student\n";
    std::cout << "3 - Find student by surname\n";
    std::cout << "4 - Delete student\n";
    std::cout << "5 - Quit\n";
}

void add_student(std::vector<Student>&student_list) {
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
    student_list.push_back(Student{ name, surname, group, age });
    std::cout << "=========================================\n";
    std::cout << "Student [ " << surname << " " << name << " ]" << " was added to " << group << std::endl;
    std::cout << "=========================================\n";
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

int main(){
    std::underlying_type_t<Choice> user_input;
    std::vector<Student> student_list;
    std::string name, surname, group;
    int age;
    do{
        menu();
        std::cin >> user_input;
        switch (Choice(user_input))
        {
        case Choice::Show:
            if (!student_list.empty())
                show_students(student_list);
            else
                std::cout << "The list is empty\n";
            break;
        case Choice::Add:
            add_student(student_list);
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
            if (delete_student(student_list, { name, surname, group, age }))
                std::cout << "Student [ " << surname << " ] was deleted from the list\n";
            else
                std::cout << "Student [ " << surname << " ] " << " was not found\n";
            break;
        default:
            break;
        }
    } while (user_input != 5);
}

