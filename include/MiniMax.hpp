/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** MiniMax
*/

#pragma once

#define MAX_DEPTH 3
#define MAX_INT 1000000.0f
#define MIN_INT -1000000.0f

#include "GameBoard.hpp"
#include "PatternMatching.hpp"
#include <vector>

class MiniMax {
    public:
        MiniMax(GameBoard &gameboard);
        ~MiniMax();

        float minimax(int depth, bool playerMax, float alpha, float beta);
        std::vector<std::pair<int, int>> getPossibleMoves();
        int PawnsNumber(int x, int y, int checkX, int checkY);
        int evaluation();
        int evaluateBoard();
        std::pair<int, int> getBestMove();

        bool isEnd();
        bool checkWin(GameCase player);
        bool checkDirection(int x, int y, int checkX, int checkY, GameCase player);
    protected:
    private:
        PatternMatching _patternMatching;
        GameBoard &_gameBoard;
        bool _isEnd = false;
        std::pair<int, int> _bestMove;
};
