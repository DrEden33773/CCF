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
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

class ToSaveMailFee {
    int NumOfBooks = 0;
    int MinFee     = 0;
    int CurrSumFee = 0;
    int ans        = 0;

    /// @brief [ <price, if_deleted> ]
    vector<pair<int, bool>> BookPriceList;
    vector<int>             PriceList;

public:
    void input() {
        int numOfBooks = 0;
        int minFee     = 0;
        cin >> numOfBooks >> minFee;
        NumOfBooks = numOfBooks;
        MinFee     = minFee;

        BookPriceList.reserve(numOfBooks);
        PriceList.reserve(numOfBooks);
        for (int index = 0; index < numOfBooks; ++index) {
            int price = 0;
            cin >> price;
            CurrSumFee += price;
            auto&& toInsert = make_pair(price, false);
            BookPriceList.emplace_back(toInsert);
            PriceList.emplace_back(price);
        }

        ans = CurrSumFee;
    }

    /// @brief @b enum_dfs
    void DFS_func(int pos, int curr_price) {
        if (pos == NumOfBooks) {
            // has reached the limit
            if (curr_price >= MinFee) {
                ans = min(ans, curr_price);
            }
            return;
        }
        if (curr_price >= MinFee) {
            ans = min(ans, curr_price);
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

    /// @brief @b zero_one_DP_pack
    void process() {
    }

    void output() {
        cout << ans;
    }

    static void solution() {
        ToSaveMailFee TheSolution;
        TheSolution.input();
        TheSolution.partial_process();
        TheSolution.output();
    }
};