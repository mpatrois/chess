#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>

struct Partie
{
    std::string name;
    std::string blows;

    Partie() {};

    Partie(std::string nam,std::string cps)
    {
        name=nam;

        blows=cps;
    };
};

namespace Utility
{
    std::vector<std::string> split(std::string toSplit,std::string delimiter);

    int stoi(std::string value);

    std::vector<Partie> listePartie();

    bool inChessboard(int x,int y);
}
