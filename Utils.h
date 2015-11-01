#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>


struct Partie
{
    std::string name;

    std::string j1;

    std::string j2;

    int tour;

    Partie() {};

    Partie(std::string nam,int tou,std::string jo1,std::string jo2)
    {
        name=nam;

        tour=tou;

        j1=jo1;

        j2=jo2;
    };
};

struct PartieD
{
    std::string name;
    std::string blows;

    PartieD() {};

    PartieD(std::string nam,std::string cps)
    {
        name=nam;

        blows=cps;
    };
};

namespace Utility
{
    std::vector<std::string> split(std::string toSplit,std::string delimiter);

    int stoi(std::string value);

    std::vector<Partie> listeParties();

    std::vector<PartieD> listePartie();

    bool inPlateau(int x,int y);
}
