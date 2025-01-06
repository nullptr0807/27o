// preflop
// calculate the probability of each hand

#include "../../inc/poker.h"
#include <iostream>
#include <iomanip> // Include the iomanip library

int main()
{
    int round = 1000000;
    int num_player = 5;
    std::map<std::string, int> cnt_map;

    for (int i = 1; i <= round; i++)
    {
        o27::Deck deck;
        for (int j = 1; j <= num_player; j++)
        {
            o27::Hand hand;
            hand.GetHand(deck);
            //std::cout<< hand.to_string(o27::OutFormat::suited) << " ";
            cnt_map[hand.to_string(o27::OutFormat::suited)] += 1;
        }
        //std::cout << std::endl;
    }

    std::cout << std::fixed << std::setprecision(3);
    double tot = 0.0;
    for (auto const &hand : cnt_map)
    {
        tot += 100.0 * hand.second / (double)(round * num_player);
        std::cout << hand.first << " " << 100.0 * hand.second / (double)(round * num_player) << " %" << std::endl;
    }
    std::cout << "Total: " << tot << "%" << std::endl;

    // print a probability sheet
    // std::cout << "Hand\tProbability" << std::endl;
    // std::string ranks = "-23456789TJQKA";
    // for (auto const i : ranks)
    // {
    //     printf("%05c", i);
    //     for (auto const j : ranks)
    //     {

    //     }
    // }
}