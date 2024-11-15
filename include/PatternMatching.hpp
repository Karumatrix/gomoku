/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** PatternMatching
*/

#pragma once

#include "Positions.hpp"
#include "GameBoard.hpp"

class PatternMatching {
    public:
        PatternMatching();
        ~PatternMatching();

        Positions getBestPositions(GameBoard &board);
    private:
        bool checkVerticalWeakness(int x, int y, size_t size);
        bool checkHorizontalWeakness(int x, int y, size_t size);
        bool checkDiagonalWeakness(int x, int y, size_t size);
};
