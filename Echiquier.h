/**
 * Header de Echiquier.cxx
 *
 * @file Echiquier.h
 */

#if !defined Echiquier_h
#define Echiquier_h

#include "Piece.h"
#include "Joueur.h"
#include <vector>
#include <iostream>
#include <fstream>
struct Partie;

//#include "util.h"
/**
 * Declaration d'une classe modélisant une piece de jeu d'echec.
 */
class Joueur;

class Echiquier
{
private:
    /**
     * Les cases de l'echiquier
     */
    Piece* m_cases[ 64 ];

    Joueur *joueurs[2];

    int tour=0;

    sf::Font font;

    sf::Sprite spriteJoueurEnCours;
    sf::Sprite spritePlateau;

    sf::Texture texturePlateau;



public:

    /**
     * Constructeur par défaut.
     * Initialise à vide l'echiquier.
     */
    Echiquier();

    Echiquier(Partie p);

    Echiquier(Joueur *j1,Joueur *j2);

    ~Echiquier();

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
     * Place une piece sur l'echiquier, aux coordonnees specifiees dans la piece.
     *
     * @param p un pointeur vers une piece
     *
     * @return 'true' si le placement s'est bien passe, 'false' sinon
     * (case occupee, coordonnees invalides, piece vide )
     */
    bool placer( Piece* p );

    /**
     * Deplace une piece sur l'echiquier, des coordonnees specifiees
     * dans la piece aux coordonnees x,y.
     *
     * @param p un pointeur vers une piece
     * @param x un entier entre 1 et 8
     * @param y un entier entre 1 et 8
     *
     * @return 'true' si le placement s'est bien passe, 'false' sinon
     * (case occupee, coordonnees invalides, piece vide, piece pas
     * presente au bon endroit sur l'echiquier)
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
     * Affiche l'echiquier avec des # pour les cases noires et . pour
     * les blanches si elles sont vides, et avec B pour les pieces
     * blanches et N pour les pieces noires.
     */
    void affiche();

    void afficheGraphique(sf::RenderWindow &app);

    bool click(int mx,int my);

    void setJoueur(Joueur *jB,Joueur *jN);

    void savePartie(std::string nameFile);

};

#endif // !defined Echiquier_h

