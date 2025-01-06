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

        std::string to_string() const
        {
            return rank + " of " + suit; // Fixed: Now returns a string representing the card.
        }

        bool IsEmpty() const
        {
            return rank.empty() && suit.empty();
        }

    private:
        static const std::unordered_map<std::string, int> pokerRanks;
    };

    const std::unordered_map<std::string, int> Card::pokerRanks =
        {{"2", 1}, {"3", 2}, {"4", 3}, {"5", 4}, {"6", 5}, {"7", 6}, {"8", 7}, {"9", 8}, {"10", 9}, {"T", 9}, {"J", 10}, {"Q", 11}, {"K", 12}, {"A", 13}};

    class Deck
    {
    public:
        Deck(bool shuffle = true)
        {
            std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
            std::vector<std::string> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};

            for (const auto &suit : suits)
            {
                for (const auto &rank : ranks)
                {
                    deck.push_back(Card(rank, suit));
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

    private:
        Card l, r;
        void Sort();
    };
}
