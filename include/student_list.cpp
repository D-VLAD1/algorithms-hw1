#include "student_list.hpp"

student_list_t::student_list_t(const std::vector<std::string>& csv) {
    size_t size = csv.size();
    for (size_t i = 0; i < size; ++i) {
        std::string curr_str = csv[i];
        student_t student{curr_str};
        students.emplace_back(student);
    }
}

std::vector<student_t> student_list_t::get_students() {
    return students;
}