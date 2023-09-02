#include "Functions.hpp"

void show_main_menu() {
    std::cout << "Who do you want to work with?\n";
    std::cout << "1 - Students\n";
    std::cout << "2 - Teachers\n";
    std::cout << "3 - Quit\n";
}
void show_students_menu() {
    std::cout << "Choose the option\n";
    std::cout << "1 - Show table of students\n";
    std::cout << "2 - Add student\n";
    std::cout << "3 - Find student by surname\n";
    std::cout << "4 - Delete student\n";
    std::cout << "5 - Show students from given group\n";
    std::cout << "6 - Quit\n";
}

void show_teachers_menu() {
    std::cout << "Choose the option\n";
    std::cout << "1 - Show table of teachers\n";
    std::cout << "2 - Add teacher\n";
    std::cout << "3 - Find teacher by surname\n";
    std::cout << "4 - Delete teacher\n";
    std::cout << "5 - Quit\n";
}

bool is_available_input_for_word(std::string user_word) {
    for (char c : user_word)
        if (!(std::isalpha(c)))
            return false;
    return true;
}

bool is_available_input_for_number(std::string user_number) {
    int is_digit{};
    std::stringstream ss{ user_number };
    if (ss >> is_digit)
        return true;
    else
        return false;
}

