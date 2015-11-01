#ifndef JOUEUR_H
#define JOUEUR_H
#include "Piece.h"
#include "Roi.h"
#include "Echiquier.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

class Joueur
{
    public:

        Joueur();

        Joueur(const Joueur &j);

        Joueur(std::vector<std::string> listPieces);

        Joueur *adverse;

        virtual ~Joueur();

        std::vector<Piece *> getPieces()
        {
            return listePieceJoueur;
        };

        void perdPiece(Piece *p);

        void affichePieceJTerminal();

        void affichePieceJGraphique(sf::RenderWindow &app,Echiquier *e);

        void placer(Echiquier *e);

        virtual bool isWhite()=0;

        Case getPosRoiJoueur()
        {
            return Case(roiJoueur->x(),roiJoueur->y());
        };

        virtual Joueur *Clone()=0;

        bool isChessMath(Echiquier *e);

        bool move(int caseX,int caseY,Echiquier *e);

        bool isMovePossible(int caseX,int caseY,Echiquier *e);

        bool isEchec(Echiquier *e);

        bool willBeEchec(int caseX,int caseY);

        void setJoueurAdverse(Joueur *jAdverse)
        {
            adverse=jAdverse;
        };

        void saveJoueur(std::ofstream &myfile)
        {
            for(unsigned int i=0; i<listePieceJoueur.size(); i++)
            {
                if(i!=0)
                {
                    myfile<<",";
                }
                myfile << listePieceJoueur[i]->typePiece() << "|" << listePieceJoueur[i]->x() << "|" << listePieceJoueur[i]->y();
            }
            myfile << std::endl;
        };

        std::vector<Case> listeMouvementPossible(Echiquier *e);

        bool viseCase(int x, int y,Echiquier *e);

        bool isCastleRight(Echiquier *e,int caseX,int caseY);

        bool canCastleRight(Echiquier *e);

        bool isCastleLeft(Echiquier *e,int caseX,int caseY);

        bool canCastleLeft(Echiquier *e);

        bool isEnPassantDroite(Echiquier *e,int caseX,int caseY);

        bool canEnPassantDroite(Echiquier *e);

        bool isEnPassantLeft(Echiquier *e,int caseX,int caseY);

        bool canEnPassantLeft(Echiquier *e);

        int getSens();

        void selectPiece(int x,int y,Echiquier *e);


    protected:

        std::vector<Piece *> listePieceJoueur;

        Roi* roiJoueur;

        Piece* pieceSelected;

    private:

        bool echec;

};

#endif // JOUEUR_H
