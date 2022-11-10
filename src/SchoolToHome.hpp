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
    static int r_cnt;
    static int y_cnt;
    static int g_cnt;

    struct TrafficLight {
        enum class Status : unsigned short {
            Red    = 1,
            Yellow = 2,
            Green  = 3,
        };
        Status status    = Status::Red;
        int    time_left = 0;

        TrafficLight(int status_code, int time) {
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
        void OneSecondLater() {
            --time_left;
            update_status();
        }
        void TimePass(int passed_time) {
            for (int i = 0; i < passed_time; ++i) {
                OneSecondLater();
            }
        }
        void BetterTimePass(int passed_time) {
            while (passed_time) {
                if (passed_time <= time_left) {
                    time_left -= passed_time;
                    passed_time = 0;
                } else {
                    passed_time -= time_left;
                    time_left = 0;
                }
                update_status();
            }
        }
        void operator-(int passed_time) {
            BetterTimePass(passed_time);
        }
        int GetWaitingTime() {
            int res = 0;
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

    list<TrafficLight> TrafficLights;
    list<int>          Paths;
    int                answer = 0;

    void input() {
        cin >> r_cnt >> y_cnt >> g_cnt;

        int n = 0;
        cin >> n;

        for (int i = 0; i < n; ++i) {
            int k = 0;
            int t = 0;
            cin >> k >> t;
            if (k == 0) {
                Paths.push_back(t);
            } else {
                TrafficLight a_traffic_light(k, t);
                TrafficLights.push_back(a_traffic_light);
                Paths.push_back(-1);
            }
        }
    }
    void update_all_lights(int passed_time) {
        for (TrafficLight& curr_light : TrafficLights) {
            curr_light - passed_time;
        }
    }
    void process() {
        // no lights
        if (TrafficLights.empty()) {
            for (int& pass_time : Paths) {
                answer += pass_time;
            }
            return;
        }
        // have lights
        for (int& time_in_need : Paths) {
            if (time_in_need == -1) {
                // meet a traffic light
                TrafficLight& curr_light   = TrafficLights.front();
                int           waiting_time = curr_light.GetWaitingTime();
                update_all_lights(waiting_time);
                answer += waiting_time;
                TrafficLights.pop_front();
            } else {
                update_all_lights(time_in_need);
                answer += time_in_need;
            }
        }
    }
    void output() {
        cout << answer;
    }
    static void solution() {
        SchoolToHome TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};

int SchoolToHome::r_cnt = 0;
int SchoolToHome::y_cnt = 0;
int SchoolToHome::g_cnt = 0;
