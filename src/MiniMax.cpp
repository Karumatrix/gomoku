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
                    if (pamplemousse == 0 && papaye == 0) continue; // Skip the current tile
                    int newI = i + pamplemousse;
                    int newJ = j + papaye;
                    GameCase neighborCaseType = _gameBoard.getCaseState(newI, newJ);
                    if (neighborCaseType == GameCase::DEFAULT) {
                        result.push_back({newI, newJ});
                    }
                }
            }
        }
    }
    return result;
}

int MiniMax::minimax(int depth, bool playerMax, int value) {
    if (depth == MAX_DEPTH) // || end (genre la fin du jeu)
        return value; // temporary
    if (playerMax) {
        int maxInt = MAX_INT;
        int max = 0;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::PLAYER);
            max = minimax(depth + 1, false, value);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
        }
        maxInt = std::max(maxInt, max);
        return maxInt;
    } else {
        int minInt = MIN_INT;
        int min = 0;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::OPPONENT);
            min = minimax(depth + 1, true, value);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
        }
        minInt = std::min(minInt, min);
        return minInt;
    }
}
