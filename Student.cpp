#include <iostream>
#include <iomanip>
#include "Student.hpp"


std::string Student::get_group() const {
    return group;
}

void Student::set_group(std::string group) {
    this->group = group;
}

double Student::get_salary() const {
    return 0.0;
}

Student::Student(std::string name, std::string surname, int age, std::string group)
    :Person(name, surname, age), group{ group } {
}

Student::Student(const Student& source)
    :Student(source.get_name(), source.get_surname(), source.get_age(), source.get_group()) {
}

std::vector <std::shared_ptr<Person>> get_student_list(std::ifstream& ifile) {
    std::string line;
    std::string name, surname, group;
    int age;
    std::vector<std::shared_ptr<Person>> student_list;
    while (std::getline(ifile, line)) {
        std::stringstream ss{ line };
        ss >> name >> surname >> age >> group;

        if (ss) {
            std::shared_ptr<Person> temp = std::make_shared<Student>(name, surname, age, group);
            student_list.push_back(temp);
        }
    }

    return student_list;
}

bool does_student_exist(const std::vector<std::shared_ptr<Person>>& student_list, std::string surname) {
    bool x = false;
    for (const auto &elem : student_list) {
        if (elem->get_surname() == surname) {
            std::cout << *elem;
            x = true;
        }
    }
    return x;
}

bool delete_student(std::vector<std::shared_ptr<Person>>& student_list, const Person* studentToDelete) {
    auto it = student_list.begin();
    while (it != student_list.end()) {
        Student* student = dynamic_cast<Student*>(it->get());
        if (student && *student == studentToDelete) {
            student_list.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}


bool does_already_exist(const Person *student, std::ifstream& ifile) {
    ifile.open(STUDENT_LIST);
    if (!ifile.is_open()) {
        std::cout << "Can not open the file\n";
        return false;
    }
    std::string line{};
    std::stringstream ss{ line };
    std::string name, surname, group;
    int age;
    while (!ifile.eof()) {
        ifile >> name >> surname >> age >> group;
        if (name == student->get_name() && surname == student->get_surname() && group == student->get_group() && age == student->get_age()) {
            ifile.close();
            return true;
        }
    }

    ifile.close();
    return false;
}
void add_student(std::ofstream& ofile) {
    std::shared_ptr<Person> student = std::make_shared<Student>();
    student->init();
    ofile << *student;
}

void rewrite_students_to_file(std::vector<std::shared_ptr<Person>> student_list, std::ofstream& ofile) {
    ofile.open(STUDENT_LIST);
    if (!ofile.is_open()) {
        std::cout << "Can not open the file\n";
        return;
    }
    ofile.clear();
    for (auto& elem : student_list) {
        ofile << elem->get_name() << "\t" << elem->get_surname() << "\t" << elem->get_age() << "\t" << elem->get_group() << std::endl;
    }
    ofile.close();
}

bool does_group_exist(std::vector <std::shared_ptr<Person>>& student_list, std::ifstream& ifile, std::string group_name) {
    student_list = get_student_list(ifile);
    for (auto &student : student_list) {
        if (student->get_group() == group_name)
            return true;
    }
    return false;
}



void Student::print(std::ostream& os) const{
    Person::print(os);
    os <<std::setw(10) << this->get_group() << std::endl;
}

void Student::show_list() const {
    Person::show_list();
    std::cout << std::setw(15) << this->get_group() << std::endl;
}

std::string Student::get_subject() const {
    return "";
}

bool Student::operator==(const Person* rhs) const {
    return this->get_name() == rhs->get_name() && this->get_surname() == rhs->get_surname() && this->get_group() == rhs->get_group() && this->get_age() == rhs->get_age();
}

void Student::init() {
    Person::init();
    std::cout << "Enter student's group: ";
    std::cin >> this->group;
    this->set_group(group);
}

void launch_students_menu() {
    std::string user_input{};
    int is_integer{};
    std::ifstream ifile;
    
    std::ofstream ofile;
    std::string surname{}, group{};
    Person *student;
    std::vector<std::shared_ptr<Person>>student_list;
    do {
        show_students_menu();
        std::cin >> user_input;
        std::stringstream ss{ user_input };
        if (!(ss >> is_integer) || is_integer <1 || is_integer >NUMBER_OF_OPTIONS_STUDENTS_MENU) {
            std::cout << "You can only choose 1 - " << NUMBER_OF_OPTIONS_STUDENTS_MENU << std::endl;
            continue;
        }
        switch (Students_menu(is_integer)) {
        case Students_menu::Show:
            ifile.open(STUDENT_LIST);
            ifile.seekg(0);
            if (!ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            student_list = get_student_list(ifile);
            ifile.clear();

            ifile.close();
            if (!student_list.empty()) {
                std::cout << std::setw(15) << std::left << "Name" << std::setw(15) << "Surname" << std::setw(10) << "Age" << std::setw(10) << "Group" << std::endl;
                for (auto& student : student_list)
                    student->show_list();
            }
            else
                std::cout << "The list is empty\n";
            break;
        case Students_menu::Add:
            ofile.open(STUDENT_LIST, std::ios::app);
            ifile.open(STUDENT_LIST);
            if (!ofile.is_open() && !ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            add_student(ofile);
            student_list = get_student_list(ifile);
            ifile.seekg(0, std::ios::beg);
            ofile.close();
            ifile.close();
            break;
        case Students_menu::Find:
            std::cout << "Enter student's surname to search\n";
            std::cin >> surname;
            if (does_student_exist(student_list, surname))
                break;
            else
                std::cout << "Student [ " << surname << " ] " << " was not found\n";
            break;
        case Students_menu::Delete:
            std::cout << "Enter information about student to delete\n";
            ifile.open(STUDENT_LIST);
            if (!ifile.is_open()) {
                std::cout << "Can not open the file!\n";
                return;
            }
            student_list = get_student_list(ifile);
            student = new Student;
            student->init();
            if (delete_student(student_list, student)) {
                rewrite_students_to_file(student_list, ofile);
                std::cout << "Student [ " << student->get_surname() << " ] was deleted from the list\n";
            }
            else
                std::cout << "Student [ " << student->get_surname() << " ] " << " was not found\n";
            delete student;
            ifile.close();
            break;
        case Students_menu::Group:
            std::cout << "Enter name of the group: ";
            std::cin >> group;
            ifile.open(STUDENT_LIST);
            if (!ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            if (does_group_exist(student_list, ifile, group)) {

                for (auto& student : student_list) {
                    if (student->get_group() == group)
                        std::cout << *student;
                }
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