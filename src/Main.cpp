/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** main
*/

#include <iostream>

#include "Core.hpp"

int main(int argc, char const *const *argv)
{
    if (argc > 2 && (argv[1] == "-h" || argv[1] == "--help")) {
        std::cout << "Usage: ./pbrain-gomoku-ai" << std::endl;
        return 0;
    }
    Core core;
    core.run();
    return 0;
}