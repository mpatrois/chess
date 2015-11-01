#ifndef Piece_h
#define Piece_h

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
/**
 * Declaration d'une classe modélisant une piece de jeu d'echec.
 */
class Chessboard;

struct Case
{
    int x;
    int y;

    Case(){};

    Case(int _x,int _y)
    {
        x=_x;
        y=_y;
    };
};

struct Coup{
    Case caseDepart;
    Case caseArrivee;

    Coup(){};

    Coup(Case cd,Case ca){
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

        virtual void move( int x, int y );

        int x();

        int y();

        bool isWhite();

        bool isBlack();

        void affiche();

        static sf::Texture texturePiece;

        static void initImage()
        {
            texturePiece.loadFromFile("ressources/chess.png");
        };

        virtual char typePiece()=0;

        sf::Sprite getSprite()
        {
            return spritePiece;
        };
        void afficheGraphique(sf::RenderWindow &app)
        {
            spritePiece.setPosition(x()*60,y()*60);
            app.draw(spritePiece);
        }

        virtual std::vector<Case> mouvementsPossible(Chessboard *e)=0;

};

#endif // !defined Piece_h
