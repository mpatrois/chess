#ifndef Piece_h
#define Piece_h

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
/**
 * Declaration d'une classe modélisant une piece de jeu d'check.
 */
class Chessboard;

struct Square
{
    int x;
    int y;

    Square(){};

    Square(int _x,int _y)
    {
        x=_x;
        y=_y;
    };
};

struct Blow{
    Square caseDepart;
    Square caseArrivee;

    Blow(){};

    Blow(Square cd,Square ca){
        caseDepart=cd;
        caseArrivee=ca;
    }
};

class Piece
{
    private:

        int m_x;

        int m_y;


    protected:

        bool m_white;

        sf::Sprite spritePiece;

    public:

        Piece();

        Piece(int x,int y,bool white);

        Piece(const Piece &p);

        virtual Piece *clone()=0;

        virtual ~Piece();

        void init( int x, int y, bool white );

        virtual void move( int x, int y ,Chessboard *e);

        int x();

        int y();

        bool isWhite();

        bool isBlack();

        void display();

        static sf::Texture texturePiece;

        static void initImage()
        {
            texturePiece.loadFromFile("ressources/chess.png");
        };

        virtual char typePiece() = 0;

        sf::Sprite getSprite()
        {
            return spritePiece;
        };

        void graphicDisplay(sf::RenderWindow &app)
        {
            spritePiece.setPosition(x()*60,y()*60);
            app.draw(spritePiece);
        }

        virtual std::vector<Square> availableMovements(Chessboard *e)=0;

};

#endif // !defined Piece_h
