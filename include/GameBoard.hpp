/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** GameBoard
*/

#pragma once

#include <vector>
#include <iostream>

#include "GameCase.hpp"

class GameBoard {
    public:
        GameBoard();
        ~GameBoard();

        void resize(size_t newSize);

        GameCase getCaseState(int x, int y) const;
        void setCaseState(int x, int y, GameCase state);

    protected:
    private:
        size_t _size = 0;
        std::vector<GameCase> _board;
};
