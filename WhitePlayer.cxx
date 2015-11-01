#include "WhitePlayer.h"

WhitePlayer::WhitePlayer():Player()
{
    playerPieces.push_back(new Rook(0,7,true));
    playerPieces.push_back(new Knight(1,7,true));
    playerPieces.push_back(new Bishop(2,7,true));

    King *king=new King(4,7,true);
    kingPlayer=king;
    playerPieces.push_back(kingPlayer);

    playerPieces.push_back(new Queen(3,7,true));
    playerPieces.push_back(new Bishop(5,7,true));
    playerPieces.push_back(new Knight(6,7,true));
    playerPieces.push_back(new Rook(7,7,true));

    for (int x=8; x<16; x++)
    {
        playerPieces.push_back(new Pawn(x%8,6,true));
    }

};
WhitePlayer::WhitePlayer(std::vector<std::string> listPieces):Player()
{
    for(unsigned int i=0; i<listPieces.size(); i++)
    {
        std::string typePiece=listPieces[i].substr(0,1);
        int x=Utility::stoi(listPieces[i].substr(2,1));
        int y=Utility::stoi(listPieces[i].substr(4,1));

        if(typePiece=="t" || typePiece=="T")
        {
            playerPieces.push_back(new Rook(x,y,true));
        }
        else if(typePiece=="r" || typePiece=="R")
        {
            King *p=new King(x,y,true);
            playerPieces.push_back(p);
            kingPlayer=p;
        }
        else if(typePiece=="q" || typePiece=="Q")
        {
            playerPieces.push_back(new Queen(x,y,true));
        }
        else if(typePiece=="f" || typePiece=="F")
        {
            playerPieces.push_back(new Bishop(x,y,true));
        }
        else if(typePiece=="c" || typePiece=="C")
        {
            playerPieces.push_back(new Knight(x,y,true));
        }
        else if(typePiece=="p" || typePiece=="P")
        {
            playerPieces.push_back(new Pawn(x,y,true));
        }
    }
};
WhitePlayer::~WhitePlayer() {};

WhitePlayer *WhitePlayer::clone()
{
    return new WhitePlayer(*this) ;
};

bool WhitePlayer::isWhite() const
{
    return true;
}
