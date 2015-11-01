#include "BlackPlayer.h"

BlackPlayer::BlackPlayer()
{
    listePiecePlayer.push_back(new Rook(0,0,false));
    listePiecePlayer.push_back(new Knight(1,0,false));
    listePiecePlayer.push_back(new Bishop(2,0,false));

    King *king=new King(4,0,false);
    kingPlayer=king;
    listePiecePlayer.push_back(kingPlayer);

    listePiecePlayer.push_back(new Queen(3,0,false));
    listePiecePlayer.push_back(new Bishop(5,0,false));
    listePiecePlayer.push_back(new Knight(6,0,false));
    listePiecePlayer.push_back(new Rook(7,0,false));

    for (int x=8; x<16; x++)
    {
        listePiecePlayer.push_back(new Pawn(x%8,1,false));
    }
};

BlackPlayer::BlackPlayer(std::vector<std::string> listPieces) : Player()
{
    for(unsigned int i=0; i<listPieces.size(); i++)
    {
        std::string typePiece=listPieces[i].substr(0,1);
        int x=Utility::stoi(listPieces[i].substr(2,1));
        int y=Utility::stoi(listPieces[i].substr(4,1));

        if(typePiece=="t" || typePiece=="T")
        {
            listePiecePlayer.push_back(new Rook(x,y,false));
        }
        else if(typePiece=="r" || typePiece=="R")
        {
            King *p=new King(x,y,false);
            listePiecePlayer.push_back(p);
            kingPlayer=p;
        }
        else if(typePiece=="q" || typePiece=="Q")
        {
            listePiecePlayer.push_back(new Queen(x,y,false));
        }
        else if(typePiece=="f" || typePiece=="F")
        {
            listePiecePlayer.push_back(new Bishop(x,y,false));
        }
        else if(typePiece=="c" || typePiece=="C")
        {
            listePiecePlayer.push_back(new Knight(x,y,false));
        }
        else if(typePiece=="p" || typePiece=="P")
        {
            listePiecePlayer.push_back(new Pawn(x,y,false));
        }
    }
}

BlackPlayer::~BlackPlayer() {}

BlackPlayer *BlackPlayer::clone()
{
    return new BlackPlayer(*this) ;
};

bool BlackPlayer::isWhite() const
{
    return false;
}
