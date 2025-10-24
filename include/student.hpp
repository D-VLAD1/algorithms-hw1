#ifndef ALGORITHMS_HW1_STUDENT_H
#define ALGORITHMS_HW1_STUDENT_H

#include <ranges>
#include <vector>

class student_t {
private:
    std::string m_name; // ім'я українською
    std::string m_surname; // прізвище українською
    std::string m_email; // [a-z.]*@student.org
    int m_birth_year; // 1950..2010
    int m_birth_month; // 1..12
    int m_birth_day; // 1 -> Number of days in m_birth_month
    std::string m_group; // [A-Z][A-Z][A-Z]-[0-9][0-9]
    float m_rating; // 0..100
    std::string m_phone_number; // 38(0xx)xx-xx-xxx

public:
    explicit student_t(const std::string& csv_row);
};

#endif