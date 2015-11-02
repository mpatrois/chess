#ifndef ChessboardView_h
#define ChessboardView_h

#include <SFML/Graphics.hpp>

class Chessboard;
class Player;
struct Partie;

class ChessboardView
{
    private:

    Chessboard *chessboardModel;

    sf::Sprite spritePieces;

    sf::Texture texturePiece;

    sf::Font font;

public:

    ChessboardView(Chessboard *chessB);

    ~ChessboardView();

    void graphicDisplay(sf::RenderWindow &app);

    void setModel(Chessboard *chessB);

    void drawJoueur(sf::RenderWindow &app,Player *player);

    Partie chargerPartie(sf::RenderWindow &app,sf::Sprite sprite,sf::Font font);

    int menu(sf::RenderWindow &app,sf::Sprite sprite,sf::Font font);

};



#endif // !defined
