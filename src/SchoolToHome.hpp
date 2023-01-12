/**
 * @file SchoolToHome.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 201812-2
 * @version 0.1
 * @date 2022-11-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct SchoolToHome {
    using ll = long long;

    static ll r_cnt;
    static ll y_cnt;
    static ll g_cnt;

    ll        answer            = 0;
    const ll& curr_waiting_time = answer;

    struct TrafficLight {
        enum class Status : unsigned short {
            Red    = 1,
            Yellow = 2,
            Green  = 3,
        };
        Status status    = Status::Red;
        ll     time_left = 0;

        TrafficLight(ll status_code, ll time) {
            switch (status_code) {
            case 1:
                status = Status::Red;
                break;
            case 2:
                status = Status::Yellow;
                break;
            case 3:
                status = Status::Green;
                break;
            }
            time_left = time;
        }
        void update_status() {
            if (!time_left) {
                switch (status) {
                case Status::Red:
                    status    = Status::Green;
                    time_left = g_cnt;
                    break;
                case Status::Yellow:
                    status    = Status::Red;
                    time_left = r_cnt;
                    break;
                case Status::Green:
                    status    = Status::Yellow;
                    time_left = y_cnt;
                    break;
                }
            }
        }
        void TimePass(ll passed_time) {
            ll modded = passed_time % (r_cnt + y_cnt + g_cnt);
            while (modded) {
                if (modded <= time_left) {
                    time_left -= modded;
                    modded = 0;
                } else {
                    modded -= time_left;
                    time_left = 0;
                }
                update_status();
            }
        }
        void operator-(ll passed_time) {
            TimePass(passed_time);
        }
        ll GetWaitingTime() {
            ll res = 0;
            if (status == Status::Red) {
                res += time_left;
            } else if (status == Status::Yellow) {
                res += time_left;
                res += r_cnt;
            } else {
                res = 0;
            }
            return res;
        }
    };

    void input() {
        cin >> r_cnt >> y_cnt >> g_cnt;

        ll n = 0;
        cin >> n;

        for (ll i = 0; i < n; ++i) {
            ll k = 0;
            ll t = 0;
            cin >> k >> t;
            if (k == 0) {
                answer += t;
            } else {
                // 1. build the model of current traffic light
                TrafficLight curr_traffic_light(k, t);

                // 2. update the time table of current traffic light
                // for your previous actions costs time, which should
                // take into consideration
                curr_traffic_light.TimePass(curr_waiting_time);

                // 3. calculate time for waiting => only after updating
                answer += curr_traffic_light.GetWaitingTime();
            }
        }
    }
    void output() {
        cout << answer;
    }
    static void solution() {
        SchoolToHome TheSolution;
        TheSolution.input();
        TheSolution.output();
    }
};

SchoolToHome::ll SchoolToHome::r_cnt = 0;
SchoolToHome::ll SchoolToHome::y_cnt = 0;
SchoolToHome::ll SchoolToHome::g_cnt = 0;
