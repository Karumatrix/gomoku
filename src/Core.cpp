/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Core
*/

#include "Core.hpp"

Core::Core() : _minimax(_board)
{
    _commands["TURN"] = std::bind(&Core::turnCommand, this, std::placeholders::_1);
    _commands["START"] = std::bind(&Core::startCommand, this, std::placeholders::_1);
    _commands["BEGIN"] = std::bind(&Core::beginCommand, this, std::placeholders::_1);
    _commands["BOARD"] = std::bind(&Core::boardCommand, this, std::placeholders::_1);
    _commands["INFO"] = std::bind(&Core::infoCommand, this, std::placeholders::_1);
    _commands["END"] = std::bind(&Core::endCommand, this, std::placeholders::_1);
    _commands["ABOUT"] = std::bind(&Core::aboutCommand, this, std::placeholders::_1);
    _commands["RECTSTART"] = std::bind(&Core::rectstartCommand, this, std::placeholders::_1);
    _commands["RESTART"] = std::bind(&Core::restartCommand, this, std::placeholders::_1);
    _commands["TAKEBACK"] = std::bind(&Core::takebackCommand, this, std::placeholders::_1);
    _commands["PLAY"] = std::bind(&Core::playCommand, this, std::placeholders::_1);
    _commands["SWAP2BOARD"] = std::bind(&Core::swap2boardCommand, this, std::placeholders::_1);
}

Core::~Core() {}

void Core::run()
{
    std::string commandBuf;
    bool positionFound = false;

    while (_isRunning) {
        commandBuf.clear();
        std::getline(std::cin, commandBuf);
        redirect_command(commandBuf);
        commandBuf.clear();
        if (_isRunning && _isGameStarted && _isMyTurn) {
            auto bestDefense = _patternMatching.getBestPositions(_board, GameCase::PLAYER, GameCase::OPPONENT);
            auto bestAttack = _patternMatching.getBestPositions(_board, GameCase::OPPONENT, GameCase::PLAYER);

            if (bestAttack.second.size == 4) {
                _board.setCaseState(bestAttack.first.x, bestAttack.first.y, GameCase::PLAYER);
                std::cout << bestAttack.first.x << "," << bestAttack.first.y << std::endl;
            } else if (bestDefense.second.size == 4) {
                _board.setCaseState(bestDefense.first.x, bestDefense.first.y, GameCase::PLAYER);
                std::cout << bestDefense.first.x << "," << bestDefense.first.y << std::endl;
            } else {
                if ((bestAttack.first.x == -1 && bestAttack.first.y == -1) && (bestDefense.first.x == -1 && bestDefense.first.y == -1)) {
                    _minimax.minimax(0, true, MIN_INT, MAX_INT);
                    auto move = _minimax.getBestMove();
                    std::cout << move.first << "," << move.second << std::endl;
                    _board.setCaseState(move.first, move.second, GameCase::PLAYER);
                } else {
                    if (bestAttack.second.nbAlreadyFound > bestDefense.second.nbAlreadyFound) {
                        _board.setCaseState(bestAttack.first.x, bestAttack.first.y, GameCase::PLAYER);
                        std::cout << bestAttack.first.x << "," << bestAttack.first.y << std::endl;
                    } else {
                        _board.setCaseState(bestDefense.first.x, bestDefense.first.y, GameCase::PLAYER);
                        std::cout << bestDefense.first.x << "," << bestDefense.first.y << std::endl;
                    }
                    if (positionFound)
                        break;
                }
            }
            positionFound = false;
            _isMyTurn = false;
        }
    }
}

void Core::redirect_command(std::string &command)
{
    std::replace(command.begin(), command.end(), '\r', '\0');
    std::vector<std::string> parsedCommand = split(command, " ");
    auto commandHandler = _commands.find(parsedCommand[0]);
    if (commandHandler == _commands.end())
        std::cout << "UNKNOW Command '" << parsedCommand[0] << "' is unknown" << std::endl;
    else
        commandHandler->second(parsedCommand);
}

