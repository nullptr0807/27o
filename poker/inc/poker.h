#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <map>
#include <unordered_map>
#include <queue>

namespace o27
{
    enum class OutFormat
    {
        text,
        icon,
        suited
    };

    static std::map<std::string, std::string> suit_map = {
        {"Clubs", "♣"},
        {"Diamonds", "♦"},
        {"Hearts", "♥"},
        {"Spades", "♠"}
    };

    class Card
    {
    public:
        Card() : rank(""), suit("") {}
        Card(std::string r, std::string s) : rank(r), suit(s) {}

        std::string rank;
        std::string suit;

        bool operator<(const Card &o) const
        {
            return pokerRanks.at(rank) < pokerRanks.at(o.rank);
        }

        // TODO: support multiple output formats, e.g., "2 of Hearts", "2♥", etc.
        std::string to_string() const
        {
            return rank + " of " + suit; 
        }

        bool IsEmpty() const
        {
            return rank.empty() && suit.empty();
        }

    private:
        static const std::unordered_map<std::string, int> pokerRanks;
    };

    static const std::unordered_map<std::string, int> pokerRanks;
    
    class Deck
    {
    public:
        Deck(bool shuffle = true)
        {
            std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
            std::vector<std::string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};

            for (const auto &suit : suits)
            {
                for (const auto &rank : ranks)
                {
                    deck.emplace_back(Card(rank, suit));
                }
            }

            if (shuffle)
                Shuffle();
        }

        Card Deal();
        std::vector<Card> DealToPlayer();
        std::vector<Card> DealFlop();
        Card DealTurn();
        Card DealRiver();

        static Deck Copy(const Deck &deck)
        {
            Deck newDeck(false);
            newDeck.deck = deck.deck;
            return newDeck;
        }

    private:
        void Shuffle();
        std::deque<Card> deck;
    };


    class Hand
    {
    public:
        Hand() : l(Card("", "")), r(Card("", "")) {}

        Hand(Card c1, Card c2)
        {
            if (c1 < c2)
                std::swap(c1, c2);
            l = c1;
            r = c2;
        }

        bool GetCard(Deck &deck);
        bool GetHand(Deck &deck);
        void Sort();
        bool Suited() const
        {
            return l.suit == r.suit;
        }

        std::string to_string(OutFormat out = OutFormat::icon) const
        {
            if (out == OutFormat::text)
                return l.to_string() + " " + r.to_string();
            else if (out == OutFormat::icon)
            {
                return l.rank + suit_map[l.suit] + r.rank + suit_map[r.suit];
            }
            else if (out == OutFormat::suited)
            {
                return l.rank + r.rank + (Suited() ? "s" : "o");
            }
            else
                return "";
        }

    private:
        Card l, r;
    };
}
