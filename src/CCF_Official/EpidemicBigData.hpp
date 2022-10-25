/**
 * @file EpidemicBigData.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b CCF_202209-3
 * @version 0.1
 * @date 2022-10-12
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief
        @e user_tuple @b <date,user,region>
        @e epidemic_tuple @b <date,region> @p [date,date+7)-->epidemic_duration
 *
 */

#pragma once
#include <iostream>
#include <map>
#include <tuple>
#include <unordered_map>
#include <vector>
using namespace std;

class solution {
    int _day = 0;

    using date          = int;
    using area_list     = vector<int>;
    using user_list     = vector<int>;
    using user_msg      = tuple<int, int, int>;
    using user_msg_list = vector<user_msg>;

    unordered_map<date, area_list>     epidemic_info;
    unordered_map<date, user_msg_list> routing_message;
    map<date, user_list>               res;

public:
    /// @brief @b data_input
    void input_routing_msg(const int& date, const int& _routing_msg) {
        user_msg_list curr_list;
        curr_list.reserve(_routing_msg);
        for (int i = 0; i < _routing_msg; ++i) {
            int user_date = 0;
            int user_id   = 0;
            int region_id = 0;
            cin >> user_date >> user_id >> region_id;
            user_msg usr_tup = make_tuple(user_date, user_id, region_id);
            curr_list.emplace_back(usr_tup);
        }
        routing_message[date] = curr_list;
    }
    int input_epidemic_info(const int& date) {
        int       _warning     = 0;
        int       _routing_msg = 0;
        area_list warning_area;
        warning_area.reserve(_warning);
        cin >> _warning >> _routing_msg;
        for (int i = 0; i < _warning; ++i) {
            int area = 0;
            cin >> area;
            warning_area.emplace_back(area);
        }
        epidemic_info[date] = warning_area;
        return _routing_msg;
    }
    void input() {
        cin >> _day;
        for (int date = 0; date < _day; ++date) {
            int _routing_msg = input_epidemic_info(date);
            input_routing_msg(date, _routing_msg);
        }
    }

    /// @brief @b sort_routing_message_by_date
    void sort_routing_message_by_date() {
        for (int date = 0; date < _day; ++date) {
            user_msg_list& curr_list = routing_message[date];
            std::sort(
                curr_list.begin(),
                curr_list.end(),
                [](user_msg& a, user_msg& b) {
                    int a_date, a_user, a_region;
                    int b_date, b_user, b_region;
                    std::tie(a_date, a_user, a_region) = a;
                    std::tie(b_date, b_user, b_region) = b;
                    return a_date < b_date;
                }
            );
        }
    }

    /// @brief @b data_process
    user_list make_user_list(const int& date) {
        user_list res;
        return res;
    }
    void process() {
        for (int date = 0; date < _day; ++date) {
            user_list returned = make_user_list(date);
            res[date]          = returned;
        }
    }

    /// @brief @b output
    void output() {
        for (int date = 0; date < _day; ++date) {
            cout << date << " ";
            for (auto&& user : res[date]) {
                cout << user << " ";
            }
            cout << endl;
        }
    }

    /// @brief @b interface
    void interface() {
        input();
        sort_routing_message_by_date();
        process();
        output();
    }
};
