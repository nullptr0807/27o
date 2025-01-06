#include "poker.h"
#include <iostream>
#include <fstream>
#include <string>

namespace o27
{
    class PokerHandRecord
    {
    public:
        std::string handID;
        std::string gameType;
        std::string dateTime;
        std::string tableName;
        int buttonSeat;
        std::vector<std::pair<int, double>> players;
        std::vector<std::string> holeCards;
        std::vector<std::string> communityCards;
        std::vector<std::string> actions;
        double potSize;
        double rake;
        std::string board;

    public:
        PokerHandRecord() {}
        PokerHandRecord(std::string id, std::string type, std::string date, std::string table, int button)
            : handID(id), gameType(type), dateTime(date), tableName(table), buttonSeat(button) {}

        bool empty()
        {
        }

        void clear()
        {
        }

        void addPlayer(int seat, double chips)
        {
            players.push_back({seat, chips});
        }

        void setHoleCards(std::vector<std::string> cards)
        {
            holeCards = cards;
        }

        void setCommunityCards(std::vector<std::string> cards)
        {
            communityCards = cards;
        }

        void addAction(std::string action)
        {
            actions.push_back(action);
        }

        void setPotSize(double pot)
        {
            potSize = pot;
        }

        void setRake(double rakeAmount)
        {
            rake = rakeAmount;
        }

        void setBoard(std::string boardCards)
        {
            board = boardCards;
        }

        // Add other methods to manipulate and retrieve the data as needed
    };

    class Reader
    {
    public:
        virtual std::vector<PokerHandRecord> ReadPokerHistoryFromFile(std::string filePath) = 0;
    };

    class GGPokerReader : public Reader
    {
        std::vector<PokerHandRecord> ReadPokerHistoryFromFile(std::string filePath)
        {
            std::vector<PokerHandRecord> pokerHistory;

            std::ifstream file(filePath);
            if (!file.is_open())
            {
                throw("Cannot open file %s", filePath.c_str());
            }

            // Read the file line by line
            std::string line;
            PokerHandRecord record;
            std::vector<std::string> rawLines;
            while (std::getline(file, line))
            {
                if (line.find("Poker Hand") != std::string::npos)
                {
                    if (!record.empty())
                    {
                        pokerHistory.push_back(record);
                    }
                    else
                    {
                        rawLines.clear();
                        record.clear();
                    }
                }

                if (line != "")
                {
                    rawLines.push_back(line);
                }

                // Process each line and create PokerHandRecord objects
                // ...

                // Add the created PokerHandRecord object to the vector
                // pokerHistory.push_back(pokerHandRecord);
            }

            // Close the file
            file.close();

            return pokerHistory;
        }
    }
}