#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Student.hpp"
#include "Teacher.hpp"

void show_main_menu();
void show_students_menu();
void show_teachers_menu();
bool is_available_input_for_word(std::string user_word);
bool is_available_input_for_number(std::string user_number);