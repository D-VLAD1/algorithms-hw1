#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

#include "student/student.h"
#include "implementation1/student_list.h"
#include "implementation2/student_list2.h"

#define DATA_FILENAME "../data/students.csv"
#define SORTED_STUDENTS_FILENAME "../data/sorted_students.csv"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution dist(0, 99);


std::vector<std::string> read_csv(const std::string& filename, int data_amount) {
    std::vector<std::string> output;
    std::fstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    std::getline(file, line);

    int i = 0;
    while (std::getline(file, line) && i < data_amount) {
        output.push_back(line);
        ++i;
    }

    file.close();
    return output;
}

template<typename StudentListT>
std::pair<std::vector<StudentListT*>, std::vector<std::string>> generate_student_list() {
    std::vector<StudentListT*> data = {};
    std::vector<std::string> csv_100000;
    for (auto& amount: {10, 100, 1000, 10000, 100000}) {
        std::vector<std::string> csv = read_csv(DATA_FILENAME, amount);
        auto* student_list = new StudentListT(csv);
        data.push_back(student_list);
        if (amount == 100000) {
            csv_100000 = csv;
        }
    }

    return {data, csv_100000};
}

template<typename StudentListT>
void launch_bench(std::vector<StudentListT*> data) {
    std::cout << "Launch of iterations through data (realization 1)\n" << std::endl;
    int len = 10;
    for (auto* student_list: data) {
        std::cout << "Start test with amount of elements: " << len << std::endl;
        auto start = std::chrono::steady_clock::now();
        int iters = 0;
        while (true) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
            if (elapsed >= 10) {
                break;
            }

            int num = dist(gen);

            if (0 <= num && num <= 99) {
                std::pair<std::string, int> largest = student_list->get_largest_group();
            } else if (100 <= num && num <= 101) {
                student_list->change_group_by_email("ostap.korol@student.org", "DHS-92");
            } else {
                std::pair<std::string, int> rate = student_list->get_largest_rate_group();
            }
            ++iters;
        }
        std::cout << "Iterations within 10 seconds(with A:B:C function distribution): " << iters << std::endl;
        len *= 10;
    }
}

void launch_sort_bench(const std::vector<std::string>& csv_100000, student_list_t* list) {
    std::cout << "\n\nLaunch sort functions on 100000 samples" << std::endl;

    auto sort_start = std::chrono::steady_clock::now();
    list->sort_by_name_surname_to_csv(SORTED_STUDENTS_FILENAME, false);
    auto end = std::chrono::steady_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(end - sort_start);

    std::cout << "My sort function: " << duration.count() << " microseconds" << std::endl;

    std::vector<student_t> vec;
    for (const auto& student: csv_100000) {
        vec.push_back(student_t(student));
    }

    auto builtin_sort_start = std::chrono::steady_clock::now();
    std::sort(vec.begin(), vec.end(),
              [](const student_t& a, const student_t& b) {
                  if (a.get_name() != b.get_name()) return a.get_name() < b.get_name();
                  return a.get_surname() < b.get_surname();
              });

    auto builtin_end = std::chrono::steady_clock::now();
    auto builtin_duration = duration_cast<std::chrono::microseconds>(builtin_end - builtin_sort_start);
    std::cout << "Built-in sort function: " << builtin_duration.count() << " microseconds" << std::endl;
}


int main() {
    auto [data, csv1_100000] = generate_student_list<student_list_t>();
    launch_bench(data);

    auto [data2, _] = generate_student_list<student_list2_t>();
    launch_bench(data2);

    launch_sort_bench(csv1_100000, data[4]);

    return 0;
}