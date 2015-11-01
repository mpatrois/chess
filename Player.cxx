#include "Player.h"
#include "Piece.h"
#include "Rook.h"
#include "Chessboard.h"
#include "Pawn.h"
#include <vector>

Player::Player()
{
    echec=false;
    pieceSelected=NULL;
}
Player::Player(const Player &j)
{
    echec=false;

    for(unsigned int i=0; i<j.listePiecePlayer.size(); i++)
    {

        Piece *p=j.listePiecePlayer[i]->clone();

        listePiecePlayer.push_back(p);

        if(j.kingPlayer==j.listePiecePlayer[i])
        {
            kingPlayer=dynamic_cast<King *>(p);
        }
        if(j.pieceSelected!=NULL)
        {
            if(j.pieceSelected==j.listePiecePlayer[i])
                pieceSelected=p;
        }
    }
}

Player::~Player()
{
    for (unsigned int x=0; x<listePiecePlayer.size(); x++)
    {
        delete listePiecePlayer[x];
    }
}
void Player::affichePieceJTerminal()
{
    for (unsigned int x=0; x<listePiecePlayer.size(); x++)
    {
        listePiecePlayer[x]->affiche();
    }
}
void Player::affichePieceJGraphique(sf::RenderWindow &app,Chessboard *e)
{
    if(echec)
    {
        sf::CircleShape circle(30);

        circle.setFillColor(sf::Color::Red);
        circle.setPosition(kingPlayer->x()*60,kingPlayer->y()*60);

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

    for (unsigned int x=0; x<listePiecePlayer.size(); x++)
    {
        listePiecePlayer[x]->afficheGraphique(app);
    }
}
void Player::perdPiece(Piece *piecePerdue)
{
    int pos=-1;

    for(unsigned int i=0; i < listePiecePlayer.size(); i++)
    {
        if(listePiecePlayer[i]==piecePerdue)
        {
            pos=i;
        }
    }
    if(pos!=-1)
    {
        delete listePiecePlayer[pos];
        listePiecePlayer.erase(std::remove(listePiecePlayer.begin(), listePiecePlayer.end(), listePiecePlayer[pos]), listePiecePlayer.end());
    }
}

void Player::placer(Chessboard *e)
{
    for (unsigned int x=0; x<listePiecePlayer.size(); x++)
    {
        e->placer(listePiecePlayer[x]);
    }
}
bool Player::willBeEchec(int caseX,int caseY)
{
    Player *myPlayer=this->clone();
    Player *myPlayerAdverse=adverse->clone();

    Chessboard *myChessboard=new Chessboard(myPlayer,myPlayerAdverse);

    int lastX=myPlayer->pieceSelected->x();
    int lastY=myPlayer->pieceSelected->y();

    myPlayer->pieceSelected->move(caseX,caseY);

    if(myChessboard->getPiece(caseX,caseY)!=NULL)
    {
        myPlayerAdverse->perdPiece(myChessboard->getPiece(caseX,caseY));
        myChessboard->enleverPiece(caseX,caseY);
    };

    myChessboard->enleverPiece(lastX,lastY);
    myChessboard->placer(myPlayer->pieceSelected);

    bool echecFuture=myPlayer->isEchec(myChessboard);

    delete myChessboard;

    return echecFuture;

};
bool Player::isChessMath(Chessboard *e)
{
    if(echec)
    {
        pieceSelected=NULL;
        for (unsigned int i=0; i<listePiecePlayer.size() ; i++)
        {
            pieceSelected=listePiecePlayer[i];

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
bool Player::isEchec(Chessboard *e)
{
    std::vector<Piece *> piecePlayerAdverse=adverse->getPieces();

    echec=false;

    for(unsigned int i=0; i<piecePlayerAdverse.size(); i++)
    {
        std::vector<Case> caseViseeParPlayerAdverse=piecePlayerAdverse[i]->mouvementsPossible(e);

        for(unsigned int j=0; j<caseViseeParPlayerAdverse.size(); j++)
        {
            if(kingPlayer->x()==caseViseeParPlayerAdverse[j].x &&
                kingPlayer->y()==caseViseeParPlayerAdverse[j].y )
                echec=true;
        }
    }
    return echec;
}
bool Player::isMovePossible(int caseX,int caseY,Chessboard *e)
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
bool Player::move(int caseX,int caseY,Chessboard *e)
{
    bool mangeOuBouge=isMovePossible(caseX,caseY,e);

    if(mangeOuBouge)
    {
        int lastX=pieceSelected->x();
        int lastY=pieceSelected->y();

        if(isCastleRight(e,caseX,caseY))
        {
            Rook *tDkingte=dynamic_cast<Rook *>(e->getPiece(7,pieceSelected->y()));
            e->enleverPiece(tDkingte->x(),tDkingte->y());
            tDkingte->move(5,pieceSelected->y());
            e->placer(tDkingte);
        }

        if(isCastleLeft(e,caseX,caseY))
        {
            Rook *tGauche=dynamic_cast<Rook *>(e->getPiece(0,pieceSelected->y()));
            e->enleverPiece(tGauche->x(),tGauche->y());
            tGauche->move(3,pieceSelected->y());
            e->placer(tGauche);
        }

        if(isEnPassantDkingte(e,caseX,caseY)){
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

int Player::getSens(){

    int sens=1;

    if(isWhite())
        sens=-1;

    return sens;
}

std::vector<Case> Player::listeMouvementPossible(Chessboard *e)
{
    std::vector <Case> listeCase=pieceSelected->mouvementsPossible(e);

    if(canCastleLeft(e))
        listeCase.push_back(Case(2,kingPlayer->y()));

    if(canCastleRight(e))
        listeCase.push_back(Case(6,kingPlayer->y()));

    if(canEnPassantDkingte(e))
        listeCase.push_back(Case(pieceSelected->x()+1,pieceSelected->y()+getSens()));

    if(canEnPassantLeft(e))
        listeCase.push_back(Case(pieceSelected->x()-1,pieceSelected->y()+getSens()));

    return listeCase;
}

bool Player::isCastleRight(Chessboard *e,int caseX,int caseY){
//    return(!kingPlayer->hadMove()
//            && pieceSelected==kingPlayer
//            && pieceSelected->y()==caseY
//            && pieceSelected->x()+2==caseX);

    return canCastleRight(e) && pieceSelected->y()==caseY && pieceSelected->x()+2==caseX;
}

bool Player::isCastleLeft(Chessboard *e,int caseX,int caseY){
//    return(!kingPlayer->hadMove()
//            && pieceSelected==kingPlayer
//            && pieceSelected->y()==caseY
//            && pieceSelected->x()-2==caseX);

    return canCastleLeft(e) && pieceSelected->y()==caseY && pieceSelected->x()-2==caseX;
}

bool Player::isEnPassantDkingte(Chessboard *e,int caseX,int caseY){

    return canEnPassantDkingte(e) && caseX==pieceSelected->x()+1 && caseY==pieceSelected->y()+getSens();
}

bool Player::isEnPassantLeft(Chessboard *e,int caseX,int caseY){
    return canEnPassantLeft(e) && caseX==pieceSelected->x()-1 && caseY==pieceSelected->y()+getSens();
}

bool Player::canCastleLeft(Chessboard *e)
{
    if(kingPlayer==pieceSelected && !kingPlayer->hadMove())
    {
        Rook *tGauche=dynamic_cast<Rook*>(e->getPiece(0,kingPlayer->y()));
        if(tGauche!=nullptr && !tGauche->hadMove())
        {
            if(e->getPiece(1,kingPlayer->y())==NULL && e->getPiece(2,kingPlayer->y())==NULL && e->getPiece(3,kingPlayer->y())==NULL){

                if(!adverse->viseCase(2,kingPlayer->y(),e) &&
                   !adverse->viseCase(3,kingPlayer->y(),e) &&
                   !adverse->viseCase(4,kingPlayer->y(),e))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Player::canCastleRight(Chessboard *e)
{
    if(kingPlayer==pieceSelected && !kingPlayer->hadMove())
    {
        Rook *tDkingte=dynamic_cast<Rook*>(e->getPiece(7,kingPlayer->y()));

        if(tDkingte!=nullptr && !tDkingte->hadMove())
        {
            if(e->getPiece(5,kingPlayer->y())==NULL && e->getPiece(6,kingPlayer->y())==NULL){

                    if(!adverse->viseCase(4,kingPlayer->y(),e) &&
                       !adverse->viseCase(5,kingPlayer->y(),e) &&
                       !adverse->viseCase(6,kingPlayer->y(),e))
                    {
                        return true;
                    }
                }
        }
    }
    return false;
}

bool Player::canEnPassantDkingte(Chessboard *e)
{
    Pawn *pionPlayer=dynamic_cast<Pawn*> (pieceSelected);

    if(pionPlayer!=nullptr){


        Pawn *pionDkingte=dynamic_cast<Pawn*> (e->getPiece(pionPlayer->x()+1,pionPlayer->y()));

        if(pionDkingte!=nullptr){

            if(pionDkingte->getNbMove()==1 && e->getPiece(pionPlayer->x()+1,pionPlayer->y()+getSens())==NULL ){
                return true;
            }
        }
    }

    return false;
}
bool Player::canEnPassantLeft(Chessboard *e)
{
    Pawn *pionPlayer=dynamic_cast<Pawn*> (pieceSelected);

        if(pionPlayer!=nullptr){

            Pawn *pionGauche=dynamic_cast<Pawn*> (e->getPiece(pionPlayer->x()-1,pionPlayer->y()));

            if(pionGauche!=nullptr){

                if(pionGauche->getNbMove()==1 && e->getPiece(pionPlayer->x()-1,pionPlayer->y()+getSens())==NULL ){
                    return true;
                }
            }
        }
        return false;
}
bool Player::viseCase(int x,int y,Chessboard *e)
{
    for(unsigned int i=0; i<listePiecePlayer.size(); i++)
    {
        std::vector<Case> caseViseeParPlayer=listePiecePlayer[i]->mouvementsPossible(e);

        for(unsigned int j=0; j<caseViseeParPlayer.size(); j++)
        {
            if(x==caseViseeParPlayer[j].x &&
                y==caseViseeParPlayer[j].y )
                return true;
        }
    }
    return false;
}

void Player::selectPiece(int caseX,int caseY,Chessboard *e){

    Piece *pTmp=e->getPiece(caseX,caseY);

        if(pTmp!=NULL)
        {
            if(isWhite()==pTmp->isWhite() )
                pieceSelected=pTmp;
//                std::cout << "coucou";
        }
}
