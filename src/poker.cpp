#include <algorithm>
#include <random>
#include <chrono>

#include "../inc/poker.h"

namespace o27
{
    bool Hand::GetCard(Deck &deck)
    {
        if (l.IsEmpty())
            l = deck.Deal();
        else if (r.IsEmpty())
            r = deck.Deal();
        else
        {
            throw std::exception("Hand is full, cannot deal more cards");
        }

        return true;
    }

    bool Hand::GetHand(Deck &deck)
    {
        if (l.IsEmpty() && r.IsEmpty())
        {
            l = deck.Deal();
            r = deck.Deal();
        }
        else if (l.IsEmpty())
        {
            l = deck.Deal();
        }
        else if (r.IsEmpty())
        {
            r = deck.Deal();
        }
        else
        {
            throw std::exception("Hand is full, cannot deal more cards");
        }

        return true;
    }

    void Hand::Sort()
    {
        if (l < r)
            std::swap(l, r);
    }

    void Deck::Shuffle()
    {
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    }

    Card Deck::Deal()
    {
        if (deck.empty())
        {
            throw std::exception("Deck is empty, cannot deal");
        }

        Card c = deck.front();
        deck.pop_front();
        return c;
    }

    std::vector<Card> Deck::DealToPlayer()
    {
        std::vector<Card> hand;
        hand.push_back(Deal());
        hand.push_back(Deal());

        return hand;
    }

    std::vector<Card> Deck::DealFlop()
    {
        deck.pop_front();

        std::vector<Card> flop;
        for (int num = 0; num < 3; num++)
            flop.push_back(Deal());

        return flop;
    }

    Card Deck::DealTurn()
    {
        deck.pop_front();

        return Deal();
    }

    Card Deck::DealRiver()
    {
        deck.pop_front();

        return Deal();
    }
}