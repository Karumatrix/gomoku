/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Core
*/

#pragma once

#include "GameBoard.hpp"

class Core {
    public:
        Core();
        ~Core();

        void run();

    protected:
    private:
        GameBoard _board;
};
