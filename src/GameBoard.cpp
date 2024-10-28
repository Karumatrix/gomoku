/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** GameBoard
*/

#include "GameBoard.hpp"

GameBoard::GameBoard()
{
}

GameBoard::~GameBoard()
{
}

void GameBoard::resize(size_t newSize)
{
    _board.clear();
    _board.resize(newSize * newSize, GameCase::DEFAULT);
    _size = newSize;
}

size_t GameBoard::getSize() const
{
    return _size;
}

GameCase GameBoard::getCaseState(int x, int y) const
{
    if (x >= _size || y >= _size) {
        std::cout << "ERROR Positions given are out of bounds" << std::endl;
        return GameCase::OUTOFBOUND;
    }
    return _board[y * _size + x];
}

void GameBoard::setCaseState(int x, int y, GameCase state)
{
    if (x >= _size || y >= _size) {
        std::cout << "ERROR Positions given are out of bounds" << std::endl;
        return;
    }
    _board[y * _size + x] = state;
}
