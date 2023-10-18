#include "Teacher.hpp"


Teacher::Teacher(std::string name, std::string surname, int age, std::string subject, double salary)
    :Person(name, surname, age), subject{ subject }, salary{ salary } {
}

Teacher::Teacher(const Teacher& source)
:Teacher(source.get_name(), source.get_surname(), source.get_age(), source.get_subject(), source.get_salary()){
}

std::string Teacher::get_subject() const {
	return this->subject;
}

double Teacher::get_salary() const {
	return this->salary;
}

void Teacher::set_subject(std::string subject) {
    this->subject = subject;
}

void Teacher::set_salary(double salary) {
    this->salary = salary;
}

bool does_teacher_exist(const std::vector<std::shared_ptr<Person>>& teacher_list, std::string surname) {
    bool x = false;
    for (const auto& elem : teacher_list) {
        if (elem->get_surname() == surname) {
            std::cout << *elem;
            x = true;
        }
    }
    return x;
}

bool Teacher::operator==(const Person* rhs) const{
    return this->get_name() == rhs->get_name() && this->get_surname() == rhs->get_surname() && this->get_age() == rhs->get_age() && this->get_subject() == rhs->get_subject() && this->get_salary() == rhs->get_salary();
}

bool delete_teacher(std::vector<std::shared_ptr<Person>>& teacher_list, const Person* teacherToDelete) {
    auto it = teacher_list.begin();
    while (it != teacher_list.end()) {
        Teacher* teacher = dynamic_cast<Teacher*>(it->get());
        if (teacher && *teacher == teacherToDelete) {
            teacher_list.erase(it);
            delete teacherToDelete;
            return true;
        }
        ++it;
    }
    delete teacherToDelete;
    return false;
}

void rewrite_teachers_to_file(std::vector<std::shared_ptr<Person>> teacher_list, std::ofstream& ofile) {
    ofile.open(TEACHER_LIST);
    if (!ofile.is_open()) {
        std::cout << "Can not open the file\n";
        return;
    }
    ofile.clear();
    for (auto& elem : teacher_list) {
        ofile << elem->get_name() << "\t" << elem->get_surname() << "\t" << elem->get_age() << "\t" << elem->get_subject() << "\t" << elem->get_salary() << std::endl;
    }
    ofile.close();
}

void launch_teachers_menu() {
    std::string user_input{};
    int is_integer{};
    std::ifstream ifile;
    std::ofstream ofile;
    std::string surname{}, group{};
    Teacher* teacher;
    std::vector<std::shared_ptr<Person>> teacher_list;

    do {
        show_teachers_menu();
        std::cin >> user_input;
        std::stringstream ss{ user_input };
        if (!(ss >> is_integer) || is_integer <1 || is_integer >NUMBER_OF_OPTIONS_TEACHERS_MENU) {
            std::cout << "You can only choose 1 - 5\n";
            continue;
        }
        switch (Teachers_menu(is_integer)) {
        case Teachers_menu::Show:
            ifile.open(TEACHER_LIST);
            if (!ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            teacher_list = get_teacher_list(ifile);
            ifile.clear();
            /*ifile.seekg(0, std::ios::beg);*/
            ifile.close();
            if (!teacher_list.empty()) {
                std::cout << std::setw(15) << std::left << "Name" << std::setw(15) << "Surname" << std::setw(10) << "Age" << std::setw(15) << "Subject" << std::setw(15) << "Salary" << std::endl;
                for (auto& teacher : teacher_list)
                    teacher->show_list();
            }
            else
                std::cout << "The list is empty\n";
            break;
        case Teachers_menu::Add:
            ofile.open(TEACHER_LIST, std::ios::app);
            ifile.open(TEACHER_LIST);
            if (!ofile.is_open() && !ifile.is_open()) {
                std::cout << "Can not open the file\n";
                return;
            }
            add_teacher(ofile);
            teacher_list = get_teacher_list(ifile);
            ifile.seekg(0, std::ios::beg);
            ofile.close();
            ifile.close();
            break;
        case Teachers_menu::Find:
            std::cout << "Enter teacher's surname to search\n";
            std::cin >> surname;
            if (does_teacher_exist(teacher_list, surname))
               break;
            else
                std::cout << "Teacher [ " << surname << " ] " << " was not found\n";
            break;
        case Teachers_menu::Delete:
            std::cout << "Enter information about a teacher to delete\n";
            teacher = new Teacher;
            teacher->init();
            if (delete_teacher(teacher_list, teacher)) {
                rewrite_teachers_to_file(teacher_list, ofile);
                std::cout << "Teacher [ " << teacher->get_surname() << " ] was deleted from the list\n";
            }
            else
                std::cout << "Student [ " << teacher->get_surname() << " ] was not found\n";
            delete teacher;
        default:
            break;
        }
    } while (is_integer != NUMBER_OF_OPTIONS_TEACHERS_MENU);
}


std::vector<std::shared_ptr<Person>> get_teacher_list(std::ifstream& ifile) {
    std::string line;
    std::string name, surname, subject;
    int age;
    double salary;
    std::vector<std::shared_ptr<Person>> teacher_list;
    while (std::getline(ifile, line)) {
        std::stringstream ss{ line };
        ss >> name >> surname >> age >> subject >> salary;

        if (ss) {
            std::shared_ptr<Person> temp = std::make_shared<Teacher>(name, surname, age, subject, salary);
            teacher_list.push_back(temp);
        }
    }
    return teacher_list;
}





std::string Teacher::get_group() const {
    return "";
}

void add_teacher(std::ofstream& ofile) {
    std::shared_ptr<Person> teacher = std::make_shared<Teacher>();
    teacher->init();
    ofile << *teacher;
}

bool does_already_exist(const Teacher teacher, std::ifstream& ifile) {
    ifile.open("list.txt");
    if (!ifile.is_open()) {
        std::cout << "Can not open the file\n";
        return false;
    }
    std::string line{};
    std::stringstream ss{ line };
    std::string name, surname, subject;
    double salary;
    int age;
    while (!ifile.eof()) {
        ifile >> name >> surname >> subject >> salary >> age;;
        if (name == teacher.get_name() && surname == teacher.get_surname() && subject == teacher.get_subject() && salary == teacher.get_salary()) {
            ifile.close();
            return true;
        }
    }

    ifile.close();
    return false;
}

void Teacher::print(std::ostream& os) const{
    Person::print(os);
    os << std::setw(10) << this->get_subject() << std::setw(10) << this->get_salary() << std::endl;
}

void Teacher::show_list() const {
    Person::show_list();
    std::cout << std::setw(15) << this->get_subject() << std::setw(15) << this->get_salary() << std::endl;
}

void Teacher::init() {
    Person::init();
    bool is_correct{ false };
    std::string is_salary;

    do {
        std::cout << "Enter teacher's subject: ";
        std::cin >> this->subject;
        if (is_available_input_for_word(subject)) {
            is_correct = true;
            this->set_subject(subject);
        }
        else {
            std::cout << "Subject can contain only letters\n";
            is_correct = false;
        }
    } while (!is_correct);

    do {
        std::cout << "Enter teacher's salary: ";
        std::cin >> is_salary;
        if (is_available_input_for_salary(is_salary)) {
            is_correct = true;
            std::stringstream ss{ is_salary };
            ss >> this->salary;
            this->set_salary(salary);
        }
        else {
            std::cout << "Salary can contain only numbers\n";
            is_correct = false;
        }
    } while (!is_correct);
}

