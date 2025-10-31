#ifndef ALGORITHMS_HW1_STUDENT_LIST_H
#define ALGORITHMS_HW1_STUDENT_LIST_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "../student/student.h"

class node_t {
private:
    node_t* left;
    node_t* right;
    student_t* student;

public:
    node_t(node_t* left, node_t* right, student_t* student)
    : left(left), right(right), student(student) {}

    void set_left(node_t* left) {
        this->left = left;
    }

    void set_right(node_t* right) {
        this->right = right;
    }

    node_t* get_left() const {
        return left;
    }

    node_t* get_right() const {
        return right;
    }

    student_t* get_student() const {
        return student;
    }
};

class student_list_t {
private:
    node_t* m_students = nullptr;

    std::unordered_map<std::string, std::vector<student_t*>> m_hash_group;
    std::unordered_map<std::string, student_t*> m_hash_emails;

public:
    explicit student_list_t(const std::vector<std::string>& csv);

    std::pair<std::string, int> get_largest_group();
    void change_group_by_email(const std::string& email, const std::string& new_group);
    std::pair<std::string, float> get_largest_rate_group();

    void sort_by_name_surname_to_csv(const std::string &filename, bool write_csv);

    ~student_list_t();
};


#endif //ALGORITHMS_HW1_STUDENT_LIST_H