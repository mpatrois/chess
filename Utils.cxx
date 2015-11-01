//#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Utils.h"
#include "Piece.h"

namespace Utility
{
    std::vector<std::string> split(std::string toSplit,std::string delimiter)
    {
        std::vector<std::string> listString;

        size_t pos = 0;

        std::string token;

        while ((pos = toSplit.find(delimiter)) != std::string::npos)
        {
            token = toSplit.substr(0, pos);

            listString.push_back(token);

            toSplit.erase(0, pos + delimiter.length());
        }

        return listString;
    }

    int stoi(std::string value)
    {
        int returnValue;

        std::stringstream is(value);

        is >> returnValue;

        return returnValue;
    }

    std::vector<Partie> listePartie()
    {
        std::vector<Partie> listParties;

        std::string name;
        std::string blows;

        std::ifstream infile("Games.txt");

        while(infile >> name >> blows)
        {
            listParties.push_back(Partie(name,blows));
        }

        infile.close();

        return listParties;
    }

    bool inPlateau(int x,int y)
    {
        return (x>-1 && x<8 && y>-1 && y<8);
    }
}
