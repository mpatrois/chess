#if !defined Piece_h
#define Piece_h

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
/**
 * Declaration d'une classe modélisant une piece de jeu d'echec.
 */
class Echiquier;

struct Case
{
    int x;
    int y;

    Case(int _x,int _y)
    {
        x=_x;
        y=_y;
    };
    ~Case() {};
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

        virtual Piece *Clone()=0;

        virtual ~Piece();

        void init( int x, int y, bool white );

        void move( int x, int y );

        int x();

        int y();

        bool isWhite();

        bool isBlack();

        void affiche();

        static sf::Texture texturePiece;

        static void initImage()
        {
            texturePiece.loadFromFile("chess.png");
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

        virtual std::vector<Case> mouvementsPossible(Echiquier *e)=0;
};

#endif // !defined Piece_h
