/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** MiniMax
*/

#include "MiniMax.hpp"

MiniMax::MiniMax(GameBoard &gameboard) : _gameBoard(gameboard)
{
}

MiniMax::~MiniMax()
{
}

std::vector<std::pair<int, int>> MiniMax::getPossibleMoves() {
    std::vector<std::pair<int, int>> result;
    size_t size = _gameBoard.getSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            GameCase caseType = _gameBoard.getCaseState(i, j);
            if (caseType != GameCase::PLAYER && caseType != GameCase::OPPONENT)
                continue;
            for (int pamplemousse = -1; pamplemousse <= 1; pamplemousse++) {
                for (int papaye = -1; papaye <= 1; papaye++) {
                    if (pamplemousse == 0 && papaye == 0) continue;
                    GameCase neighborCaseType = _gameBoard.getCaseState(i + pamplemousse, j + papaye);
                    if (neighborCaseType == GameCase::DEFAULT) {
                        result.push_back({i + pamplemousse, j + papaye});
                    }
                }
            }
        }
    }
    return result;
}

bool MiniMax::isEnd() {
    bool playerWin = checkWin(GameCase::PLAYER), opponentWin = checkWin(GameCase::OPPONENT);
    if (playerWin || opponentWin || getPossibleMoves().empty())
        return true;
    return false;
}

bool MiniMax::checkWin(GameCase player) {
    for (int i = 0; i < _gameBoard.getSize(); ++i) {
        for (int j = 0; j < _gameBoard.getSize(); ++j) {
            if (checkDirection(i, j, 1, 0, player) ||
                checkDirection(i, j, 0, 1, player) ||
                checkDirection(i, j, 1, 1, player) ||
                checkDirection(i, j, 1, -1, player)) {
                return true;
            }
        }
    }
    return false;
}

bool MiniMax::checkDirection(int x, int y, int checkX, int checkY, GameCase player) {
    int newX = 0, newY = 0;
    for (int i = 0; i < 5; i++) {
        newX = x + i * checkX;
        newY = y + i * checkY;
        if (_gameBoard.getCaseState(newX, newY) != player)
            return false;
    }
    return true;
}

int MiniMax::evaluateBoard() {
    int result = 0;
    auto bestDefense = _patternMatching.getBestPositions(_gameBoard, GameCase::PLAYER, GameCase::OPPONENT);
    auto bestAttack = _patternMatching.getBestPositions(_gameBoard, GameCase::PLAYER, GameCase::OPPONENT);
    return result;
}

int MiniMax::minimax(int depth, bool playerMax) {
    if (depth == MAX_DEPTH || isEnd()) // || end (genre la fin du jeu)
        return evaluateBoard(); // temporary
    if (playerMax) {
        int maxInt = MIN_INT;
        int max = 0;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::PLAYER);
            max = minimax(depth + 1, false);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
            maxInt = std::max(maxInt, max);
        }
        return maxInt;
    } else {
        int minInt = MAX_INT;
        int min = 0;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::OPPONENT);
            min = minimax(depth + 1, true);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
            minInt = std::min(minInt, min);
        }
        return minInt;
    }
}
