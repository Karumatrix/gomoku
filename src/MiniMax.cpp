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
    if (result.empty() && _gameBoard.getCaseState(size / 2, size / 2) == GameCase::DEFAULT)
        result.push_back({size / 2, size / 2});
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

int MiniMax::PawnsNumber(int x, int y, int checkX, int checkY) {
    int count = 0, newX = 0, newY = 0;
    for (int i = 0; i < 5; i++) {
        newX = x + i * checkX;
        newY = y + i * checkY;
        if (_gameBoard.getCaseState(newX, newY) == GameCase::PLAYER)
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
            result += PawnsNumber(i, j, 1, 0);
            result += PawnsNumber(i, j, 0, 1);
            result += PawnsNumber(i, j, 1, 1);
            result += PawnsNumber(i, j, 1, -1);
        }
    }
    return result;
}

int MiniMax::evaluateBoard() {
    if (_isEnd) {
        if (checkWin(GameCase::PLAYER))
            return 10000;
        if (checkWin(GameCase::OPPONENT))
            return -10000;
        return 0;
    }
    return evaluation();
}

float MiniMax::minimax(int depth, bool playerMax, float alpha, float beta) {
    _isEnd = isEnd();
    std::pair<int, int> bestMove;
    if (depth == MAX_DEPTH || _isEnd)
        return _gameBoard.Evaluate() * (-1);
    if (playerMax) {
        float best = MIN_INT;
        float max = 0;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::PLAYER);
            max = minimax(depth + 1, false, alpha, beta);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
            best = std::max(best, max);
            alpha = std::max(alpha, best);
            if (beta <= alpha)
                break;
            if (best == max)
                bestMove = node;
        }
        if (depth == 0)
            _bestMove = bestMove;
        return best;
    } else {
        float best = MAX_INT;
        float min = 0;
        for (std::pair<int, int> node: getPossibleMoves()) {
            _gameBoard.setCaseState(node.first, node.second, GameCase::OPPONENT);
            min = minimax(depth + 1, true, alpha, beta);
            _gameBoard.setCaseState(node.first, node.second, GameCase::DEFAULT);
            best = std::min(best, min);
            beta = std::min(beta, best);
            if (beta <= alpha)
                break;
            if (best == min)
                bestMove = node;
        }
        if (depth == 0)
            _bestMove = bestMove;
        return best;
    }
}
