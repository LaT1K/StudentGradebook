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
    std::string user_input{};
    int is_integer{};
    std::ifstream ifile;
    const int NUMBER_OF_OPTIONS_STUDENTS_MENU{ 6 };
    std::ofstream ofile;
    std::string surname{}, group{};
    Student student{};
    std::vector<Student> student_list;
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
                show_list(student_list);
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
                show_list(student_list, group);
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

void show_list(const std::vector<Student>& student_list) {
    std::cout << std::setw(15) << std::left << "Name" << std::setw(15) << "Surname" << std::setw(10) << "Group" << std::setw(3) << "Age\n";
    for (auto& elem : student_list)
        std::cout << elem;
}

void show_list(const std::vector<Student>& student_list, std::string group_name) {
    std::cout << std::setw(15) << std::left << "Name" << std::setw(15) << "Surname" << std::setw(10) << "Group" << std::setw(3) << "Age\n";
    for (auto& student : student_list)
        if (student.get_group() == group_name)
            std::cout << student;
}