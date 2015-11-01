/**
 * Header de Chessboard.cxx
 *
 * @file Chessboard.h
 */

#ifndef Chessboard_h
#define Chessboard_h

#include "Piece.h"
#include "Utils.h"
#include <vector>
#include <iostream>
#include <fstream>

struct Partie;

//#include "Utils.h"
/**
 * Declaration d'une classe modélisant une piece de jeu d'check.
 */
class Player;

class Chessboard
{
private:
    /**
     * Les cases de l'chessboard
     */
    Piece* m_cases[ 64 ];

    Player *players[2];

    int tour;

    sf::Font font;

    sf::Sprite spriteCurrentPlayer;
    sf::Sprite spritePlateau;

    sf::Texture texturePlateau;

    std::vector<Blow> listeBlows;

public:

    /**
     * Constructeur par défaut.
     * Initialise à vide l'chessboard.
     */
    Chessboard();

    Chessboard(Partie p);

    Chessboard(Player *j1,Player *j2);

    ~Chessboard();

    /**
     * Recupere la piece situee sur une square.
     *
     * @param x un entier entre 1 et 8
     * @param y un entier entre 1 et 8
     *
     * @return 0 si aucune piece n'est sur cette square et un pointeur
     * vers une piece sinon.
     */
    Piece* getPiece( int x, int y );

    /**
     * Place une piece sur l'chessboard, aux coordonnees specifiees dans la piece.
     *
     * @param p un pointeur vers une piece
     *
     * @return 'true' si le placement s'est bien passe, 'false' sinon
     * (square occupee, coordonnees invalides, piece vide )
     */
    bool put( Piece* p );

    /**
     * Enleve la piece situee sur une square (qui devient vide).
     *
     * @param x un entier entre 1 et 8
     * @param y un entier entre 1 et 8
     *
     * @return 0 si aucune piece n'est sur cette square et le pointeur
     * vers la piece enlevee sinon.
     */
    void removePiece( int x, int y );

    /**
     * Affiche l'chessboard avec des # pour les cases noires et . pour
     * les blanches si elles sont vides, et avec B pour les pieces
     * blanches et N pour les pieces noires.
     */
    void display();

    void graphicDisplay(sf::RenderWindow &app);

    bool click(int mx,int my);

    void setPlayer(Player *jB,Player *jN);

    void savePartie(std::string nameFile);

    Player *getOpponent(bool coulPlayer);

    void addBlow(Square cd,Square ca);

    Blow getLastBlow();

};

#endif // !defined Chessboard_h
