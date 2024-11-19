/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** GameBoard
*/

#pragma once

#include <array>
#include <iostream>

#include "GameCase.hpp"

class GameBoard {
    public:
        GameBoard();
        ~GameBoard();

        void resize(size_t newSize);
        size_t getSize() const;

        GameCase getCaseState(int x, int y) const;
        void setCaseState(int x, int y, GameCase state);
        float Evaluate();

        void printBoard() const;

        void printBoard() const;

    protected:
    private:
        size_t _size = 0;
        int evaluateLine(int x, int y, int dx, int dy);
        std::array<std::array<GameCase, 20>, 20> _board;
};
