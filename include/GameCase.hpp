/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** GameCase
*/

#pragma once

#include <cstdint>

enum class GameCase : uint32_t {
    DEFAULT,
    PLAYER,
    OPPONENT,
    OUTOFBOUND
};
