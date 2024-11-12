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
    if (x >= _size || y >= _size)
    {
        std::cout << "ERROR Positions given are out of bounds" << std::endl;
        return GameCase::OUTOFBOUND;
    }
    return _board[y * _size + x];
}

void GameBoard::setCaseState(int x, int y, GameCase state)
{
    if (x >= _size || y >= _size)
    {
        std::cout << "ERROR Positions given are out of bounds" << std::endl;
        return;
    }
    _board[y * _size + x] = state;
}

int GameBoard::evaluateLine(int x, int y, int dx, int dy)
{
    int consecutive = 0;
    int openEnds = 0;
    for (int i = 0; i < 5; ++i)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;

        if (nx < 0 || nx >= _size || ny < 0 || ny >= _size || getCaseState(nx, ny) != GameCase::PLAYER)
        {
            return 0;
        }
        ++consecutive;
    }
    int prevX = x - dx;
    int prevY = y - dy;
    int nextX = x + 5 * dx;
    int nextY = y + 5 * dy;
    if (prevX >= 0 && prevX < _size && prevY >= 0 && prevY < _size && getCaseState(prevX, prevY) == GameCase::DEFAULT)
    {
        ++openEnds;
    }
    if (nextX >= 0 && nextX < _size && nextY >= 0 && nextY < _size && getCaseState(nextX, nextY) == GameCase::DEFAULT)
    {
        ++openEnds;
    }
    if (consecutive == 5)
        return 10000;
    if (consecutive == 4 && openEnds > 0)
        return 1000;
    if (consecutive == 3 && openEnds > 0)
        return 100;
    if (consecutive == 2 && openEnds > 0)
        return 10;

    return 0;
}

float GameBoard::Evaluate()
{
    float score = 0.0f;
    for (int x = 0; x < _size; ++x)
    {
        for (int y = 0; y < _size; ++y)
        {
            if (getCaseState(x, y) == GameCase::PLAYER)
            {
                score += evaluateLine(x, y, 1, 0);
                score += evaluateLine(x, y, 0, 1);
                score += evaluateLine(x, y, 1, 1);
                score += evaluateLine(x, y, 1, -1);
            }
        }
    }
    return score;
}