#include "Fou.h"
#include "Roi.h"
#include "Reine.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Pion.h"
#include "util.h"
#include "JoueurNoir.h"

JoueurNoir::JoueurNoir()
{
    listePieceJoueur.push_back(new Tour(0,0,false));
    listePieceJoueur.push_back(new Cavalier(1,0,false));
    listePieceJoueur.push_back(new Fou(2,0,false));

    Roi *roi=new Roi(4,0,false);
    roiJoueur=roi;
    listePieceJoueur.push_back(roiJoueur);

    listePieceJoueur.push_back(new Reine(3,0,false));
    listePieceJoueur.push_back(new Fou(5,0,false));
    listePieceJoueur.push_back(new Cavalier(6,0,false));
    listePieceJoueur.push_back(new Tour(7,0,false));

    for (int x=8; x<16; x++)
    {
        listePieceJoueur.push_back(new Pion(x%8,1,false));
    }
};
JoueurNoir::JoueurNoir(std::vector<std::string> listPieces):Joueur()
{
    for(unsigned int i=0; i<listPieces.size(); i++)
    {
        std::string typePiece=listPieces[i].substr(0,1);
        int x=utility::stoi(listPieces[i].substr(2,1));
        int y=utility::stoi(listPieces[i].substr(4,1));

        if(typePiece=="t" || typePiece=="T")
        {
            listePieceJoueur.push_back(new Tour(x,y,false));
        }
        else if(typePiece=="r" || typePiece=="R")
        {
            Roi *p=new Roi(x,y,false);
            listePieceJoueur.push_back(p);
            roiJoueur=p;
        }
        else if(typePiece=="q" || typePiece=="Q")
        {
            listePieceJoueur.push_back(new Reine(x,y,false));
        }
        else if(typePiece=="f" || typePiece=="F")
        {
            listePieceJoueur.push_back(new Fou(x,y,false));
        }
        else if(typePiece=="c" || typePiece=="C")
        {
            listePieceJoueur.push_back(new Cavalier(x,y,false));
        }
        else if(typePiece=="p" || typePiece=="P")
        {
            listePieceJoueur.push_back(new Pion(x,y,false));
        }
    }
}

JoueurNoir::~JoueurNoir();

JoueurNoir *JoueurNoir::Clone()
{
    return new JoueurNoir(*this) ;
};

bool JoueurNoir::isWhite()
{
    return false;
}