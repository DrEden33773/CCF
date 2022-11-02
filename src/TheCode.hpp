/**
 * @file TheCode.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 202209-1
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <iostream>
#include <vector>

class TheCode {
    // 20 + 16
    static constexpr int MAX_TASK_NUM = 20 + 16;

    int task_num  = 0;
    int magic_num = 0;

    // effective index starts from 1
    std::vector<int> a_arr = std::vector<int>(MAX_TASK_NUM, 0);
    // effective index starts from 0
    std::vector<int> c_arr = std::vector<int>(MAX_TASK_NUM, 0);
    // effective index starts from 1
    std::vector<int> b_arr = std::vector<int>(MAX_TASK_NUM, 0);

public:
    void input() {
        std::cin >> task_num >> magic_num;
        for (int i = 1; i <= task_num; ++i) {
            int curr_option = 0;
            std::cin >> curr_option;
            a_arr[i] = curr_option;
        }
    }
    void process() {
        // get c_arr
        c_arr[0] = 1;
        for (int i = 1; i <= task_num; ++i) {
            c_arr[i] = c_arr[i - 1] * a_arr[i];
        }
        // start to opt
        b_arr[1] = (magic_num % c_arr[1]) / c_arr[0];
        for (int i = 2; i <= task_num; ++i) {
            int&& m_mod_ci     = magic_num % c_arr[i];
            int&& m_mod_cisub1 = magic_num % c_arr[i - 1];
            b_arr[i]           = (m_mod_ci - m_mod_cisub1) / c_arr[i - 1];
        }
    }
    void output() {
        for (int i = 1; i <= task_num; ++i) {
            std::cout << b_arr[i] << " ";
        }
    }
    static void solution() {
        TheCode the_solution;
        the_solution.input();
        the_solution.process();
        the_solution.output();
    }
};