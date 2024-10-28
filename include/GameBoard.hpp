/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** GameBoard
*/

#pragma once

#include <vector>

#include "GameCase.hpp"

class GameBoard {
    public:
        GameBoard();
        ~GameBoard();

        void resize(size_t newSize);

        GameCase getCaseState(int x, int y) const;

    protected:
    private:
        size_t size = 0;
        std::vector<std::vector<GameCase>> _board;
};
