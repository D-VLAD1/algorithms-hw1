#include <sstream>

#include "student.h"


student_t::student_t(): m_name("None"), m_surname("None"), m_email("None"), m_birth_year(0),
                        m_birth_month(0), m_birth_day(0), m_group("None"), m_rating(.0), m_phone_number("None") {}

student_t::student_t(const std::string& csv_row) {
    std::vector<std::string> split_data;
    std::string token;
    std::istringstream iss(csv_row);

    while (std::getline(iss, token, ',')) {
        split_data.push_back(token);
    }

    m_name = split_data[0];
    m_surname = split_data[1];
    m_email = split_data[2];
    m_birth_year = std::stoi(split_data[3]);
    m_birth_month = std::stoi(split_data[4]);
    m_birth_day = std::stoi(split_data[5]);
    m_group = split_data[6];
    m_rating = std::stof(split_data[7]);
    m_phone_number = split_data[8];
}

std::string student_t::get_group() const {
    return m_group;
}

std::string student_t::get_email() const {
    return m_email;
}

void student_t::set_group(const std::string& new_group) {
    m_group = new_group;
}

float student_t::get_rating() const {
    return m_rating;
}

std::string student_t::get_name() const {
    return m_name;
}

std::string student_t::get_surname() const {
    return m_surname;
}

std::string student_t::to_string() {
    return m_name + "," +
           m_surname + "," +
           m_email + "," +
           std::to_string(m_birth_year) + "," +
           std::to_string(m_birth_month) + "," +
           std::to_string(m_birth_day) + "," +
           m_group + "," +
           std::to_string(m_rating) + "," +
           m_phone_number;
}