bool Core::isInteger(const std::string &str)
{
    try {
        std::size_t pos;
        std::stoi(str, &pos);
        return pos == str.size();
    } catch (const std::invalid_argument &) {
        return false;
    } catch (const std::out_of_range &) {
        return false;
    }
}

std::vector<std::string> Core::split(std::string &s, const std::string delimiter)
{
    size_t pos_start = 0;
    size_t pos_end = 0;
    size_t delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    for (auto &str : res)
        str.resize(strlen(str.c_str()));
    return res;
}

void Core::turnCommand(std::vector<std::string> &parsedCommand)
{
    std::vector<std::string> positionsArg;

    if (parsedCommand.size() != 2) {
        std::cout << "ERROR Turn received too many or not enough arguments" << std::endl;
    } else {
        positionsArg = split(parsedCommand[1], ",");
        if (positionsArg.size() != 2 || !isInteger(positionsArg[0]) || !isInteger(positionsArg[1]))
            std::cout << "ERROR Coordinates must be two integers" << std::endl;
        else {
            _board.setCaseState(
                std::stoi(positionsArg[0]), std::stoi(positionsArg[1]), GameCase::OPPONENT);
            _isMyTurn = true;
        }
    }
}

void Core::startCommand(std::vector<std::string> &parsedCommand)
{
    if (parsedCommand.size() != 2) {
        std::cout << "ERROR Size not given" << std::endl;
    } else {
        int size = 0;
        if (!isInteger(parsedCommand[1])) {
            std::cout << "ERROR Size is not an integer" << std::endl;
        } else {
            size = std::stoi(parsedCommand[1]);
            if (size < 5 || size > 20)
                std::cout << "ERROR Size is too big or too small (min: 5, max: 20)" << std::endl;
            else {
                _board.resize(size);
                _isGameStarted = true;
                std::cout << "OK" << std::endl;
            }
        }
    }
}

void Core::beginCommand(std::vector<std::string> &parsedCommand) { _isMyTurn = true; }

void Core::boardCommand(std::vector<std::string> &parsedCommand)
{
    std::string tmpBuf = "";
    std::vector<std::string> parsedTmpBuf;

    while (1) {
        std::getline(std::cin, tmpBuf);
        std::replace(tmpBuf.begin(), tmpBuf.end(), '\r', '\0');
        if (tmpBuf == "DONE")
            break;
        parsedTmpBuf = split(tmpBuf, ",");
        if (parsedTmpBuf.size() != 3 || !isInteger(parsedTmpBuf[0]) ||
            !isInteger(parsedTmpBuf[1]) || !isInteger(parsedTmpBuf[2]))
            std::cout << "ERROR Board cell given is not valid" << std::endl;
        else {
            switch (std::stoi(parsedTmpBuf[2])) {
            case 1:
                _board.setCaseState(
                    std::stoi(parsedTmpBuf[0]), std::stoi(parsedTmpBuf[1]), GameCase::PLAYER);
                break;
            case 2:
                _board.setCaseState(
                    std::stoi(parsedTmpBuf[0]), std::stoi(parsedTmpBuf[1]), GameCase::OPPONENT);
                break;
            default:
                std::cout << "ERROR Stone owner is not known" << std::endl;
                break;
            }
        }
    }
    _isGameStarted = true;
    _isMyTurn = true;
}

