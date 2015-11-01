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
    private:

        bool check;

    protected:

        std::vector<Piece *> playerPieces;

        King* kingPlayer;

        Piece* selectedPiece;

    public:

        Player *opponent;

        Player();

        Player(const Player &j);

        virtual ~Player();

        std::vector<Piece *> getPieces();

        void loosePiece(Piece *p);

        void affichePieceJTerminal();

        void displayPlayerPiece(sf::RenderWindow &app,Chessboard *e);

        void put(Chessboard *e);

        virtual bool isWhite() const = 0 ;

        Square getPosKingPlayer();

        virtual Player *clone() = 0;

        bool isChessMath(Chessboard *e);

        bool move(int caseX,int caseY,Chessboard *e);

        bool isMovePossible(int caseX,int caseY,Chessboard *e);

        bool isEchec(Chessboard *e);

        bool willBeEchec(int caseX,int caseY);

        void setPlayerAdverse(Player *jAdverse)
        {
            opponent=jAdverse;
        };

        void savePlayer(std::ofstream &myfile);

        std::vector<Square> listeMouvementPossible(Chessboard *e);

        bool viseCase(int x, int y,Chessboard *e);

        bool isCastleRight(Chessboard *e,int caseX,int caseY);

        bool canCastleRight(Chessboard *e);

        bool isCastleLeft(Chessboard *e,int caseX,int caseY);

        bool canCastleLeft(Chessboard *e);

        bool isEnPassantRight(Chessboard *e,int caseX,int caseY);

        bool canEnPassantRight(Chessboard *e);

        bool isEnPassantLeft(Chessboard *e,int caseX,int caseY);

        bool canEnPassantLeft(Chessboard *e);

        int getSens();

        void selectPiece(int x,int y,Chessboard *e);

};

#endif // JOUEUR_H
