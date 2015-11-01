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
struct PartieD;

//#include "Utils.h"
/**
 * Declaration d'une classe modélisant une piece de jeu d'echec.
 */
class Player;

class Chessboard
{
private:
    /**
     * Les cases de l'chessboard
     */
    Piece* m_cases[ 64 ];

    Player *joueurs[2];

    int tour;

    sf::Font font;

    sf::Sprite spritePlayerEnCours;
    sf::Sprite spritePlateau;

    sf::Texture texturePlateau;

    std::vector<Coup> listeCoups;

public:

    /**
     * Constructeur par défaut.
     * Initialise à vide l'chessboard.
     */
    Chessboard();

    Chessboard(Partie p);

    Chessboard(PartieD p);

    Chessboard(Player *j1,Player *j2);

    ~Chessboard();

    /**
     * Recupere la piece situee sur une case.
     *
     * @param x un entier entre 1 et 8
     * @param y un entier entre 1 et 8
     *
     * @return 0 si aucune piece n'est sur cette case et un pointeur
     * vers une piece sinon.
     */
    Piece* getPiece( int x, int y );

    /**
     * Place une piece sur l'chessboard, aux coordonnees specifiees dans la piece.
     *
     * @param p un pointeur vers une piece
     *
     * @return 'true' si le placement s'est bien passe, 'false' sinon
     * (case occupee, coordonnees invalides, piece vide )
     */
    bool placer( Piece* p );

    /**
     * Deplace une piece sur l'chessboard, des coordonnees specifiees
     * dans la piece aux coordonnees x,y.
     *
     * @param p un pointeur vers une piece
     * @param x un entier entre 1 et 8
     * @param y un entier entre 1 et 8
     *
     * @return 'true' si le placement s'est bien passe, 'false' sinon
     * (case occupee, coordonnees invalides, piece vide, piece pas
     * presente au bon endkingt sur l'chessboard)
     */
    bool deplacer( Piece* p, int x, int y );

    /**
     * Enleve la piece situee sur une case (qui devient vide).
     *
     * @param x un entier entre 1 et 8
     * @param y un entier entre 1 et 8
     *
     * @return 0 si aucune piece n'est sur cette case et le pointeur
     * vers la piece enlevee sinon.
     */
    void enleverPiece( int x, int y );

    /**
     * Affiche l'chessboard avec des # pour les cases noires et . pour
     * les blanches si elles sont vides, et avec B pour les pieces
     * blanches et N pour les pieces noires.
     */
    void affiche();

    void afficheGraphique(sf::RenderWindow &app);

    bool click(int mx,int my);

    void setPlayer(Player *jB,Player *jN);

    void savePartie(std::string nameFile);

    Player *getAdverse(bool coulPlayer);

    void addCoup(Case cd,Case ca);

    Coup getLastBlow();

};

#endif // !defined Chessboard_h
