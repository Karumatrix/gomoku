/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** MiniMax
*/

#pragma once

#define MAX_INT 1000000
#define MIN_INT -1000000

#include "GameBoard.hpp"
#include "PatternMatching.hpp"
#include <vector>
#include <chrono>

class MiniMax {
    public:
        MiniMax(GameBoard &gameboard);
        ~MiniMax();

        using TimePoint = std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::_V2::system_clock::duration>;
        int minimax(int depth, GameCase currPlayer, int alpha, int beta, int maxDepth, TimePoint start);
        std::vector<std::pair<int, int>> getPossibleMoves();
        int PawnsNumber(int x, int y, int checkX, int checkY);
        std::pair<int, int> getBestMove();

        bool isEnd();
        bool checkWin(GameCase player);
        bool checkDirection(int x, int y, int checkX, int checkY, GameCase player);
        void setTimeLimit(int newLimit);
        bool getIsFinished() const;
    protected:
    private:
        PatternMatching _patternMatching;
        GameBoard &_gameBoard;
        bool _isEnd = false;
        std::pair<int, int> _bestMove = {0, 0};
        int _timeLimit = 0;
        bool _isFinished = true;
};
