/**
 * @file NucleicAcidTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief NucleicAcidTest (1st week, 4th task)
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

// Update => Should use a `Differential Array`

/**
 * @note
        You need to take location into first consideration
        Use `enter_time` and `effective` period to found =>
        @b the_earliest(with_it) and @b the_latest(with_it) @e acid_check_time
            @p which @p satisfy_the_requirement
        Then you could simply @b add_one in the array
            @p which @p show_how_many_location_this_check_time_satisfy
            @p in_range_of @b [the_earliest,the_latest]
        That will be much easier to operate in an @b Diff_Array
            @b origin||->[the_earliest:the_latest]+=N
            @b diff||->[the_earliest]+=N,[the_latest+1]-=N
 *
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
using namespace std;

class NucleicAcidTest {
    // max_of_check_time = 2e5
    // max_of_waiting_period = 1e5
    // max_of_waiting_period + max_of_check_time = 3e5
    const int MAX = 2e5 + 1e5;

    int num_of_schedule = 0; // n
    int num_of_query    = 0; // m
    int waiting_period  = 0; // k

    /// @brief <enter_time, effective_period>
    vector<tuple<int, int>> schedule_list;

    /// @brief { effective_period: <enter_time, effective_period> }
    unordered_map<int, vector<int>> period_enter_map;

    /// @brief <time_of_check>
    vector<int> query_list;

    /// @brief result_vec
    vector<int> res;

    /// @brief Differential Array
    vector<int> Differential = vector<int>(MAX + 4, 0);

    /// @brief binary-search-based, for `ascending ordered` query_list
    auto find_first_non_smaller_than(const int& range_begin)
        -> decltype(schedule_list.begin()) {
        int enter_time       = 0;
        int effective_period = 0;

        tie(enter_time, effective_period) = schedule_list.back();
        if (enter_time < range_begin) {
            return schedule_list.end();
        }

        auto&& first_non_smaller = schedule_list.end();
        auto&& left              = schedule_list.begin();
        auto&& right             = schedule_list.end() - 1;

        while (left <= right) {
            auto&& mid = left + ((right - left) / 2);

            int enter_time       = 0;
            int effective_period = 0;

            tie(enter_time, effective_period) = *mid;
            if (enter_time >= range_begin) {
                if (first_non_smaller == schedule_list.end()) {
                    first_non_smaller = mid;
                } else {
                    first_non_smaller = (first_non_smaller < mid)
                        ? first_non_smaller
                        : mid;
                }
                if (mid == schedule_list.begin()) {
                    break;
                }
                right = mid - 1;
            } else {
                if (mid == schedule_list.end()) {
                    break;
                }
                left = mid + 1;
            }
        }

        return first_non_smaller;
    }

    // >=
    auto v_find_first_non_smaller_than(
        vector<int>& vec,
        const int&   range_begin
    ) -> decltype(vec.begin()) {
        auto&& first_non_smaller = vec.end();
        auto&& left              = vec.begin();
        auto&& right             = vec.end() - 1;

        while (left <= right) {
            auto&& mid        = left + ((right - left) / 2);
            int    enter_time = *mid;
            if (enter_time >= range_begin) {
                if (first_non_smaller == vec.end()) {
                    first_non_smaller = mid;
                } else {
                    first_non_smaller = (first_non_smaller < mid)
                        ? first_non_smaller
                        : mid;
                }
                if (mid == vec.begin()) {
                    break;
                }
                right = mid - 1;
            } else {
                if (mid == vec.end()) {
                    break;
                }
                left = mid + 1;
            }
        }

        return first_non_smaller;
    }

public:
    // element in `origin_arr of diff_arr` in range [left, right] + value
    void insert_differential(int left, int right, int value) {
        Differential[left] += value;
        Differential[right + 1] -= value;
    }
    void input() {
        // n, m, k
        cin >> num_of_schedule;
        cin >> num_of_query;
        cin >> waiting_period;
        // input schedule
        schedule_list.reserve(num_of_schedule);
        for (int i = 0; i < num_of_schedule; ++i) {
            int enter_time       = 0;
            int effective_period = 0;
            cin >> enter_time;
            cin >> effective_period;

            // build: schedule_list => O(1)
            auto&& curr_tuple = make_tuple(enter_time, effective_period);
            schedule_list.emplace_back(curr_tuple);

            // build: period_enter_map => O(1)
            period_enter_map[effective_period].push_back(enter_time);

            // build: differential
            int  earliest_report_time = 0;
            int  latest_report_time   = 0;
            int& left                 = earliest_report_time;
            int& right                = latest_report_time;
            // left + effective_period - 1 = enter_time
            left  = enter_time - effective_period + 1;
            right = enter_time;
            left  = (left >= 0) ? left : 0;
            insert_differential(left, right, 1);
        }
        // input query_of <time_of_check>
        query_list.reserve(num_of_query);
        for (int i = 0; i < num_of_query; ++i) {
            int time_of_check = 0;
            cin >> time_of_check;
            query_list.emplace_back(time_of_check);
        }
    }
    void get_res() {
        // check
        res.reserve(query_list.size());
        for (auto&& time_of_check : query_list) {
            int    curr_available_num = 0;
            int    range_begin        = time_of_check + waiting_period; // >=
            auto&& first_not_ahead    = find_first_non_smaller_than(range_begin);
            if (first_not_ahead != schedule_list.end()) {
                for (
                    auto&& iter = first_not_ahead;
                    iter != schedule_list.end();
                    ++iter
                ) {
                    int enter_time       = 0;
                    int effective_period = 0;
                    tie(enter_time, effective_period)
                        = *iter;
                    int range_end = range_begin + effective_period; // <
                    if (enter_time < range_end) {
                        ++curr_available_num;
                    }
                }
            }
            res.emplace_back(curr_available_num);
        }
    }
    void improved_get_res() {
        // run check in the map
        for (auto&& time_of_check : query_list) {
            int curr_available_num = 0;
            int range_begin        = time_of_check + waiting_period; // >=
            for (auto&& curr_pair : period_enter_map) {
                const int&   effective_period = curr_pair.first;
                vector<int>& enter_time_list  = curr_pair.second;

                int    range_end = range_begin + effective_period;
                auto&& first_beq_than_begin
                    = v_find_first_non_smaller_than(enter_time_list, range_begin);
                auto&& first_beq_than_end
                    = v_find_first_non_smaller_than(enter_time_list, range_end);

                // note => should pick [first_beq_than_begin, first_beq_than_end)
                // which means [IndexOf->first>=range_begin, IndexOf->first>=range_end)
                //
                // eg => [1,1,2,2,3,4], want to pick [2,3)
                // which means to pick [IndexOf->first_beq_than_2, IndexOf->first_beq_than_3)
                //
                // and then Num_Of_Elements_In_Range =
                // IndexOf->first>=range_end - IndexOf->first>=range_begin

                auto&& sub_available_num = first_beq_than_end - first_beq_than_begin;
                curr_available_num += static_cast<int>(sub_available_num);
            }
            res.emplace_back(curr_available_num);
        }
    }
    void best_get_res() {
        res.reserve(query_list.size());
        for (int i = 1; i <= MAX; i++) {
            Differential[i] = Differential[i - 1] + Differential[i];
        }
        for (auto&& time_of_check : query_list) {
            res.emplace_back(Differential[time_of_check + waiting_period]);
        }
    }
    void output() {
        for (auto&& curr_available_num : res) {
            cout << curr_available_num << endl;
        }
    }
    static void solution() {
        NucleicAcidTest TheSolution;
        TheSolution.input();
        TheSolution.best_get_res();
        TheSolution.output();
    }
};