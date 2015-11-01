#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"
#include "King.h"
#include "Chessboard.h"

class Player
{
    public:

        Player();

        Player(const Player &j);

        Player(std::vector<std::string> listPieces);

        Player *adverse;

        virtual ~Player();

        std::vector<Piece *> getPieces()
        {
            return listePiecePlayer;
        };

        void perdPiece(Piece *p);

        void affichePieceJTerminal();

        void affichePieceJGraphique(sf::RenderWindow &app,Chessboard *e);

        void placer(Chessboard *e);

        virtual bool isWhite() const = 0 ;

        Case getPosKingPlayer()
        {
            return Case(kingPlayer->x(),kingPlayer->y());
        };

        virtual Player *clone()=0;

        bool isChessMath(Chessboard *e);

        bool move(int caseX,int caseY,Chessboard *e);

        bool isMovePossible(int caseX,int caseY,Chessboard *e);

        bool isEchec(Chessboard *e);

        bool willBeEchec(int caseX,int caseY);

        void setPlayerAdverse(Player *jAdverse)
        {
            adverse=jAdverse;
        };

        void savePlayer(std::ofstream &myfile)
        {
            for(unsigned int i=0; i<listePiecePlayer.size(); i++)
            {
                if(i!=0)
                {
                    myfile<<",";
                }
                myfile << listePiecePlayer[i]->typePiece() << "|" << listePiecePlayer[i]->x() << "|" << listePiecePlayer[i]->y();
            }
            myfile << std::endl;
        };

        std::vector<Case> listeMouvementPossible(Chessboard *e);

        bool viseCase(int x, int y,Chessboard *e);

        bool isCastleRight(Chessboard *e,int caseX,int caseY);

        bool canCastleRight(Chessboard *e);

        bool isCastleLeft(Chessboard *e,int caseX,int caseY);

        bool canCastleLeft(Chessboard *e);

        bool isEnPassantDkingte(Chessboard *e,int caseX,int caseY);

        bool canEnPassantDkingte(Chessboard *e);

        bool isEnPassantLeft(Chessboard *e,int caseX,int caseY);

        bool canEnPassantLeft(Chessboard *e);

        int getSens();

        void selectPiece(int x,int y,Chessboard *e);


    protected:

        std::vector<Piece *> listePiecePlayer;

        King* kingPlayer;

        Piece* pieceSelected;

    private:

        bool echec;

};

#endif // JOUEUR_H
