#include <sstream>

#include "student.hpp"


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