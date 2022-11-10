/**
 * @file SequenceQuery.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 202012-2
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SequenceQuery {
    int         n = 0;
    int         N = 0;
    vector<int> seq;     // ascending order, could be guaranteed
    vector<int> sub_seq; // sub_seq[i] = seq[i+1] - seq[i] & sub_seq[n] = N - seq[n]

    int answer = 0;

public:
    void input() {
        // 1. input `n` and `N`
        cin >> n >> N;
        // 2. init seq & query
        seq     = vector<int>(n + 1, 0);
        sub_seq = vector<int>(n + 1, 0);
        // 3. input `A1`...`An`
        for (int idx = 1; idx <= n; ++idx) {
            int temp = 0;
            cin >> temp;
            seq[idx] = temp;
        }
    }
    void process() {
        // 1. build sub_seq
        for (int i = 0; i < n; ++i) {
            sub_seq[i] = seq[i + 1] - seq[i];
        }
        sub_seq[n] = N - seq[n];
        // 2. get answer
        for (int i = 1; i <= n; ++i) {
            answer += i * sub_seq[i];
        }
    }
    void output() {
        cout << answer;
    }

    static void solution() {
        SequenceQuery TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};