#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Student.hpp"
#include "Teacher.hpp"
#include "Functions.hpp"

const int NUMBER_OF_OPTIONS_MAIN_MENU{ 3 };

enum class Main_menu { Students = 1, Teachers };

int main() {
    int is_integer{};
    std::string user_input{};
    do{
        show_main_menu();
        std::cin >> user_input;
        std::stringstream ss{user_input};
        if (!(ss >> is_integer) || is_integer <1 || is_integer >NUMBER_OF_OPTIONS_MAIN_MENU) {
            std::cout << "You can only choose 1 - " << NUMBER_OF_OPTIONS_MAIN_MENU << std::endl;
            continue;
        }
        switch (Main_menu(is_integer)){
        case Main_menu::Students:
            launch_students_menu();
            break;
        case Main_menu::Teachers:
            launch_teachers_menu();
            break;
        default:
            break;
        }
    } while (is_integer != NUMBER_OF_OPTIONS_MAIN_MENU);
}