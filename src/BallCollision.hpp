/**
 * @file BallCollision.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief BallCollision (1st week, 5th task)
 * @version 0.1
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class BallCollision {
    int num_of_ball = 0;
    int length      = 0;
    int calc_time   = 0;

    int max_location = 0;

    constexpr static int velocity = 1;

    /// @brief <index, location>
    std::vector<std::pair<int, int>> ball_info;

    /// @attention only used after sort ball_info by `location`
    std::vector<int> velocity_map_after_ordered;

public:
    void init_velocity() {
        velocity_map_after_ordered.reserve(num_of_ball);
        for (int index = 0; index < num_of_ball; ++index) {
            velocity_map_after_ordered.emplace_back(velocity);
        }
    }
    void input() {
        std::cin >> num_of_ball;
        std::cin >> length;
        std::cin >> calc_time;
        max_location = length;

        ball_info.reserve(num_of_ball);
        for (int i = 0; i < num_of_ball; ++i) {
            int curr_location = 0;
            std::cin >> curr_location;
            auto input = std::make_pair(i, curr_location);
            ball_info.emplace_back(input);
        }

        std::sort(
            ball_info.begin(),
            ball_info.end(),
            [](pair<int, int>& a, pair<int, int>& b) {
                return a.second < b.second;
            }
        );

        init_velocity();
    }
    void reverse_velocity(const int& index) {
        velocity_map_after_ordered[index] *= -1;
    }
    void update(const int& times = 0) {
        if (times == 0) {
            return;
        }
        // now, maintain the second_decided_ordered ball_info
        for (int updated = 0; updated < times; ++updated) {
            for (int index = 0; index < num_of_ball; ++index) {
                int unwrapped_index    = ball_info[index].first;
                int unwrapped_location = ball_info[index].second;

                bool if_head = false;
                bool if_tail = false;

                if (index == 0) {
                    if_head = true;
                } else if (index == num_of_ball - 1) {
                    if_tail = true;
                }

                bool collision_with_prev = false;
                bool collision_with_next = false;

                collision_with_prev = (if_head == true)
                    ? ball_info[index].second == 0
                    : ball_info[index].second == ball_info[index - 1].second;
                collision_with_next = (if_tail == true)
                    ? ball_info[index].second == max_location
                    : ball_info[index].second == ball_info[index + 1].second;

                if (collision_with_prev || collision_with_next) {
                    reverse_velocity(index);
                }
            }
            for (int index = 0; index < num_of_ball; ++index) {
                ball_info[index].second += velocity_map_after_ordered[index];
            }
        }
        // re-order ball_info by `index`
        std::sort(
            ball_info.begin(),
            ball_info.end(),
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.first < b.first;
            }
        );
    }
    void output() {
        for (auto& pair : ball_info) {
            auto& index    = pair.first;
            auto& location = pair.second;
            std::cout << location << " ";
        }
    }
    static void solution() {
        BallCollision TheSolution;
        TheSolution.input();
        TheSolution.update(TheSolution.calc_time);
        TheSolution.output();
    }
};
