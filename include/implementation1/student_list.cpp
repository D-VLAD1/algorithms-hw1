#include "student_list.h"

#include <fstream>


student_list_t::student_list_t(const std::vector<std::string>& csv) {
    size_t size = csv.size();
    for (size_t i = 0; i < size; ++i) {
        const std::string& curr_str = csv[i];
        auto* student = new student_t(curr_str);

        if (!m_students) {
            m_students = new node_t(nullptr, nullptr, student);
        } else {
            node_t* curr = m_students;
            while (curr != nullptr) {
                std::string name = student->get_name();
                std::string curr_name = curr->get_student()->get_name();

                if (name < curr_name) {
                    if (curr->get_left() == nullptr) {
                        curr->set_left(new node_t(nullptr, nullptr, student));
                        break;
                    }
                    curr = curr->get_left();

                } else if (name > curr_name) {
                    if (curr->get_right() == nullptr) {
                        curr->set_right(new node_t(nullptr, nullptr, student));
                        break;
                    }
                    curr = curr->get_right();
                } else {
                    std::string surname = student->get_surname();
                    std::string curr_surname = curr->get_student()->get_surname();

                    if (surname < curr_surname) {
                        if (curr->get_left() == nullptr) {
                            curr->set_left(new node_t(nullptr, nullptr, student));
                            break;
                        }
                    } else if (surname > curr_surname) {
                        if (curr->get_right() == nullptr) {
                            curr->set_right(new node_t(nullptr, nullptr, student));
                            break;
                        }
                    }
                    break;
                }
            }
        }

        std::string group = student->get_group();
        std::string email = student->get_email();
        m_hash_group[group].insert(student);
        m_hash_emails[email] = student;
    }
}

std::pair<std::string, size_t> student_list_t::get_largest_group() {
    std::pair<std::string, size_t> max_group = {"", 0};

    for (auto& [group, students] : m_hash_group) {
        size_t group_size = students.size();
        if (group_size > max_group.second) {
            max_group.first = group;
            max_group.second = group_size;
        }
    }

    return max_group;
}

void student_list_t::change_group_by_email(const std::string& email, const std::string& new_group) {
    student_t* student = m_hash_emails[email];

    std::string prev_group = student->get_group();
    std::set<student_t*>& prev_group_members = m_hash_group[prev_group];
    prev_group_members.erase(student);

    student->set_group(new_group);
    m_hash_group[new_group].insert(student);
}

std::pair<std::string, float> student_list_t::get_largest_rate_group() {
    std::pair<std::string, float> max_group = {"", 0};

    for (auto& [group_name, students] : m_hash_group) {
        float curr_sum = 0;
        for (student_t* student : students) {
            curr_sum += student->get_rating();
        }
        curr_sum /= students.size();

        if (curr_sum > max_group.second) {
            max_group.first = group_name;
            max_group.second = curr_sum;
        }
    }

    return max_group;
}

std::vector<student_t*> tree_traversal(const node_t* node) {
    if (node == nullptr) {
        return {};
    }

    std::vector<student_t*> left_output = tree_traversal(node->get_left());
    student_t* student = node->get_student();
    std::vector<student_t*> right_output = tree_traversal(node->get_right());

    left_output.push_back(student);
    left_output.insert(left_output.end(), right_output.begin(), right_output.end());

    return left_output;
}

void student_list_t::sort_by_name_surname_to_csv(const std::string& filename, bool write_csv) {
    std::vector<student_t*> traversal = tree_traversal(m_students);

    if (write_csv) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Cannot write the file");
        }

        for (auto& student : traversal) {
            std::string csv_row = student->to_string();
            file << csv_row + "\n";
        }
        file.close();
    }
}

void delete_tree(node_t* node) {
    if (node == nullptr)
        return;

    delete_tree(node->get_left());
    delete_tree(node->get_right());

    delete node->get_student();
    delete node;
}

student_list_t::~student_list_t() {
    delete_tree(m_students);
    m_hash_group.clear();
    m_hash_emails.clear();
}