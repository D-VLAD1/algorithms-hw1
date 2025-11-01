#ifndef ALGORITHMS_HW1_STUDENT_LIST3_H
#define ALGORITHMS_HW1_STUDENT_LIST3_H


#include <map>
#include <queue>
#include <vector>

#include "student/student.h"

class student_list3_t {
private:
    std::queue<student_t*> m_students;
    std::map<std::string, std::queue<student_t*>> m_map_group;


public:
    explicit student_list3_t(const std::vector<std::string>& csv);

    std::pair<std::string, size_t> get_largest_group();
    void change_group_by_email(const std::string& email, const std::string& new_group);
    std::pair<std::string, float> get_largest_rate_group();

    ~student_list3_t();
};



#endif //ALGORITHMS_HW1_STUDENT_LIST3_H