#include <fstream>
#include <iostream>

#include "student.hpp"
#include "student_list.hpp"

#define DATA_FILENAME "../data/students.csv"
#define SORTED_STUDENTS_FILENAME "../data/sorted_students.csv"

std::vector<std::string> read_csv(const std::string& filename) {
    std::vector<std::string> output;
    std::fstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        output.push_back(line);
    }

    file.close();
    return output;
}


int main() {
    std::vector<std::string> csv = read_csv(DATA_FILENAME);
    student_list_t student_list{csv};

    std::pair<std::string, int> largest = student_list.get_largest_group();
    student_list.change_group_by_email("ostap.korol@student.org", "DHS-92");
    std::pair<std::string, int> rate = student_list.get_largest_rate_group();
    student_list.sort_by_name_surname_to_csv(SORTED_STUDENTS_FILENAME);

    return 0;
}