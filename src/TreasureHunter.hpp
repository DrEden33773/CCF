/**
 * @file TreasureHunter.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 202206-2
 * @version 0.1
 * @date 2022-11-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class TreasureHunter {
    using matrix_t     = std::vector<std::vector<int>>;
    using sub_matrix_t = std::vector<int>;
    using pair_t       = std::pair<int, int>;

    /* HashFunc of pair_t */
    struct IntPairHash {
        size_t operator()(const pair_t& pair) const { // must be const
            size_t first  = std::hash<int> {}(pair.first);
            size_t second = std::hash<int> {}(pair.second);
            return first ^ (second << 1);
        }
    };

    /* row data */
    int n = 0; // num of tree
    int L = 0;
    int S = 0;

    /* necessary data */
    int num_in_treasure_map = 0;

    /* map */
    matrix_t TreasureMap; // [0][0] to [S][S] => (S+1) * (S+1)

    /* vec => locations of all tree */
    std::unordered_set<pair_t, IntPairHash> TreeLocation;

    /* answer */
    int answer = 0;

    void init_TreasureMap() {
        TreasureMap = matrix_t(S + 1, sub_matrix_t(S + 1, 0));
    }
    void match_at(const int& x, const int& y) {
        // 1. if two areas have same number of tree
        int num_in_general_map = 0;
        for (int t_x = 0; t_x <= S; ++t_x) {
            for (int t_y = 0; t_y <= S; ++t_y) {
                pair_t pair = std::make_pair(x + t_x, y + t_y);
                if (TreeLocation.find(pair) != TreeLocation.end()) {
                    ++num_in_general_map;
                }
            }
        }
        if (num_in_general_map != num_in_treasure_map) {
            return;
        }
        // 2. if each area's tree_location is same
        for (int t_x = 0; t_x <= S; ++t_x) {
            for (int t_y = 0; t_y <= S; ++t_y) {
                if (!TreasureMap[t_x][t_y]) {
                    // not a tree on TreasureMap, continue
                    continue;
                }
                pair_t pair = std::make_pair(x + t_x, y + t_y);
                if (TreeLocation.find(pair) == TreeLocation.end()) {
                    // TreasureMap's tree not on GeneralMap, return
                    return;
                }
            }
        }
        ++answer;
    }
    void input() {
        // 1. size init
        cin >> n >> L >> S;
        // 2. init TreasureMap
        init_TreasureMap();
        // 3. Tree coordinate
        for (int i = 0; i < n; ++i) {
            int x = 0;
            int y = 0;
            cin >> x >> y;
            // update TreeLocation
            TreeLocation.insert(std::make_pair(x, y));
        }
        // 4. Treasure Map
        for (int i = 0; i <= S; ++i) {
            for (int j = 0; j <= S; ++j) {
                int x = S - i;
                int y = j;
                cin >> TreasureMap[x][y];
                if (TreasureMap[x][y]) {
                    ++num_in_treasure_map;
                }
            }
        }
    }
    void process() {
        for (const std::pair<int, int>& coordinate : TreeLocation) {
            int x = coordinate.first;
            int y = coordinate.second;

            const bool& if_x_in_range = x >= 0 && x <= L - S;
            const bool& if_Y_in_range = y >= 0 && y <= L - S;

            if (if_x_in_range && if_Y_in_range) {
                match_at(x, y);
            }
        }
    }
    void output() {
        cout << answer;
    }

public:
    static void solution() {
        TreasureHunter TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};
