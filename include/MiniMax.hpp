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
#include "PatternMatching.hpp"
#include <vector>

class MiniMax {
    public:
        MiniMax(GameBoard &gameboard);
        ~MiniMax();

        int minimax(int depth, bool playerMax);
        std::vector<std::pair<int, int>> getPossibleMoves();
        int evaluateBoard();
        bool isEnd();
        bool checkWin(GameCase player);
        bool checkDirection(int x, int y, int checkX, int checkY, GameCase player);
    protected:
    private:
        PatternMatching _patternMatching;
        GameBoard _gameBoard;
};
