#include "Teacher.hpp"

Teacher::Teacher(){
    init();
}

Teacher::Teacher(std::string name, std::string surname, std::string subject, int age, double salary)
    :Person(name, surname, age), subject{ subject }, salary{ salary } {
}

Teacher::Teacher(const Teacher& source)
:Teacher(source.get_name(), source.get_surname(), source.get_subject(), source.get_age(), source.get_salary()){
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


//void launch_teachers_menu() {
//    std::string user_input{};
//    int is_integer{};
//    std::ifstream ifile;
//    const int NUMBER_OF_OPTIONS_TEACHERS_MENU{ 5 };
//    std::ofstream ofile;
//    std::string surname{}, group{};
//    Teacher teacher{};
//    std::vector<Teacher> teacher_list;
//    const std::string TEACHER_LIST{ "teacher_list" };
//    do {
//        show_teachers_menu();
//        std::cin >> user_input;
//        std::stringstream ss{ user_input };
//        if (!(ss >> is_integer) || is_integer <1 || is_integer >NUMBER_OF_OPTIONS_TEACHERS_MENU) {
//            std::cout << "You can only choose 1 - 5\n";
//            continue;
//        }
//        switch (Teachers_menu(is_integer))
//        {
//        case Teachers_menu::Show:
//            ifile.open(TEACHER_LIST);
//            if (!ifile.is_open()) {
//                std::cout << "Can not open the file\n";
//                return;
//            }
//            teacher_list = get_teacher_list(ifile);
//            ifile.clear();
//            ifile.seekg(0, std::ios::beg);
//            ifile.close();
//            if (!teacher_list.empty())
//                show_list(teacher_list);
//            else
//                std::cout << "The list is empty\n";
//            break;
//        case Teachers_menu::Add:
//            ofile.open(TEACHER_LIST, std::ios::app);
//            if (!ofile.is_open()) {
//                std::cout << "Can not open the file\n";
//                return;
//            }
//            add_teacher(ofile, ifile);
//            ofile.close();
//            break;
//        case Teachers_menu::Find:
//            std::cout << "Enter student's surname to search\n";
//            std::cin >> surname;
//            /*if (find_student(student_list, surname))
//               break;
//            else
//                std::cout << "Student [ " << surname << " ] " << " was not found\n";
//            break;*/
//        case Teachers_menu::Delete:
//            std::cout << "Enter information about teacher to delete\n";
//            //input_data_about_student(student);
//            /*if (delete_student(teacher_list, teacher)) {
//                rewrite_data_to_file(teacher_list, ofile);
//                std::cout << "Student [ " << teacher.get_surname() << " ] was deleted from the list\n";
//            }
//            else
//                std::cout << "Student [ " << teacher.get_surname() << " ] " << " was not found\n";
//            break;*/
//        default:
//            break;
//        }
//    } while (is_integer != NUMBER_OF_OPTIONS_TEACHERS_MENU);
//}

std::vector<Teacher> get_teacher_list(std::ifstream& ifile) {
    std::string line;
    std::string name, surname, group;
    int age;
    std::vector<Teacher> student_list;
    while (std::getline(ifile, line)) {
        std::stringstream ss{ line };
        ss >> name >> surname >> group >> age;
        student_list.push_back({ name, surname, group, age });
    }
    return student_list;
}

std::string Teacher::get_group() const {
    return "";
}

void add_teacher(std::ofstream& ofile, std::ifstream& ifile) {

}

//void input_data_about_teacher(Teacher& teacher) {
//    std::string name, surname, subject, salary, age;
//    int age_int;
//    double salary_double;
//    bool is_correct{ true };
//    do {
//        std::cout << "Enter teacher's name: ";
//        std::cin >> name;
//        if (is_available_input_for_word(name)) {
//            is_correct = true;
//            teacher.set_name(name);
//        }
//        else {
//            std::cout << "Name can contain only letters\n";
//            is_correct = false;
//        }
//    } while (!is_correct);
//
//    do {
//        std::cout << "Enter teacher's surname: ";
//        std::cin >> surname;
//        if (is_available_input_for_word(surname)) {
//            is_correct = true;
//            teacher.set_surname(surname);
//        }
//        else {
//            std::cout << "Surname can contain only letters\n";
//            is_correct = false;
//        }
//    } while (!is_correct);
//
//    do {
//        std::cout << "Enter teacher's subject: ";
//        std::cin >> subject;
//        if (is_available_input_for_word(subject)) {
//            is_correct = true;
//            teacher.set_subject(subject);
//        }
//        else {
//            std::cout << "Subject can contain only letters\n";
//            is_correct = false;
//        }
//    } while (!is_correct);
//
//    do {
//        std::cout << "Enter teacher's salary: ";
//        std::cin >> salary;
//        if (is_available_input_for_salary(salary)) {
//            is_correct = true;
//            std::stringstream ss{ salary };
//            ss >> salary_double;
//            teacher.set_salary(salary_double);
//        }
//        else {
//            std::cout << "Age can contain only numbers\n";
//            is_correct = false;
//        }
//    } while (!is_correct);
//
//    do {
//        std::cout << "Enter teacher's age: ";
//        std::cin >> age;
//        if (is_available_input_for_number(age)) {
//            is_correct = true;
//            std::stringstream ss{ age };
//            ss >> age_int;
//            teacher.set_age(age_int);
//        }
//        else {
//            std::cout << "Age can contain only numbers\n";
//            is_correct = false;
//        }
//    } while (!is_correct);
//}

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
    os << std::setw(10) << this->get_subject() << std::setw(10) << this->get_salary() << std::endl;
}

void Teacher::show_list() const {
    Person::show_list();
    std::cout << *this;
}

void Teacher::init() {
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