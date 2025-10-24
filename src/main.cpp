#include <fstream>
#include <iostream>

#include "student.hpp"
#include "student_list.hpp"

#define DATA_FILENAME "../data/students.csv"

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

    std::vector<student_t> list = student_list.get_students();

    return 0;
}