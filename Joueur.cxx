#include "Joueur.h"
#include "Piece.h"
#include "Echiquier.h"
#include <vector>

Joueur::Joueur()
{
    echec=false;
    pieceSelected=NULL;
}
Joueur::Joueur(const Joueur &j)
{
    echec=false;

    for(unsigned int i=0; i<j.listePieceJoueur.size(); i++)
    {

        Piece *p=j.listePieceJoueur[i]->Clone();

        listePieceJoueur.push_back(p);

        if(j.roiJoueur==j.listePieceJoueur[i])
        {
            roiJoueur=p;
        }
        if(j.pieceSelected!=NULL)
        {
            if(j.pieceSelected==j.listePieceJoueur[i])
                pieceSelected=p;
        }
    }
}

Joueur::~Joueur()
{
    for (unsigned int x=0; x<listePieceJoueur.size(); x++)
    {
        delete listePieceJoueur[x];
    }
}
void Joueur::affichePieceJTerminal()
{
    for (unsigned int x=0; x<listePieceJoueur.size(); x++)
    {
        listePieceJoueur[x]->affiche();
    }
}
void Joueur::affichePieceJGraphique(sf::RenderWindow &app,Echiquier *e)
{
    if(echec)
    {
        sf::CircleShape circle(30);

        circle.setFillColor(sf::Color::Red);
        circle.setPosition(roiJoueur->x()*60,roiJoueur->y()*60);

        app.draw(circle);
    }

    if(pieceSelected!=NULL)
    {
        sf::RectangleShape rectangle;

        rectangle.setSize(sf::Vector2f(60, 60));
        rectangle.setFillColor(sf::Color(81,124,102));
        rectangle.setPosition(pieceSelected->x()*60,pieceSelected->y()*60);

        app.draw(rectangle);

        std::vector<Case> listCase=pieceSelected->mouvementsPossible(e);

        for (unsigned int j=0; j<listCase.size(); j++)
        {
            if(!willBeEchec(listCase[j].x,listCase[j].y))
            {
                sf::CircleShape circle(15);

                circle.setFillColor(sf::Color(81,124,102));
                circle.setPosition(listCase[j].x*60+15,listCase[j].y*60+15);

                app.draw(circle);
            }
        }
    }

    for (unsigned int x=0; x<listePieceJoueur.size(); x++)
    {
        listePieceJoueur[x]->afficheGraphique(app);
    }
}
void Joueur::perdPiece(Piece *piecePerdue)
{
    int pos=-1;

    for(unsigned int i=0; i < listePieceJoueur.size(); i++)
    {
        if(listePieceJoueur[i]==piecePerdue)
        {
            pos=i;
        }
    }
    if(pos!=-1)
    {
        delete listePieceJoueur[pos];
        listePieceJoueur.erase(std::remove(listePieceJoueur.begin(), listePieceJoueur.end(), listePieceJoueur[pos]), listePieceJoueur.end());
    }
}

void Joueur::placer(Echiquier *e)
{
    for (unsigned int x=0; x<listePieceJoueur.size(); x++)
    {
        e->placer(listePieceJoueur[x]);
    }
}
bool Joueur::willBeEchec(int caseX,int caseY)
{
    Joueur *myJoueur=this->Clone();
    Joueur *myJoueurAdverse=adverse->Clone();

    Echiquier *myEchiquier=new Echiquier(myJoueur,myJoueurAdverse);

    int lastX=myJoueur->pieceSelected->x();
    int lastY=myJoueur->pieceSelected->y();

    myJoueur->pieceSelected->move(caseX,caseY);

    if(myEchiquier->getPiece(caseX,caseY)!=NULL)
    {
        myJoueurAdverse->perdPiece(myEchiquier->getPiece(caseX,caseY));
        myEchiquier->enleverPiece(caseX,caseY);
    };

    myEchiquier->enleverPiece(lastX,lastY);
    myEchiquier->placer(myJoueur->pieceSelected);

    bool echecFuture=myJoueur->isEchec(myEchiquier);

    delete myEchiquier;

    return echecFuture;

};
bool Joueur::isChessMath(Echiquier *e)
{
    if(echec)
    {
        pieceSelected=NULL;
        for (unsigned int i=0; i<listePieceJoueur.size() ; i++)
        {
            pieceSelected=listePieceJoueur[i];

            std::vector<Case> listeMouvPossible=pieceSelected->mouvementsPossible(e);

            for (unsigned int j=0; j<listeMouvPossible.size() ; j++)
            {
                if(!willBeEchec(listeMouvPossible[j].x,listeMouvPossible[j].y))
                {
                    return false;
                }
            }
        }
        pieceSelected=NULL;

        return true;
    }
    else
    {
        return false;
    }
}
bool Joueur::isEchec(Echiquier *e)
{
    std::vector<Piece *> pieceJoueurAdverse=adverse->getPieces();

    echec=false;

    for(unsigned int i=0; i<pieceJoueurAdverse.size(); i++)
    {
        std::vector<Case> caseViseeParJoueurAdverse=pieceJoueurAdverse[i]->mouvementsPossible(e);

        for(unsigned int j=0; j<caseViseeParJoueurAdverse.size(); j++)
        {
            if(roiJoueur->x()==caseViseeParJoueurAdverse[j].x &&
                roiJoueur->y()==caseViseeParJoueurAdverse[j].y )
                echec=true;
        }
    }
    return echec;
}
bool Joueur::isMovePossible(int caseX,int caseY,Echiquier *e)
{
    if(pieceSelected!=NULL)
    {
        std::vector<Case> listeCase=pieceSelected->mouvementsPossible(e);

        for (unsigned int i=0; i<listeCase.size(); i++)
        {
            if(listeCase[i].x==caseX && listeCase[i].y==caseY && !willBeEchec(caseX,caseY) )
                return true;
        }
    }
    return false;
}
bool Joueur::move(int caseX,int caseY,Echiquier *e)
{
    bool mangeOuBouge=isMovePossible(caseX,caseY,e);

    if(mangeOuBouge)
    {
        int lastX=pieceSelected->x();
        int lastY=pieceSelected->y();

        pieceSelected->move(caseX,caseY);

        if(e->getPiece(caseX,caseY)!=NULL)
        {
            adverse->perdPiece(e->getPiece(caseX,caseY));
            e->enleverPiece(caseX,caseY);
        };

        e->enleverPiece(lastX,lastY);
        e->placer(pieceSelected);

        pieceSelected=NULL;
    }
    else
    {
        Piece *pTmp=e->getPiece(caseX,caseY);

        if(pTmp!=NULL)
        {
            if(isWhite()==pTmp->isWhite() )
                pieceSelected=pTmp;
        }
    }
    return mangeOuBouge;
}
