/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** PatternMatching
*/

#include "PatternMatching.hpp"

PatternMatching::PatternMatching() {}

PatternMatching::~PatternMatching() {}

std::pair<Positions, Priority> PatternMatching::getBestPositions(GameBoard &board, GameCase defense, GameCase attack)
{
    std::vector<std::pair<Positions, Priority>> bestPos;
    size_t boardSize = board.getSize();

    for (int x = 0; x < boardSize - 3; x++) {
        for (int y = 0; y < boardSize - 3; y++) {
            bestPos = checkDiagonalWeakness(x, y, board, bestPos, defense, attack);
            bestPos = checkHorizontalWeakness(x, y, board, bestPos, defense, attack);
            bestPos = checkVerticalWeakness(x, y, board, bestPos, defense, attack);
        }
    }
    if (bestPos.size() == 0)
        return {{-1, -1}, {-1, -1}};
    std::sort(bestPos.begin(), bestPos.end(), [](const std::pair<Positions, Priority> &elem1, const std::pair<Positions, Priority> &elem2) {
        if (elem1.second.size != elem2.second.size)
            return elem1.second.size > elem2.second.size;
        return elem1.second.nbAlreadyFound > elem2.second.nbAlreadyFound;
    });
    return bestPos.at(0);
}

std::vector<std::pair<Positions, Priority>> &PatternMatching::checkVerticalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPos, GameCase defense, GameCase attack)
{
    int nbCaseTaken = 0;
    std::vector<Positions> tmpPos;

    for (int i = 0; i < 5; i++) {
        if (board.getCaseState(x + i, y) == defense || board.getCaseState(x + i, y) == GameCase::OUTOFBOUND)
            return bestPos;
        if (board.getCaseState(x + i, y) == attack)
            nbCaseTaken += 1;
        if (board.getCaseState(x + i, y) == GameCase::DEFAULT)
            tmpPos.push_back({x + i, y});
    }
    if (nbCaseTaken >= 3 && tmpPos.size() > 0)
        bestPos = addToBestPositions(bestPos, tmpPos, nbCaseTaken);
    return bestPos;
}

std::vector<std::pair<Positions, Priority>> &PatternMatching::checkHorizontalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPos, GameCase defense, GameCase attack)
{
    int nbCaseTaken = 0;
    std::vector<Positions> tmpPos;

    for (int i = 0; i < 5; i++) {
        if (board.getCaseState(x, y + i) == defense || board.getCaseState(x + i, y) == GameCase::OUTOFBOUND)
            return bestPos;
        if (board.getCaseState(x, y + i) == attack)
            nbCaseTaken += 1;
        if (board.getCaseState(x, y + i) == GameCase::DEFAULT)
            tmpPos.push_back({x, y + i});
    }
    if (nbCaseTaken >= 3 && tmpPos.size() > 0)
        bestPos = addToBestPositions(bestPos, tmpPos, nbCaseTaken);
    return bestPos;
}

std::vector<std::pair<Positions, Priority>> &PatternMatching::checkDiagonalWeakness(int x, int y, GameBoard &board, std::vector<std::pair<Positions, Priority>> &bestPos, GameCase defense, GameCase attack)
{
    int nbCaseTaken = 0;
    std::vector<Positions> tmpPos;

    for (int i = 0; i < 5; i++) {
        if (board.getCaseState(x + i, y + i) == defense || board.getCaseState(x + i, y) == GameCase::OUTOFBOUND) {
            tmpPos.clear();
            break;
        }
        if (board.getCaseState(x + i, y + i) == attack)
            nbCaseTaken += 1;
        if (board.getCaseState(x + i, y + i) == GameCase::DEFAULT)
            tmpPos.push_back({x + i, y + i});
    }
    if (nbCaseTaken >= 3 && tmpPos.size() > 0)
        bestPos = addToBestPositions(bestPos, tmpPos, nbCaseTaken);
    nbCaseTaken = 0;
    tmpPos.clear();
    for (int i = 4; i >= 0; i--) {
        if (board.getCaseState(x + (4 - i), y + i) == defense || board.getCaseState(x + i, y) == GameCase::OUTOFBOUND)
            return bestPos;
        if (board.getCaseState(x + (4 - i), y + i) == attack)
            nbCaseTaken += 1;
        if (board.getCaseState(x + (4 - i), y + i) == GameCase::DEFAULT)
            tmpPos.push_back({x + (4 - i), y + i});
    }
    if (nbCaseTaken >= 3 && tmpPos.size() > 0)
        bestPos = addToBestPositions(bestPos, tmpPos, nbCaseTaken);
    return bestPos;
}

std::vector<std::pair<Positions, Priority>> &PatternMatching::addToBestPositions(std::vector<std::pair<Positions, Priority>> &positions, std::vector<Positions> &tmp, int &nbCaseTaken)
{
    for (auto &pos : tmp) {
        auto it = std::find_if(
            positions.begin(), positions.end(), [pos](std::pair<Positions, Priority> &posToCheck) {
                if (posToCheck.first.x == pos.x && posToCheck.first.y == pos.y)
                    return true;
                return false;
            });
        if (it == positions.end()) {
            positions.push_back({{pos.x, pos.y}, {nbCaseTaken, 1}});
        } else {
            it->second.nbAlreadyFound += 1;
            if (nbCaseTaken == 4)
                it->second.size = 4;
        }
    }
    return positions;
}
