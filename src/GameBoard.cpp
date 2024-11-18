/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** GameBoard
*/

#include "GameBoard.hpp"

GameBoard::GameBoard()
{
    for (auto &line : _board)
        std::fill(line.begin(), line.end(), GameCase::DEFAULT);
}

GameBoard::~GameBoard()
{
}

void GameBoard::resize(size_t newSize)
{
    if (newSize > 20 || newSize < 0) {
        std::cout << "ERROR - Size \"" << newSize << "\" is invalid" << std::endl;
        return;
    }
    for (auto &line : _board)
        std::fill(line.begin(), line.end(), GameCase::DEFAULT);
    _size = newSize;
}

size_t GameBoard::getSize() const
{
    return _size;
}

GameCase GameBoard::getCaseState(int x, int y) const
{
    if (x >= _size || y >= _size) {
        return GameCase::OUTOFBOUND;
    }
    return _board[x][y];
}

void GameBoard::setCaseState(int x, int y, GameCase state)
{
    if (x >= _size || y >= _size) {
        return;
    }
    _board[x][y] = state;
}

void GameBoard::printBoard() const
{
    std::cout << "DEBUG Board: " << std::endl;
    for (auto &line : _board) {
        std::cout << "DEBUG ";
        for (auto &state : line) {
            switch (state) {
                case GameCase::OPPONENT:
                    std::cout << "O";
                    break;
                case GameCase::PLAYER:
                    std::cout << "P";
                    break;
                case GameCase::DEFAULT:
                    std::cout << ".";
                    break;
                default:
                    break;
            }
        }
        std::cout << std::endl;
    }
}