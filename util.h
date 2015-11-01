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
    std::string coups;

    PartieD() {};

    PartieD(std::string nam,std::string cps)
    {
        name=nam;

        coups=cps;
    };
};

namespace utility
{
    std::vector<std::string> split(std::string toSplit,std::string delimiter);

    int stoi(std::string value);



    std::vector<Partie> listeParties();

    std::vector<PartieD> listePartie();

    bool inPlateau(int x,int y);
}

class Ressources
{
    public:

    static sf::Font font;

    static sf::Texture textureBackground;

    static sf::Texture texturePiece;

    static sf::Texture textureButtonSave;

    static sf::Texture textureButtonBack;

    static void loadRessources()
    {
        font.loadFromFile("dreamwalker.ttf");

        textureBackground.loadFromFile("fischer.png");

        texturePiece.loadFromFile("chess.png");

        textureButtonSave.loadFromFile("save.png");

        textureButtonBack.loadFromFile("retour.png");
    }
};
