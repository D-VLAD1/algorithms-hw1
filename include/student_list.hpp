#ifndef ALGORITHMS_HW1_STUDENT_LIST_H
#define ALGORITHMS_HW1_STUDENT_LIST_H

#include <vector>
#include <string>

#include "student.hpp"

class student_list_t {
private:
    std::vector<student_t> students;

public:
    explicit student_list_t(const std::vector<std::string>& csv);

    std::vector<student_t> get_students();
};


#endif //ALGORITHMS_HW1_STUDENT_LIST_H