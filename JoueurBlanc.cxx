#include "Fou.h"
#include "Roi.h"
#include "Reine.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Pion.h"
#include "JoueurBlanc.h"

JoueurBlanc::JoueurBlanc():Joueur()
{
    listePieceJoueur.push_back(new Tour(0,0,true));
    listePieceJoueur.push_back(new Cavalier(1,0,true));
    listePieceJoueur.push_back(new Fou(2,0,true));

    Piece *roi=new Roi(3,0,true);
    roiJoueur=roi;
    listePieceJoueur.push_back(roiJoueur);

    listePieceJoueur.push_back(new Reine(4,0,true));
    listePieceJoueur.push_back(new Fou(5,0,true));
    listePieceJoueur.push_back(new Cavalier(6,0,true));
    listePieceJoueur.push_back(new Tour(7,0,true));

    for (int x=8; x<16; x++)
    {
        listePieceJoueur.push_back(new Pion(x%8,1,true));
    }

};
JoueurBlanc::JoueurBlanc(std::vector<std::string> listPieces):Joueur()
{
    for(unsigned int i=0; i<listPieces.size(); i++)
    {
        std::string typePiece=listPieces[i].substr(0,1);
        int x=utility::stoi(listPieces[i].substr(2,1));
        int y=utility::stoi(listPieces[i].substr(4,1));

        if(typePiece=="t" || typePiece=="T")
        {
            listePieceJoueur.push_back(new Tour(x,y,true));
        }
        else if(typePiece=="r" || typePiece=="R")
        {
            Piece *p=new Roi(x,y,true);
            listePieceJoueur.push_back(p);
            roiJoueur=p;
        }
        else if(typePiece=="q" || typePiece=="Q")
        {
            listePieceJoueur.push_back(new Reine(x,y,true));
        }
        else if(typePiece=="f" || typePiece=="F")
        {
            listePieceJoueur.push_back(new Fou(x,y,true));
        }
        else if(typePiece=="c" || typePiece=="C")
        {
            listePieceJoueur.push_back(new Cavalier(x,y,true));
        }
        else if(typePiece=="p" || typePiece=="P")
        {
            listePieceJoueur.push_back(new Pion(x,y,true));
        }
    }
};
JoueurBlanc::~JoueurBlanc() {};

JoueurBlanc *JoueurBlanc::Clone()
{
    return new JoueurBlanc(*this) ;
};

bool JoueurBlanc::isWhite()
{
    return true;
}