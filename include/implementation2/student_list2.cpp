#include "student_list2.h"


student_list2_t::student_list2_t(const std::vector<std::string>& csv) {
    for (auto& row: csv) {
        student_t* student = new student_t(row);
        m_students.push_back(student);

        std::string group = student->get_group();
        bool pushed = false;

        for (auto& pair: m_vec_group) {
            if (pair.first == group) {
                pair.second.push_back(student);
                pushed = true;
            }
        }
        if (!pushed) {
            std::pair<std::string, std::vector<student_t*>> new_pair{group, {student}};
            m_vec_group.push_back(new_pair);
        }
    }
}

std::pair<std::string, size_t> student_list2_t::get_largest_group() {
    std::pair<std::string, size_t> largest{"", 0};
    for (auto& group: m_vec_group) {
        size_t group_size = group.second.size();
        if (group_size > largest.second) {
            largest.first = group.first;
            largest.second = group_size;
        }
    }
    return largest;
}

void student_list2_t::change_group_by_email(const std::string& email, const std::string& new_group) {
    for (auto* student: m_students) {
        if (student->get_email() == email) {
            std::string old_group = student->get_group();
            student->set_group(new_group);

            for (auto& group: m_vec_group) {
                if (group.first == old_group) {
                    std::erase_if(group.second,
                        [&](const student_t* s) { return s->get_email() == email; }
                    );
                }

                if (group.first == new_group) {
                    group.second.push_back(student);
                }
            }
            break;
        }
    }
}

std::pair<std::string, float> student_list2_t::get_largest_rate_group() {
    std::pair<std::string, float> largest{"", 0};
    for (auto& group: m_vec_group) {
        float rate = 0;
        for (student_t* student : m_students) {
            rate += student->get_rating();
        }
        rate /= m_students.size();

        if (rate > largest.second) {
            largest.first = group.first;
            largest.second = rate;
        }
    }
    return largest;
}


student_list2_t::~student_list2_t() {
    for (auto& student: m_students) {
        delete student;
    }
    m_vec_group.clear();
    m_students.clear();
}