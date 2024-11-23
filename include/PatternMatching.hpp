/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** PatternMatching
*/

#pragma once

#include <algorithm>
#include <vector>

#include "GameBoard.hpp"
#include "Positions.hpp"

class PatternMatching {
    public:
        PatternMatching();
        ~PatternMatching();

        std::pair<Positions, Priority> getBestPositions(GameBoard &board, GameCase defense, GameCase attack);
    private:
        std::vector<std::pair<Positions, Priority>> &checkVerticalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPositions, GameCase defense, GameCase attack);
        std::vector<std::pair<Positions, Priority>> &checkHorizontalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPositions, GameCase defense, GameCase attack);
        std::vector<std::pair<Positions, Priority>> &checkDiagonalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPositions, GameCase defense, GameCase attack);
        std::vector<std::pair<Positions, Priority>> &addToBestPositions(std::vector<std::pair<Positions, Priority>> &positions, std::vector<Positions> &tmp, int &nbCaseTaken);
};
