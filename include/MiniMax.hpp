/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** MiniMax
*/

#pragma once

#define MAX_DEPTH 4
#define MAX_INT 1000000
#define MIN_INT -1000000

#include "GameBoard.hpp"

class MiniMax {
    public:
        MiniMax(GameBoard &gameboard);
        ~MiniMax();

        int minimax(int depth, bool playerMax);
        std::vector<int, int> getPossibleMoves();
    protected:
    private:
        GameBoard _gameBoard;
};
