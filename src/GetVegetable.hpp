/**
 * @file GetVegetable.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 201809-2
 * @version 0.1
 * @date 2022-10-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

// This is a variation of traditional `in out vehicle`
// It judges the time of `both on the vehicle`

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class GetVegetable {
    std::vector<std::pair<int, int>> ATime;
    std::vector<std::pair<int, int>> BTime;

    /// @brief @b 0__|=>__used_by_non
    /// @brief @b 1__|=>__used_by_one
    /// @brief @b 2__|=>__used_by_two
    std::vector<int> TimeTable;

    int END_OF_PERIOD = 0;
    int BEG_OF_PERIOD = 0;
    int number        = 0;
    int answer        = 0;

public:
    void input() {

        int num = 0;
        std::cin >> num;
        number = num;

        ATime     = std::vector<std::pair<int, int>>(num + 3);
        BTime     = std::vector<std::pair<int, int>>(num + 3);
        TimeTable = std::vector<int>(1000003, 0);

        for (int i = 1; i <= num; ++i) {
            int ABeg = 0;
            int AEnd = 0;
            std::cin >> ABeg >> AEnd;
            BEG_OF_PERIOD = std::min(BEG_OF_PERIOD, ABeg);
            END_OF_PERIOD = std::max(END_OF_PERIOD, AEnd);
            ATime[i]      = std::make_pair(ABeg, AEnd);

            for (int j = ABeg; j < AEnd; ++j) {
                ++TimeTable[j];
            }
            --TimeTable[AEnd];
        }

        for (int i = 1; i <= num; ++i) {
            int BBeg = 0;
            int BEnd = 0;
            std::cin >> BBeg >> BEnd;
            BEG_OF_PERIOD = std::min(BEG_OF_PERIOD, BBeg);
            END_OF_PERIOD = std::max(END_OF_PERIOD, BEnd);
            BTime[i]      = std::make_pair(BBeg, BEnd);

            for (int j = BBeg; j < BEnd; ++j) {
                ++TimeTable[j];
            }
            --TimeTable[BEnd];
        }
    }
    void process() {
        for (int i = BEG_OF_PERIOD; i <= END_OF_PERIOD; ++i) {
            if (TimeTable[i] == 2) {
                ++answer;
            }
        }
    }
    void output() {
        std::cout << answer;
    }
    static void solution() {
        GetVegetable S;
        S.input();
        S.process();
        S.output();
    }
};