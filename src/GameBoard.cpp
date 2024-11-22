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

GameBoard::~GameBoard() {}

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

size_t GameBoard::getSize() const { return _size; }

GameCase GameBoard::getCaseState(int x, int y) const
{
    if (x >= _size || y >= _size)
    {
        return GameCase::OUTOFBOUND;
    }
    return _board[x][y];
}

void GameBoard::setCaseState(int x, int y, GameCase state)
{
    if (x >= _size || y >= _size)
    {
        return;
    }
    _board[x][y] = state;
}

int GameBoard::evaluateLine(int x, int y, int dx, int dy, GameCase player)
{
    int consecutive = 0;
    int openEnds = 0;

    for (int i = 0; i < 5; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx < 0 || nx >= _size || ny < 0 || ny >= _size) break;
        if (getCaseState(nx, ny) != player) break;                
        consecutive++;
    }
    int prevX = x - dx, prevY = y - dy;
    int nextX = x + 5 * dx, nextY = y + 5 * dy;
    if (prevX >= 0 && prevX < _size && prevY >= 0 && prevY < _size &&
        getCaseState(prevX, prevY) == GameCase::DEFAULT) {
        openEnds++;
    }
    if (nextX >= 0 && nextX < _size && nextY >= 0 && nextY < _size &&
        getCaseState(nextX, nextY) == GameCase::DEFAULT) {
        openEnds++;
    }
    if (consecutive == 5) return 10000;
    if (consecutive == 4 && openEnds > 0) return 1000;
    if (consecutive == 3 && openEnds > 0) return 100;
    if (consecutive == 2 && openEnds > 0) return 10;
    return 0;
}

float GameBoard::Evaluate() {
    float score = 0.0f;

    for (int x = 0; x < _size; x++) {
        for (int y = 0; y < _size; y++) {
            if (getCaseState(x, y) == GameCase::PLAYER) {
                score += evaluateLine(x, y, 1, 0, GameCase::PLAYER);   
                score += evaluateLine(x, y, 0, 1, GameCase::PLAYER);   
                score += evaluateLine(x, y, 1, 1, GameCase::PLAYER);   
                score += evaluateLine(x, y, 1, -1, GameCase::PLAYER);  
            } else if (getCaseState(x, y) == GameCase::OPPONENT) {
                score -= evaluateLine(x, y, 1, 0, GameCase::OPPONENT); 
                score -= evaluateLine(x, y, 0, 1, GameCase::OPPONENT); 
                score -= evaluateLine(x, y, 1, 1, GameCase::OPPONENT); 
                score -= evaluateLine(x, y, 1, -1, GameCase::OPPONENT);
            }
        }
    }

    return score;
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