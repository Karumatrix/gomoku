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
    _board.resize(newSize);
    for (auto line : _board) {
        line.resize(newSize);
        for (auto boardCase : line)
            boardCase = GameCase::DEFAULT;
    }
}

GameCase GameBoard::getCaseState(int x, int y) const
{
    return _board[x][y];
}