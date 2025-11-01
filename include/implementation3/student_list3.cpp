#include "student_list3.h"

student_list3_t::student_list3_t(const std::vector<std::string>& csv) {
    for (auto& row: csv) {
        auto* student = new student_t(row);
        m_students.push(student);

        std::string group = student->get_group();
        m_map_group[group].push(student);
    }
}

std::pair<std::string, size_t> student_list3_t::get_largest_group() {
    std::pair<std::string, size_t> largest = {"", 0};

    for (auto& [group_name, queue]: m_map_group) {
        size_t curr_size = queue.size();
        if (curr_size > largest.second) {
            largest.first = group_name;
            largest.second = curr_size;
        }
    }
    return largest;
}

void student_list3_t::change_group_by_email(const std::string& email, const std::string& new_group) {
    size_t size = m_students.size();
    for (int i = 0; i < size; ++i) {
        student_t* curr_student = m_students.front();
        m_students.pop();

        if (curr_student->get_email() == email) {
            std::string old_group = curr_student->get_group();
            curr_student->set_group(new_group);
            m_map_group[new_group].push(curr_student);

            size_t old_group_size = m_map_group[old_group].size();
            for (int j = 0; j < old_group_size; ++j) {
                student_t* curr = m_map_group[old_group].front();
                m_map_group[old_group].pop();
                if (curr->get_email() == email) {
                    break;
                }
                m_map_group[old_group].push(curr);
            }
        }
        m_students.push(curr_student);
    }
}

std::pair<std::string, float> student_list3_t::get_largest_rate_group() {
    std::pair<std::string, float> largest = {"", 0};

    for (auto& [group_name, queue]: m_map_group) {
        size_t group_size = queue.size();
        float sum = 0;
        for (int i = 0; i < group_size; ++i) {
            student_t* curr_student = queue.front();
            sum += curr_student->get_rating();
            queue.push(curr_student);
        }
        sum /= group_size;
        if (sum > largest.second) {
            largest.first = group_name;
            largest.second = sum;
        }
    }
    return largest;
}

student_list3_t::~student_list3_t() {
    size_t size = m_students.size();
    for (int i = 0; i < size; ++i) {
        delete m_students.front();
        m_students.pop();
    }
    m_map_group.clear();
}