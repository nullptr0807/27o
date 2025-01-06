#pragma once
#include <iostream>
#include <cstdint>
#include <string>
#include <optional>
#include "poker.h"

namespace o27
{
    class Action
    {
    public:
        enum class Type
        {
            Unknown,
            Ante,
            Straddle,
            Fold,
            Check,
            Call,
            Bet,
            Raise,
            AllIn
        };

        Action() {}
        Action(Type t, std::optional<double> v = std::nullopt) : type(t), value(v) {}
        std::optional<double> value;
        Type type;
    };

    class PlayerStats
    {
    };

    class Player
    {
    public:
        Player() {}
        std::string playerID;
        std::string playerName;
        double playerStack;
        Hand playerHand;
    };

    class Holdem
    {
    public:
        std::uint8_t playerNum;

        Holdem() {}
        Holdem(std::uint8_t playerNum) : playerNum(playerNum) {}

        enum class Phase
        {
            Prepare,
            PreFlop,
            Flop,
            Turn,
            River,
            Showdown,
            Finish
        }
    };
}