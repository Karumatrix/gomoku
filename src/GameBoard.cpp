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
        if (getCaseState(nx, ny) == GameCase::DEFAULT) continue;
        if (getCaseState(nx, ny) != player) break;
        consecutive++;
    }
    int prevX = x - dx, prevY = y - dy;
    int nextX = x + consecutive * dx, nextY = y + consecutive * dy;
    if (getCaseState(prevY, prevX) == GameCase::DEFAULT)
        openEnds++;
    if (getCaseState(nextY, nextX) == GameCase::DEFAULT)
        openEnds++;

    if (consecutive == 5) return 10000;
    if (consecutive == 4) return 1000 * openEnds;
    if (consecutive == 3) return 100 * openEnds;
    if (consecutive == 2) return 10 * openEnds;
    if (consecutive == 1) return openEnds;
    return 0;
}

int GameBoard::Evaluate(GameCase currPlayer) {
    int score = 0.0f;

    GameCase currOpponent = currPlayer == GameCase::PLAYER ? GameCase::OPPONENT : GameCase::PLAYER;
    for (int x = 0; x < _size; x++) {
        for (int y = 0; y < _size; y++) {
            if (getCaseState(x, y) == currPlayer) {
                score += evaluateLine(x, y, 1, 0, currPlayer);
                score += evaluateLine(x, y, 0, 1, currPlayer);
                score += evaluateLine(x, y, 1, 1, currPlayer);
                score += evaluateLine(x, y, 1, -1, currPlayer);
            } else if (getCaseState(x, y) == currOpponent) {
                score -= evaluateLine(x, y, 1, 0, currOpponent);
                score -= evaluateLine(x, y, 0, 1, currOpponent);
                score -= evaluateLine(x, y, 1, 1, currOpponent);
                score -= evaluateLine(x, y, 1, -1, currOpponent);
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