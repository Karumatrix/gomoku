/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** PatternMatching
*/

#pragma once

#include <vector>
#include <algorithm>

#include "Positions.hpp"
#include "GameBoard.hpp"

class PatternMatching {
    public:
        PatternMatching();
        ~PatternMatching();

        Positions getBestPositions(GameBoard &board);
    private:
        std::vector<std::pair<Positions, Priority>> &checkVerticalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPositions);
        std::vector<std::pair<Positions, Priority>> &checkHorizontalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPositions);
        std::vector<std::pair<Positions, Priority>> &checkDiagonalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPositions);
        std::vector<std::pair<Positions, Priority>> &addToBestPositions(std::vector<std::pair<Positions, Priority>> &positions, std::vector<Positions> &tmp, int &nbCaseTaken);
};
