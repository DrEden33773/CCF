/**
 * @file AppleTreeTwo.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 201909-2
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class AppleTreeTwo {
    int N = 0; /* num of apple trees */

    int T = 0; /* num of sum of remained_apple */
    int D = 0; /* num of apple_dropped trees */
    int E = 0; /* num of apple_dropped group */

    // { index : [apple_num_1, apple_num_2, ... ] }
    unordered_map<int, vector<int>> Info;

    // [ ... ,if_{index}_dropped, ... ]
    // 0 = maintained, 1 = dropped
    vector<int> drop_case;

    void update_drop_case_of(int tree_idx, int apple_num_idx) {
        if (!apple_num_idx) {
            // apple_num_idx = 0 ==> 100% possibility of `observe`
            // impossible to update
            return;
        }
        vector<int>& info_vec = Info[tree_idx];
        if (info_vec[apple_num_idx] < info_vec[apple_num_idx - 1]) {
            if (!drop_case[tree_idx]) {
                // this tree hasn't dropped before, but now dropped
                ++D;
            } // or it has already dropped, then we shouldn't re_count that!
            drop_case[tree_idx] = 1;
        }
    }
    void input() {
        cin >> N;

        // 0. init drop_case vec
        drop_case = vector<int>(N, 0);

        for (int idx = 0; idx < N; ++idx) {
            // 1. opt_num
            int opt_num = 0;
            cin >> opt_num;

            // 2. init current info_vec in hashmap
            Info.insert(make_pair(idx, vector<int>(opt_num)));

            /* alias */
            vector<int>& curr_info_vec = Info[idx];

            // 3. opt/observe
            for (int i = 0; i < opt_num; ++i) {
                int curr = 0;
                cin >> curr;
                if (curr > 0) {
                    // didn't opt, just observe
                    curr_info_vec[i] = curr;
                    // drop will only be detected during observation process
                    update_drop_case_of(idx, i);
                } else {
                    // opt! need to get the `prefix`
                    curr_info_vec[i] = curr_info_vec[i - 1] + curr;
                }
            }
        }
    }
    void process() {
        // 1. figure out T
        for (int idx = 0; idx < N; ++idx) {
            vector<int>& curr_tree = Info[idx];
            T += curr_tree.back();
        }
        // 2. figure out E
        for (int idx = 0; idx < N; ++idx) {
            int next_idx      = (idx + 1) % N;
            int next_next_idx = (next_idx + 1) % N;
            if (drop_case[idx]
                && drop_case[next_idx]
                && drop_case[next_next_idx]) {
                ++E;
            }
        }
    }
    void output() {
        cout << T << " ";
        cout << D << " ";
        cout << E << " ";
    }

public:
    static void solution() {
        AppleTreeTwo TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};