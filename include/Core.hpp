/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Core
*/

#pragma once

#include <algorithm>
#include <bitset>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "GameBoard.hpp"
#include "PatternMatching.hpp"
#include "MiniMax.hpp"

enum class GameType : size_t
{
    HUMAN = 0,
    BRAIN = 1,
    TOURNAMENT = 2,
    NETWORK_TOURNAMENT = 3
};

class Core {
    public:
        Core();
        ~Core();

        void run();
        void redirect_command(std::string &command);
        std::vector<std::string> split(std::string &s, const std::string delimiter);

    protected:
        void turnCommand(std::vector<std::string> &parsedCommand);
        void startCommand(std::vector<std::string> &parsedCommand);
        void beginCommand(std::vector<std::string> &parsedCommand);
        void boardCommand(std::vector<std::string> &parsedCommand);
        void infoCommand(std::vector<std::string> &parsedCommand);
        void endCommand(std::vector<std::string> &parsedCommand);
        void aboutCommand(std::vector<std::string> &parsedCommand);
        void rectstartCommand(std::vector<std::string> &parsedCommand);
        void restartCommand(std::vector<std::string> &parsedCommand);
        void takebackCommand(std::vector<std::string> &parsedCommand);
        void playCommand(std::vector<std::string> &parsedCommand);
        void swap2boardCommand(std::vector<std::string> &parsedCommand);

        bool isInteger(const std::string &str);
        bool runPatternMatching();

    private:
        bool _isRunning = true;
        bool _isMyTurn = false;
        bool _isGameStarted = false;
        GameBoard _board;
        PatternMatching _patternMatching;
        MiniMax _minimax;
        std::unordered_map<std::string, std::function<void(std::vector<std::string>&)>> _commands;

        std::string _name = "Platypus";
        std::string _version = "0.5";
        std::string _authors = "Babouuchee, Zelda_lol, Karumapathetic";
        std::string _country = "FR";

        int _timeout_turn = 0;
        int _timeout_match = 0;
        int _max_memory = 0;
        int _time_left = 0;
        GameType _game_type = GameType::BRAIN;
        std::bitset<4> _rule;
        Positions _evaluate = {0, 0};
        std::string _folder = "";
};
