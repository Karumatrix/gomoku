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
    int evaluateLine(int x, int y, int dx, int dy, GameCase player);
    int Evaluate(GameCase currPlayer);

    void printBoard() const;
    std::pair<int, int> findFirstPosFree() const;

    protected:
    private:
        size_t _size = 0;
        std::array<std::array<GameCase, 20>, 20> _board;
};
