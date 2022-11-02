/**
 * @file ToSaveMailFee.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 202209-2
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class ToSaveMailFee {
    int NumOfBooks = 0;
    int MinFee     = 0;
    int CurrSumFee = 0;
    int ans        = 0;

    vector<int> PriceList;
    vector<int> Prefix_List;

public:
    void input() {
        int numOfBooks = 0;
        int minFee     = 0;
        cin >> numOfBooks >> minFee;
        NumOfBooks = numOfBooks;
        MinFee     = minFee;

        PriceList   = vector<int>(numOfBooks);
        Prefix_List = vector<int>(numOfBooks);

        for (int index = 0; index < numOfBooks; ++index) {
            int price = 0;
            cin >> price;
            CurrSumFee += price;
            PriceList[index] = price;
            if (index == 0) {
                Prefix_List[index] = PriceList[index];
            } else {
                Prefix_List[index] = PriceList[index] + Prefix_List[index - 1];
            }
        }

        ans = CurrSumFee;
    }

    /// @brief @b enum_dfs
    void DFS_func(const int& pos, const int& curr_price) {
        if (curr_price >= MinFee) {
            ans = min(ans, curr_price);
            return;
        }
        if (pos == NumOfBooks) {
            return;
        }
        // unselected PriceList[pos]
        DFS_func(pos + 1, curr_price);
        // selected PriceList[pos]
        DFS_func(pos + 1, curr_price + PriceList[pos]);
    }
    void partial_process() {
        DFS_func(0, 0);
    }

    /// @brief @b dfs_with_cutting_edge
    void better_dfs(const int& pos, const int& curr_price) {
        // cutting edge at first
        int curr_sum_of_rest = 0;
        if (!pos) {
            curr_sum_of_rest = Prefix_List[NumOfBooks - 1];
        } else {
            curr_sum_of_rest = Prefix_List[NumOfBooks - 1] - Prefix_List[pos - 1];
        }
        if (curr_price + curr_sum_of_rest < MinFee) {
            // curr_price is too low! You could just discard it
            return;
        }

        if (curr_price >= MinFee) {
            ans = min(ans, curr_price);
            return;
        }
        if (pos == NumOfBooks) {
            return;
        }
        // unselected PriceList[pos]
        better_dfs(pos + 1, curr_price);
        // selected PriceList[pos]
        better_dfs(pos + 1, curr_price + PriceList[pos]);
    }
    void process() {
        better_dfs(0, 0);
    }

    void output() {
        cout << ans;
    }

    static void solution() {
        ToSaveMailFee TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};