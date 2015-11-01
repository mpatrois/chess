#include "Player.h"

Player::Player()
{
    check=false;
    selectedPiece=NULL;
}

Player::Player(const Player &j)
{
    check=false;

    for(unsigned int i=0; i<j.playerPieces.size(); i++)
    {

        Piece *p=j.playerPieces[i]->clone();

        playerPieces.push_back(p);

        if(j.kingPlayer==j.playerPieces[i])
            kingPlayer=dynamic_cast<King *>(p);

        if(j.selectedPiece!=NULL)
            if(j.selectedPiece==j.playerPieces[i])
                selectedPiece=p;
    }
}

Player::~Player()
{
    for (unsigned int x=0; x<playerPieces.size(); x++)
        delete playerPieces[x];
}

std::vector<Piece *> Player::getPieces()
{
    return playerPieces;
}

void Player::affichePieceJTerminal()
{
    for (unsigned int x=0; x<playerPieces.size(); x++)
        playerPieces[x]->display();
}

void Player::displayPlayerPiece(sf::RenderWindow &app,Chessboard *e)
{
    if(check)
    {
        sf::CircleShape circle(30);

        circle.setFillColor(sf::Color::Red);
        circle.setPosition(kingPlayer->x()*60,kingPlayer->y()*60);

        app.draw(circle);
    }

    if(selectedPiece!=NULL)
    {
        sf::RectangleShape rectangle;

        rectangle.setSize(sf::Vector2f(60, 60));
        rectangle.setFillColor(sf::Color(81,124,102));
        rectangle.setPosition(selectedPiece->x()*60,selectedPiece->y()*60);

        app.draw(rectangle);

        std::vector<Square> listCase=listeMouvementPossible(e);

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

    for (unsigned int x=0; x<playerPieces.size(); x++)
    {
        playerPieces[x]->graphicDisplay(app);
    }
}

void Player::loosePiece(Piece *piecePerdue)
{
    int pos=-1;

    for(unsigned int i=0; i < playerPieces.size(); i++)
    {
        if(playerPieces[i]==piecePerdue)
        {
            pos=i;
        }
    }
    if(pos!=-1)
    {
        delete playerPieces[pos];
        playerPieces.erase(std::remove(playerPieces.begin(), playerPieces.end(), playerPieces[pos]), playerPieces.end());
    }
}

void Player::put(Chessboard *e)
{
    for (unsigned int x=0; x<playerPieces.size(); x++)
    {
        e->put(playerPieces[x]);
    }
}

bool Player::willBeEchec(int caseX,int caseY)
{
    Player *myPlayer=this->clone();
    Player *myPlayerAdverse=opponent->clone();

    Chessboard *myChessboard=new Chessboard(myPlayer,myPlayerAdverse);

    myPlayer->selectedPiece->move(caseX,caseY,myChessboard);

    bool echecFuture=myPlayer->isEchec(myChessboard);

    delete myChessboard;

    return echecFuture;

}

Square Player::getPosKingPlayer()
{
    return Square(kingPlayer->x(),kingPlayer->y());
}

void Player::savePlayer(std::ofstream &myfile)
{
    for(unsigned int i=0; i<playerPieces.size(); i++)
    {
        if(i!=0)
        {
            myfile<<",";
        }
        myfile << playerPieces[i]->typePiece() << "|" << playerPieces[i]->x() << "|" << playerPieces[i]->y();
    }
    myfile << std::endl;
};

bool Player::isChessMath(Chessboard *e)
{
    if(check)
    {
        selectedPiece=NULL;

        for (unsigned int i=0; i<playerPieces.size() ; i++)
        {
            selectedPiece = playerPieces[i];

            std::vector<Square> listAvailableMovements = selectedPiece->availableMovements(e);

            for (unsigned int j=0; j<listAvailableMovements.size() ; j++)
            {
                if(!willBeEchec(listAvailableMovements[j].x,listAvailableMovements[j].y))
                {
                    return false;
                }
            }
        }

        selectedPiece=NULL;

        return true;
    }

    return false;
}
bool Player::isEchec(Chessboard *e)
{
    std::vector<Piece *> opponentPieces = opponent->getPieces();

    check=false;

    for(unsigned int i=0; i<opponentPieces.size(); i++)
    {
        std::vector<Square> opponentTargetSquares = opponentPieces[i]->availableMovements(e);

        for(unsigned int j=0; j<opponentTargetSquares.size(); j++)
        {
            if(kingPlayer->x()==opponentTargetSquares[j].x &&
                kingPlayer->y()==opponentTargetSquares[j].y )
                check = true;
        }
    }

    return check;
}

bool Player::isMovePossible(int caseX,int caseY,Chessboard *e)
{
    if(selectedPiece!=NULL)
    {
        std::vector<Square> listeCase=listeMouvementPossible(e);

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
        int lastX=selectedPiece->x();
        int lastY=selectedPiece->y();

        if(isCastleRight(e,caseX,caseY))
        {
            Rook *tDkingte=dynamic_cast<Rook *>(e->getPiece(7,selectedPiece->y()));
            tDkingte->move(5,selectedPiece->y(),e);
        }

        if(isCastleLeft(e,caseX,caseY))
        {
            Rook *tGauche=dynamic_cast<Rook *>(e->getPiece(0,selectedPiece->y()));
            tGauche->move(3,selectedPiece->y(),e);
        }

        if(isEnPassantRight(e,caseX,caseY)){
            opponent->loosePiece(e->getPiece(caseX,caseY+(getSens()*-1)));
            e->removePiece(caseX,caseY+(getSens()*-1));
        }

        if(isEnPassantLeft(e,caseX,caseY)){
            opponent->loosePiece(e->getPiece(caseX,caseY+(getSens()*-1)));
            e->removePiece(caseX,caseY+(getSens()*-1));
        }

        selectedPiece->move(caseX,caseY,e);

        selectedPiece=NULL;

        e->addBlow(Square(lastX,lastY),Square(caseX,caseY));
    }
    else
    {
        Piece *pTmp=e->getPiece(caseX,caseY);

        if(pTmp!=NULL)
        {
            if(isWhite()==pTmp->isWhite() )
                selectedPiece=pTmp;
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

std::vector<Square> Player::listeMouvementPossible(Chessboard *e)
{
    std::vector <Square> listeCase=selectedPiece->availableMovements(e);

    if(canCastleLeft(e))
        listeCase.push_back(Square(2,kingPlayer->y()));

    if(canCastleRight(e))
        listeCase.push_back(Square(6,kingPlayer->y()));

    if(canEnPassantRight(e))
        listeCase.push_back(Square(selectedPiece->x()+1,selectedPiece->y()+getSens()));

    if(canEnPassantLeft(e))
        listeCase.push_back(Square(selectedPiece->x()-1,selectedPiece->y()+getSens()));

    return listeCase;
}

bool Player::isCastleRight(Chessboard *e,int caseX,int caseY){
    return canCastleRight(e) && selectedPiece->y()==caseY && selectedPiece->x()+2==caseX;
}

bool Player::isCastleLeft(Chessboard *e,int caseX,int caseY){
    return canCastleLeft(e) && selectedPiece->y()==caseY && selectedPiece->x()-2==caseX;
}

bool Player::isEnPassantRight(Chessboard *e,int caseX,int caseY){
    return canEnPassantRight(e) && caseX==selectedPiece->x()+1 && caseY==selectedPiece->y()+getSens();
}

bool Player::isEnPassantLeft(Chessboard *e,int caseX,int caseY){
    return canEnPassantLeft(e) && caseX==selectedPiece->x()-1 && caseY==selectedPiece->y()+getSens();
}

bool Player::canCastleLeft(Chessboard *e)
{
    if(kingPlayer==selectedPiece && !kingPlayer->hadMove())
    {
        Rook *tGauche=dynamic_cast<Rook*>(e->getPiece(0,kingPlayer->y()));
        if(tGauche!=nullptr && !tGauche->hadMove())
        {
            if(e->getPiece(1,kingPlayer->y())==NULL && e->getPiece(2,kingPlayer->y())==NULL && e->getPiece(3,kingPlayer->y())==NULL){

                if(!opponent->viseCase(2,kingPlayer->y(),e) &&
                   !opponent->viseCase(3,kingPlayer->y(),e) &&
                   !opponent->viseCase(4,kingPlayer->y(),e))
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
    if(kingPlayer==selectedPiece && !kingPlayer->hadMove())
    {
        Rook *tDkingte=dynamic_cast<Rook*>(e->getPiece(7,kingPlayer->y()));

        if(tDkingte!=nullptr && !tDkingte->hadMove())
        {
            if(e->getPiece(5,kingPlayer->y())==NULL && e->getPiece(6,kingPlayer->y())==NULL){

                    if(!opponent->viseCase(4,kingPlayer->y(),e) &&
                       !opponent->viseCase(5,kingPlayer->y(),e) &&
                       !opponent->viseCase(6,kingPlayer->y(),e))
                    {
                        return true;
                    }
                }
        }
    }
    return false;
}

bool Player::canEnPassantRight(Chessboard *e)
{
    Pawn *pionPlayer=dynamic_cast<Pawn*> (selectedPiece);

    if(pionPlayer!=nullptr){

        Pawn *pionRight=dynamic_cast<Pawn*> (e->getPiece(pionPlayer->x()+1,pionPlayer->y()));

        if(pionRight!=nullptr){

            Blow c=e->getLastBlow();

            if(pionRight->x()==c.caseArrivee.x && pionRight->y()==c.caseArrivee.y  ){
                return true;
            }


        }
    }

    return false;
}
bool Player::canEnPassantLeft(Chessboard *e)
{
    Pawn *pionPlayer=dynamic_cast<Pawn*> (selectedPiece);

        if(pionPlayer!=nullptr){

            Pawn *pionGauche=dynamic_cast<Pawn*> (e->getPiece(pionPlayer->x()-1,pionPlayer->y()));

            if(pionGauche!=nullptr){

                Blow c=e->getLastBlow();
                if(pionGauche->x()==c.caseArrivee.x && pionGauche->y()==c.caseArrivee.y  ){
                    return true;
                }
            }
        }
        return false;
}
bool Player::viseCase(int x,int y,Chessboard *e)
{
    for(unsigned int i=0; i<playerPieces.size(); i++)
    {
        std::vector<Square> caseViseeParPlayer=playerPieces[i]->availableMovements(e);

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
                selectedPiece=pTmp;
        }
}
