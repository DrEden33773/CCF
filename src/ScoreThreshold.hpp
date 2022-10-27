/**
 * @file ScoreThreshold.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 202012-2
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class ScoreThreshold {
    int num_of_data = 0;
    int answer      = 0;
    int num_of_y    = 0; // y->{ 1, 1, 2, 3 } => num_of_y == 3

    // { y : num_of(1) }
    map<int, int> num_of_pass; // y_ascending

    // { y : num_of(0) }
    map<int, int> num_of_fail; // y_ascending

    // { num_of_correct_case : [ y ] }
    map<int, vector<int>> final_map; // num_of_correct_case_ascending

    void make_map() {
        // 1. transfer map into vec
        vector<pair<int, int>> vec_num_of_fail;
        vector<pair<int, int>> vec_num_of_pass;
        vec_num_of_fail.reserve(num_of_y);
        vec_num_of_pass.reserve(num_of_y);
        for (auto&& elem : num_of_fail) {
            vec_num_of_fail.emplace_back(elem);
        }
        for (auto&& elem : num_of_pass) {
            vec_num_of_pass.emplace_back(elem);
        }

        // 2. allocate space for sub_arr (prefix)
        vector<pair<int, int>> sub_fail(num_of_y);
        vector<pair<int, int>> sub_pass(num_of_y);

        // 3. fill `sub_fail` vec
        for (int i = 0; i < num_of_y; ++i) {
            int y               = vec_num_of_fail[i].first;
            int num_of_sub_fail = 0;
            if (i == 0) {
                num_of_sub_fail = 0;
            } else {
                num_of_sub_fail = sub_fail[i - 1].second + vec_num_of_fail[i - 1].second;
            }
            sub_fail[i] = make_pair(y, num_of_sub_fail);
        }

        // 4. fill `sub_success` vec
        // (1). reverse `vec_num_of_pass`
        auto&& beg_iter = vec_num_of_pass.begin();
        auto&& end_iter = vec_num_of_pass.end() - 1;
        while (beg_iter < end_iter) {
            swap(*beg_iter, *end_iter);
            ++beg_iter;
            --end_iter;
        }
        // (2). prefix
        for (int i = 0; i < num_of_y; ++i) {
            int y               = vec_num_of_pass[i].first;
            int num_of_sub_pass = 0;
            if (i == 0) {
                num_of_sub_pass = vec_num_of_pass[0].second;
            } else {
                num_of_sub_pass = sub_pass[i - 1].second + vec_num_of_pass[i].second;
            }
            sub_pass[i] = make_pair(y, num_of_sub_pass);
        }
        // (3). reverse `sub_pass` again => right order
        beg_iter = sub_pass.begin();
        end_iter = sub_pass.end() - 1;
        while (beg_iter < end_iter) {
            swap(*beg_iter, *end_iter);
            ++beg_iter;
            --end_iter;
        }

        // 5. add up, make map
        for (int i = 0; i < num_of_y; ++i) {
            int y                   = sub_fail[i].first;
            int num_of_correct_case = sub_fail[i].second + sub_pass[i].second;
            final_map[num_of_correct_case].push_back(y);
        }
    }

public:
    void input() {
        cin >> num_of_data;

        vector<pair<int, int>> temp(num_of_data);

        for (int i = 0; i < num_of_data; ++i) {
            int y      = 0;
            int result = 0;
            cin >> y >> result;

            temp[i] = make_pair(y, result);
        }

        for (auto&& curr_pair : temp) {
            num_of_pass[curr_pair.first] = 0;
            num_of_fail[curr_pair.first] = 0;
        }

        num_of_y = static_cast<int>(num_of_fail.size());

        for (auto&& curr_pair : temp) {
            if (curr_pair.second) {
                ++num_of_pass[curr_pair.first];
            } else {
                ++num_of_fail[curr_pair.first];
            }
        }
    }
    void process() {
        make_map();

        vector<pair<int, vector<int>>> final_vec;
        final_vec.reserve(num_of_data);
        for (auto&& elem : final_map) {
            final_vec.emplace_back(elem);
        }

        vector<int>& optional_vec = final_vec.back().second;

        for (auto&& elem : optional_vec) {
            answer = max(answer, elem);
        }
    }
    void output() {
        cout << answer;
    }

    static void solution() {
        ScoreThreshold TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};