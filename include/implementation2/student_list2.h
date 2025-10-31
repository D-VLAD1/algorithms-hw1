#ifndef ALGORITHMS_HW1_STUDENT_LIST2_H
#define ALGORITHMS_HW1_STUDENT_LIST2_H

#include <vector>

#include "../student/student.h"

class student_list2_t {
private:
    std::vector<student_t*> m_students;
    std::vector<std::pair<std::string, std::vector<student_t*>>> m_vec_group;

public:
    explicit student_list2_t(const std::vector<std::string>& csv);

    std::pair<std::string, int> get_largest_group();
    void change_group_by_email(const std::string& email, const std::string& new_group);
    std::pair<std::string, float> get_largest_rate_group();

    ~student_list2_t();
};


#endif //ALGORITHMS_HW1_STUDENT_LIST2_H