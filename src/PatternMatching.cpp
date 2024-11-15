/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** PatternMatching
*/

#include "PatternMatching.hpp"

PatternMatching::PatternMatching()
{
}

PatternMatching::~PatternMatching()
{
}

Positions PatternMatching::getBestPositions(GameBoard &board)
{
    size_t boardSize = board.getSize();
    Positions bestPos = {-1, -1};
    int nbWeaknessFound = 0;

    for (int x = 0; x < boardSize - 5; x++) {
        for (int y = 0; y < boardSize - 5; y++) {
                if (checkDiagonalWeakness(x, y, boardSize))
                    nbWeaknessFound += 1;
                if (checkHorizontalWeakness(x, y, boardSize))
                    nbWeaknessFound += 1;
                if (checkVerticalWeakness(x, y, boardSize))
                    nbWeaknessFound += 1;
        }
    }
}

bool PatternMatching::checkVerticalWeakness(int x, int y, size_t size)
{

}

bool PatternMatching::checkHorizontalWeakness(int x, int y, size_t size)
{

}

bool PatternMatching::checkDiagonalWeakness(int x, int y, size_t size)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i >= size || j >= size)
                continue;
        }
    }
}