void Core::infoCommand(std::vector<std::string> &parsedCommand)
{
    std::string key;
    if (parsedCommand.size() != 3) {
        std::cout << "ERROR Info has " << (parsedCommand.size() < 3 ? "not enough arguments" : "too many arguments") << std::endl;
        return;
    }
    key = parsedCommand[1];
    if (key == "timeout_turn") {
        if (!isInteger(parsedCommand[2]))
            std::cout << "ERROR Value is not an integer" << std::endl;
        else
            _timeout_turn = std::stoi(parsedCommand[2]);
    } else if (key == "timeout_match") {
        if (!isInteger(parsedCommand[2]))
            std::cout << "ERROR Value is not an integer" << std::endl;
        else
            _timeout_match = std::stoi(parsedCommand[2]);
    } else if (key == "max_memory") {
        if (!isInteger(parsedCommand[2]))
            std::cout << "ERROR Value is not an integer" << std::endl;
        else
            _max_memory = std::stoi(parsedCommand[2]);
    } else if (key == "time_left") {
        if (!isInteger(parsedCommand[2]))
            std::cout << "ERROR Value is not an integer" << std::endl;
        else
            _time_left = std::stoi(parsedCommand[2]);
    } else if (key == "game_type") {
        if (!isInteger(parsedCommand[2]))
            std::cout << "ERROR Value is not an integer" << std::endl;
        else {
            int gameType = std::stoi(parsedCommand[2]);
            switch (gameType) {
            case 0:
                _game_type = GameType::HUMAN;
                break;
            case 1:
                _game_type = GameType::BRAIN;
                break;
            case 2:
                _game_type = GameType::TOURNAMENT;
                break;
            case 3:
                _game_type = GameType::NETWORK_TOURNAMENT;
                break;
            default:
                std::cout << "ERROR This game_type does not exists" << std::endl;
                break;
            }
        }
    } else if (key == "rule") {
        if (!isInteger(parsedCommand[2]))
            std::cout << "ERROR Value is not an integer" << std::endl;
        else {
            int bitmask = std::stoi(parsedCommand[2]);
            if (bitmask != 1 && bitmask != 2 && bitmask != 4 && bitmask != 8)
                std::cout << "ERROR Invalid bitmask" << std::endl;
            else {
                _rule ^= bitmask;
            }
        }
    } else if (key == "evaluate") {
        std::vector<std::string> posArg = split(parsedCommand[2], ",");
        if (posArg.size() != 2)
            std::cout << "ERROR Evaluate does not have two positions" << std::endl;
        else {
            if (!isInteger(posArg[0]) || !isInteger(posArg[1]))
                std::cout << "ERROR Coordinates is not an integer" << std::endl;
            else {
                _evaluate.x = std::stoi(posArg[0]);
                _evaluate.y = std::stoi(posArg[1]);
            }
        }
    } else if (key == "folder") {
        _folder = parsedCommand[2];
    } else {
        std::cout << "ERROR Info '" << key << "' is not known" << std::endl;
    }
}

void Core::endCommand(std::vector<std::string> &parsedCommand) { _isRunning = false; }

void Core::aboutCommand(std::vector<std::string> &parsedCommand)
{
    std::cout << "name=\"" << _name << "\", version=\"" << _version << "\", author=\"" << _authors << "\", country=\"" << _country << "\"" << std::endl;
}

void Core::rectstartCommand(std::vector<std::string> &parsedCommand)
{
    std::cout << "UNKNOW Command '" << parsedCommand[0] << "' is unknown" << std::endl;
}

void Core::restartCommand(std::vector<std::string> &parsedCommand)
{
    std::cout << "UNKNOW Command '" << parsedCommand[0] << "' is unknown" << std::endl;
}

void Core::takebackCommand(std::vector<std::string> &parsedCommand)
{
    std::cout << "UNKNOW Command '" << parsedCommand[0] << "' is unknown" << std::endl;
}

void Core::playCommand(std::vector<std::string> &parsedCommand)
{
    std::cout << "UNKNOW Command '" << parsedCommand[0] << "' is unknown" << std::endl;
}

void Core::swap2boardCommand(std::vector<std::string> &parsedCommand)
{
    std::cout << "UNKNOW Command '" << parsedCommand[0] << "' is unknown" << std::endl;
}
