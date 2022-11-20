/**
 * @file Tetris.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief @b 201604-2
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Tetris {
    using SubMatrixType = vector<int>;
    using MatrixType    = vector<vector<int>>;

    static constexpr int ROW     = 15;
    static constexpr int COL     = 10;
    static constexpr int IN_SIZE = 4;

    int IN_ROW = IN_SIZE;
    int IN_COL = IN_SIZE;

    MatrixType Mat; // original mat
    MatrixType In;  // input

    /* The lefter col of input */
    int which_col = 0; // [0, COL)

    /* The upper row of input */
    int which_row = 0; // [0, ROW)

    Tetris() {
        Mat = MatrixType(ROW, SubMatrixType(COL, 0));
        In  = MatrixType(IN_SIZE, SubMatrixType(IN_SIZE, 0));
    }

    void init() {
        for (int in_row = 0; in_row < IN_ROW; ++in_row) {
            for (int in_col = 0; in_col < IN_COL; ++in_col) {
                int row       = in_row + which_row;
                int col       = in_col + which_col;
                Mat[row][col] = In[in_row][in_col];
            }
        }
    }
    bool move_down() {
        bool if_touch_the_bottle = false;
        // 1. move down
        int which_row_before_moved = which_row;
        ++which_row;
        // 2. judge if have `whole row of 0` get out
        if (which_row + IN_ROW >= ROW) {
            for (int in_col = 0; in_col < IN_COL; ++in_col) {
                if (In[IN_ROW - 1][in_col]) {
                    if_touch_the_bottle = true;
                }
            }
            if (!if_touch_the_bottle) {
                --IN_ROW;
            }
        }
        for (int in_row = 0; in_row < IN_ROW; ++in_row) {
            for (int in_col = 0; in_col < IN_COL; ++in_col) {
                int row = in_row + which_row;
                int col = in_col + which_col;
                if (Mat[row][col] != 1) {
                    Mat[row][col] = In[in_row][in_col];
                }
            }
        }
        for (int in_col = 0; in_col < IN_COL; ++in_col) {
            Mat[which_row_before_moved][in_col + which_col] = 0;
        }
        return if_touch_the_bottle;
    }
    bool if_collide() {
        for (int in_row = 0; in_row < IN_ROW; ++in_row) {
            for (int in_col = 0; in_col < IN_COL; ++in_col) {
                int row      = in_row + which_row;
                int col      = in_col + which_col;
                int next_row = row + 1;
                if (Mat[next_row][col] == 1 && Mat[row][col] == 2) {
                    return true;
                }
            }
        }
        return false;
    }

    bool if_output_input(
        const int& curr_row,
        const int& curr_col
    ) {
        bool if_row_satisfy = (curr_row >= which_row)
            && (curr_row < (which_row + IN_SIZE));
        bool if_col_satisfy = (curr_col >= which_col)
            && (curr_col < (which_col + IN_SIZE));
        if (if_row_satisfy && if_col_satisfy) {
            return true;
        }
        return false;
    }

public:
    void input() {
        for (int row = 0; row < ROW; ++row) {
            for (int col = 0; col < COL; ++col) {
                cin >> Mat[row][col];
            }
        }
        for (int row = 0; row < IN_SIZE; ++row) {
            for (int col = 0; col < IN_SIZE; ++col) {
                cin >> In[row][col];
                if (In[row][col]) {
                    In[row][col] = 2;
                }
            }
        }
        cin >> which_col;
        if (which_col > 7) {
            throw std::runtime_error("Input shouldn't bigger than 7, exit... ");
        }
        --which_col;
    }
    void process() {
        init();
        // judge
        while (!if_collide()) {
            bool if_touched_bottle_after_curr_move = move_down();
            if (if_touched_bottle_after_curr_move) {
                break;
            }
        }
    }
    void output() {
        for (int row = 0; row < ROW; ++row) {
            for (int col = 0; col < COL; ++col) {
                if (Mat[row][col]) {
                    cout << "1 ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
    static void solution() {
        Tetris TheSolution;
        TheSolution.input();
        TheSolution.process();
        TheSolution.output();
    }
};