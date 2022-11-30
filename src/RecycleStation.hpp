/**
 * @file RecycleStation.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class RecycleStation {
    using IntPair = std::pair<int, int>;

    struct IntPairHash {
        size_t operator()(const IntPair& pair) const {
            size_t first  = hash<int> {}(pair.first);
            size_t second = hash<int> {}(pair.second);
            return first ^ (second << 1);
        }
    };

    unordered_map<int, int> score_map {
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { 3, 0 },
        { 4, 0 },
    };

    unordered_set<IntPair, IntPairHash> location_set;
    unordered_set<IntPair, IntPairHash> available_location_set;
    int                                 location_num = 0;

    void input() {
        cin >> location_num;
        for (int i = 0; i < location_num; ++i) {
            int x = 0;
            int y = 0;
            cin >> x >> y;
            location_set.insert(make_pair(x, y));
        }
    }
    void process() {
        // 1. get available_location_set
        for (const IntPair& pair : location_set) {
            int       x      = pair.first;
            int       y      = pair.second;
            IntPair&& xp1    = make_pair(x + 1, y);
            IntPair&& xs1    = make_pair(x - 1, y);
            IntPair&& yp1    = make_pair(x, y + 1);
            IntPair&& ys1    = make_pair(x, y - 1);
            bool      if_xp1 = location_set.find(xp1) != location_set.end();
            bool      if_xs1 = location_set.find(xs1) != location_set.end();
            bool      if_yp1 = location_set.find(yp1) != location_set.end();
            bool      if_ys1 = location_set.find(ys1) != location_set.end();
            if (if_xp1 && if_xs1 && if_yp1 && if_ys1) {
                // available_location
                int       score = 0;
                IntPair&& a     = make_pair(x + 1, y + 1);
                IntPair&& b     = make_pair(x - 1, y + 1);
                IntPair&& c     = make_pair(x + 1, y - 1);
                IntPair&& d     = make_pair(x - 1, y - 1);
                bool      if_a  = location_set.find(a) != location_set.end();
                bool      if_b  = location_set.find(b) != location_set.end();
                bool      if_c  = location_set.find(c) != location_set.end();
                bool      if_d  = location_set.find(d) != location_set.end();
                for (auto curr : { if_a, if_b, if_c, if_d }) {
                    if (curr) {
                        ++score;
                    }
                }
                // score statistic
                ++score_map[score];
            }
        }
    }
    void output() {
        for (int i = 0; i <= 4; ++i) {
            cout << score_map[i] << endl;
        }
    }

public:
    static void solution() {
        RecycleStation TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};