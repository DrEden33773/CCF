/**
 * @file UninitializedWarning.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 202203-1
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

/// @attention @b DO_NOT_USE_VECTOR<BOOL>
/// @attention @b JUST_USE_VECTOR<INT>

#pragma once

#include <iostream>
#include <vector>

using namespace std;

class UninitializedWarning {
    int         n   = 0; // num of var
    int         k   = 0; // num of assignment
    int         ans = 0; // answer
    vector<int> table;   // initialization_status_table

public:
    void update_answer(const int& lhs, const int& rhs) {
        if (rhs != 0) {        // rhs is var
            if (!table[rhs]) { // rhs is uninitialized
                ++ans;
            }
        }
        table[lhs] = 1;
    }
    void input() {
        // input `num_of_var` & `num_of_assignment`
        cin >> n >> k;
        // init table
        table = vector<int>(n, 0);
        // input
        for (int i = 0; i < k; ++i) {
            int left  = 0;
            int right = 0;
            cin >> left >> right;
            update_answer(left, right);
        }
    }
    void output() {
        cout << ans;
    }

    static void solution() {
        UninitializedWarning TheSolution;
        TheSolution.input();
        TheSolution.output();
    }
};
