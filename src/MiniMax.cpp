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

std::vector<int, int> MiniMax::getPossibleMoves() {
    size_t size = _gameBoard.getSize();
}

int MiniMax::minimax(int depth, bool playerMax, int value) {
    if (depth == MAX_DEPTH) // || end (genre la fin du jeu)
        return value; // temporary
    if (playerMax) { // Maximizing player
        int maxInt = MAX_INT;
        int max = minimax(depth + 1, false, value);
        maxInt = std::max(maxInt, max);
        return maxInt;
    } else { // Minimizing player
        int minInt = MIN_INT;
        int min = minimax(depth + 1, true, value);
        minInt = std::max(minInt, min);
        return minInt;
    }
}
