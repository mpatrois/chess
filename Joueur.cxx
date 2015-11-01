#include "Joueur.h"
#include "Piece.h"
#include "Tour.h"
#include "Echiquier.h"
#include "Pion.h"
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
            roiJoueur=dynamic_cast<Roi *>(p);
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

//       std::vector<Case> listCase=pieceSelected->mouvementsPossible(e);
        std::vector<Case> listCase=listeMouvementPossible(e);

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
        std::vector<Case> listeCase=listeMouvementPossible(e);

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

        if(isCastleRight(e,caseX,caseY))
        {
            Tour *tDroite=dynamic_cast<Tour *>(e->getPiece(7,pieceSelected->y()));
            e->enleverPiece(tDroite->x(),tDroite->y());
            tDroite->move(5,pieceSelected->y());
            e->placer(tDroite);
        }

        if(isCastleLeft(e,caseX,caseY))
        {
            Tour *tGauche=dynamic_cast<Tour *>(e->getPiece(0,pieceSelected->y()));
            e->enleverPiece(tGauche->x(),tGauche->y());
            tGauche->move(3,pieceSelected->y());
            e->placer(tGauche);
        }

        if(isEnPassantDroite(e,caseX,caseY)){
            adverse->perdPiece(e->getPiece(caseX,caseY+(getSens()*-1)));
            e->enleverPiece(caseX,caseY+(getSens()*-1));
        }

        if(isEnPassantLeft(e,caseX,caseY)){
            adverse->perdPiece(e->getPiece(caseX,caseY+(getSens()*-1)));
            e->enleverPiece(caseX,caseY+(getSens()*-1));
        }

        pieceSelected->move(caseX,caseY);

        if(e->getPiece(caseX,caseY)!=NULL)
        {
            adverse->perdPiece(e->getPiece(caseX,caseY));
            e->enleverPiece(caseX,caseY);
        };

        e->enleverPiece(lastX,lastY);
        e->placer(pieceSelected);

        pieceSelected=NULL;

        e->addCoup(Case(lastX,lastY),Case(caseX,caseY));
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

int Joueur::getSens(){

    int sens=1;

    if(isWhite())
        sens=-1;

    return sens;
}

std::vector<Case> Joueur::listeMouvementPossible(Echiquier *e)
{
    std::vector <Case> listeCase=pieceSelected->mouvementsPossible(e);

    if(canCastleLeft(e))
        listeCase.push_back(Case(2,roiJoueur->y()));

    if(canCastleRight(e))
        listeCase.push_back(Case(6,roiJoueur->y()));

    if(canEnPassantDroite(e))
        listeCase.push_back(Case(pieceSelected->x()+1,pieceSelected->y()+getSens()));

    if(canEnPassantLeft(e))
        listeCase.push_back(Case(pieceSelected->x()-1,pieceSelected->y()+getSens()));

    return listeCase;
}

bool Joueur::isCastleRight(Echiquier *e,int caseX,int caseY){
//    return(!roiJoueur->hadMove()
//            && pieceSelected==roiJoueur
//            && pieceSelected->y()==caseY
//            && pieceSelected->x()+2==caseX);

    return canCastleRight(e) && pieceSelected->y()==caseY && pieceSelected->x()+2==caseX;
}

bool Joueur::isCastleLeft(Echiquier *e,int caseX,int caseY){
//    return(!roiJoueur->hadMove()
//            && pieceSelected==roiJoueur
//            && pieceSelected->y()==caseY
//            && pieceSelected->x()-2==caseX);

    return canCastleLeft(e) && pieceSelected->y()==caseY && pieceSelected->x()-2==caseX;
}

bool Joueur::isEnPassantDroite(Echiquier *e,int caseX,int caseY){

    return canEnPassantDroite(e) && caseX==pieceSelected->x()+1 && caseY==pieceSelected->y()+getSens();
}

bool Joueur::isEnPassantLeft(Echiquier *e,int caseX,int caseY){
    return canEnPassantLeft(e) && caseX==pieceSelected->x()-1 && caseY==pieceSelected->y()+getSens();
}

bool Joueur::canCastleLeft(Echiquier *e)
{
    if(roiJoueur==pieceSelected && !roiJoueur->hadMove())
    {
        Tour *tGauche=dynamic_cast<Tour*>(e->getPiece(0,roiJoueur->y()));
        if(tGauche!=nullptr && !tGauche->hadMove())
        {
            if(e->getPiece(1,roiJoueur->y())==NULL && e->getPiece(2,roiJoueur->y())==NULL && e->getPiece(3,roiJoueur->y())==NULL){

                if(!adverse->viseCase(2,roiJoueur->y(),e) &&
                   !adverse->viseCase(3,roiJoueur->y(),e) &&
                   !adverse->viseCase(4,roiJoueur->y(),e))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Joueur::canCastleRight(Echiquier *e)
{
    if(roiJoueur==pieceSelected && !roiJoueur->hadMove())
    {
        Tour *tDroite=dynamic_cast<Tour*>(e->getPiece(7,roiJoueur->y()));

        if(tDroite!=nullptr && !tDroite->hadMove())
        {
            if(e->getPiece(5,roiJoueur->y())==NULL && e->getPiece(6,roiJoueur->y())==NULL){

                    if(!adverse->viseCase(4,roiJoueur->y(),e) &&
                       !adverse->viseCase(5,roiJoueur->y(),e) &&
                       !adverse->viseCase(6,roiJoueur->y(),e))
                    {
                        return true;
                    }
                }
        }
    }
    return false;
}

bool Joueur::canEnPassantDroite(Echiquier *e)
{
    Pion *pionJoueur=dynamic_cast<Pion*> (pieceSelected);

    if(pionJoueur!=nullptr){


        Pion *pionDroite=dynamic_cast<Pion*> (e->getPiece(pionJoueur->x()+1,pionJoueur->y()));

        if(pionDroite!=nullptr){

            if(pionDroite->getNbMove()==1 && e->getPiece(pionJoueur->x()+1,pionJoueur->y()+getSens())==NULL ){
                return true;
            }
        }
    }

    return false;
}
bool Joueur::canEnPassantLeft(Echiquier *e)
{
    Pion *pionJoueur=dynamic_cast<Pion*> (pieceSelected);

        if(pionJoueur!=nullptr){

            Pion *pionGauche=dynamic_cast<Pion*> (e->getPiece(pionJoueur->x()-1,pionJoueur->y()));

            if(pionGauche!=nullptr){

                if(pionGauche->getNbMove()==1 && e->getPiece(pionJoueur->x()-1,pionJoueur->y()+getSens())==NULL ){
                    return true;
                }
            }
        }
        return false;
}
bool Joueur::viseCase(int x,int y,Echiquier *e)
{
    for(unsigned int i=0; i<listePieceJoueur.size(); i++)
    {
        std::vector<Case> caseViseeParJoueur=listePieceJoueur[i]->mouvementsPossible(e);

        for(unsigned int j=0; j<caseViseeParJoueur.size(); j++)
        {
            if(x==caseViseeParJoueur[j].x &&
                y==caseViseeParJoueur[j].y )
                return true;
        }
    }
    return false;
}

void Joueur::selectPiece(int caseX,int caseY,Echiquier *e){

    Piece *pTmp=e->getPiece(caseX,caseY);

        if(pTmp!=NULL)
        {
            if(isWhite()==pTmp->isWhite() )
                pieceSelected=pTmp;
//                std::cout << "coucou";
        }
}
