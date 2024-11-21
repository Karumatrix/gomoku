/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** MiniMax
*/

#include "MiniMax.hpp"

MiniMax::MiniMax(GameBoard &gameboard) : _gameBoard(gameboard)
{
    _isEnd = false;
}

MiniMax::~MiniMax()
{
}

std::pair<int, int> MiniMax::getBestMove() {
    return _bestMove;
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
                        if (std::find(result.begin(), result.end(), std::make_pair(i + pamplemousse, j + papaye)) != result.end())
                            continue;
                        result.push_back({i + pamplemousse, j + papaye});
                    }
                }
            }
        }
    }
    if (result.empty() && _gameBoard.getCaseState(size / 2, size / 2) == GameCase::DEFAULT) {
        // std::cout << "DEBUG empty result." << std::endl;
        result.push_back({size / 2, size / 2});
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

int MiniMax::PawnsNumber(int x, int y, int checkX, int checkY, GameCase player) {
    int count = 0, newX = 0, newY = 0;
    for (int i = 0; i < 5; i++) {
        newX = x + i * checkX;
        newY = y + i * checkY;
        if (_gameBoard.getCaseState(newX, newY) == player)
            count += i + 1;
        else
            break;
    }
    return count;
}

int MiniMax::evaluation() {
    int result = 0;
    for (int i = 0; i < _gameBoard.getSize(); ++i) {
        for (int j = 0; j < _gameBoard.getSize(); ++j) {
            result += PawnsNumber(i, j, 1, 0, GameCase::PLAYER);
            result += PawnsNumber(i, j, 0, 1, GameCase::PLAYER);
            result += PawnsNumber(i, j, 1, 1, GameCase::PLAYER);
            result += PawnsNumber(i, j, 1, -1, GameCase::PLAYER);
        }
    }
    return result;
}

int MiniMax::evaluateBoard() {
    if (_isEnd) {
        if (checkWin(GameCase::PLAYER)) {
            // std::cout << "DEBUG yeah" << std::endl;
            return 10000;
        }
        if (checkWin(GameCase::OPPONENT)) {
            // std::cout << "DEBUG no" << std::endl;
            return -10000;
        }
        _isEnd = false;
        return 0;
    }
    return evaluation();
}

int MiniMax::minimax(int depth, bool playerMax) {
    _isEnd = isEnd();
    std::pair<int, int> bestMove;
    if (depth == MAX_DEPTH || _isEnd)
        return evaluateBoard();
    if (playerMax) {
        int maxInt = MIN_INT;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::PLAYER);
            int max = minimax(depth + 1, false);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
            maxInt = std::max(maxInt, max);
            if (maxInt == max)
                bestMove = node;
        }
        if (depth == 0) {
            _bestMove = bestMove;
            std::cout << "DEBUG max: " << std::to_string(maxInt) << std::endl;
        }
        return maxInt;
    } else {
        int minInt = MAX_INT;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::OPPONENT);
            int min = minimax(depth + 1, true);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
            minInt = std::min(minInt, min);
            if (minInt == min)
                bestMove = node;
        }
        if (depth == 0)
            _bestMove = bestMove;
        return minInt;
    }
}
