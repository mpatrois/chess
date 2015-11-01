/**
 * Mise en oeuvre de Chessboard.h
 *
 * @file Chessboard.cxx
 */

#include "Chessboard.h"
#include "Player.h"
#include "WhitePlayer.h"
#include "BlackPlayer.h"


using namespace std;

/**
 * Constructeur par défaut.
 * Initialise à vide l'chessboard.
 */
Chessboard::Chessboard() : tour(0)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }

    Player *jB=new WhitePlayer();
    Player *jN=new BlackPlayer();

    setPlayer(jB,jN);

    font.loadFromFile("ressources/dreamwalker.ttf");

    spriteCurrentPlayer=sf::Sprite(Piece::texturePiece);

    texturePlateau.loadFromFile("ressources/board.png");

    spritePlateau=sf::Sprite(texturePlateau);


}

Chessboard::Chessboard(Player *j1,Player *j2) : tour(0)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }

    setPlayer(j1,j2);

    font.loadFromFile("ressources/dreamwalker.ttf");

    spriteCurrentPlayer=sf::Sprite(Piece::texturePiece);

}

Chessboard::Chessboard(Partie p) : tour(0)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }

    Player *jB = new WhitePlayer();
    Player *jN = new BlackPlayer();
    setPlayer(jB,jN);

    std::vector<std::string> listeBlowsString = Utility::split(p.blows,"|");

    std::vector<Blow> listeBlowsCharge;

    for (unsigned int i=0;i<listeBlowsString.size();i++ )
    {
        int cseDepX=listeBlowsString[i][0]-'0';
        int cseDepY=listeBlowsString[i][1]-'0';
        int cseArvX=listeBlowsString[i][2]-'0';
        int cseArvY=listeBlowsString[i][3]-'0';

        Square caseDepart(cseDepX,cseDepY);
        Square caseArrivee(cseArvX,cseArvY);

        listeBlowsCharge.push_back(Blow(caseDepart,caseArrivee));
    }

    for (unsigned int i=0;i<listeBlowsCharge.size();i++ )
    {
        players[tour]->selectPiece(listeBlowsCharge[i].caseDepart.x,listeBlowsCharge[i].caseDepart.y,this);
        players[tour]->move(listeBlowsCharge[i].caseArrivee.x,listeBlowsCharge[i].caseArrivee.y,this);

        tour=(tour+1)%2;
    }

    font.loadFromFile("dreamwalker.ttf");

    spriteCurrentPlayer = sf::Sprite(Piece::texturePiece);

    texturePlateau.loadFromFile("board.png");

    spritePlateau = sf::Sprite(texturePlateau);
}
Chessboard::~Chessboard()
{
    delete players[0];
    delete players[1];
}

/**
 * Recupere la piece situee sur une square.
 *
 * @param x un entier entre 1 et 8
 * @param y un entier entre 1 et 8
 *
 * @return 0 si aucune piece n'est sur cette square et un pointeur
 * vers une piece sinon.
 */
Piece* Chessboard::getPiece( int x, int y )
{
    if(Utility::inChessboard(x,y))
        return m_cases[y*8+x];
    else
        return NULL;
}




/**
 * Place une piece sur l'chessboard, aux coordonnees specifiees dans la piece.
 *
 * @param p un pointeur vers une piece
 *
 * @return 'true' si le placement s'est bien passe, 'false' sinon
 * (square occupee, coordonnees invalides, piece vide )
 */
bool Chessboard::put( Piece* p )
{
    if(p!=NULL)
    {
        if(Utility::inChessboard(p->x(),p->y()))
        {
            int pos=p->y()*8+p->x();

            if(m_cases[pos]==NULL)
            {
                m_cases[pos]=p;
                return true;
            }
            return false;
        }
    }

    return false;
}


/**
 * Enleve la piece situee sur une square (qui devient vide).
 *
 * @param x un entier entre 1 et 8
 * @param y un entier entre 1 et 8
 *
 * @return 0 si aucune piece n'est sur cette square et le pointeur
 * vers la piece enlevee sinon.
 */
void Chessboard::removePiece( int x, int y )
{
    if(Utility::inChessboard(x,y))
        m_cases[y*8+x]=NULL;
}


/**
 * Affiche l'chessboard avec des # pour les cases noires et . pour
 * les blanches si elles sont vides, et avec B pour les pieces
 * blanches et N pour les pieces noires.
 */
void Chessboard::display()
{
    cout << endl << "  01234567" << endl;
    for ( int y = 0; y < 8; ++y )
    {
        cout << y << " ";
        for ( int x = 0; x <= 7; ++x )
        {
            string c;
            Piece* p = getPiece( x, y );
            if ( p == 0 )
                c = ( ( x + y ) % 2 ) == 0 ? '#' : '.';
            else
                c = p->typePiece();
            cout << c;
        }
        cout << " " << y << endl;
    }
    cout << "  01234567" << endl;
}

void
Chessboard::graphicDisplay(sf::RenderWindow &app)
{
    sf::Text text;

    text.setFont(font);
    text.setString("Current player");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Underlined);
    text.setPosition(500,130);

    app.draw(text);

    if(players[tour]->isWhite())
        spriteCurrentPlayer.setTextureRect(sf::IntRect(60, 60, 60, 60));
    else
        spriteCurrentPlayer.setTextureRect(sf::IntRect(0, 60, 60, 60));

    spriteCurrentPlayer.setPosition(500,160);

    app.draw(spritePlateau);
    app.draw(spriteCurrentPlayer);

    players[0]->displayPlayerPiece(app,this);
    players[1]->displayPlayerPiece(app,this);
}

bool Chessboard::click(int mx,int my)
{
    int caseX=mx/60;
    int caseY=my/60;

    bool checkMate=false;

    if(players[tour]->move(caseX,caseY,this))
    {
        players[tour]->isEchec(this);
        players[(tour+1)%2]->isEchec(this);

        tour=(tour+1)%2;

        checkMate=players[tour]->isChessMath(this);
    }
    return checkMate;
}
void Chessboard::setPlayer(Player *jB,Player *jN)
{
    players[0]=jB;
    players[1]=jN;

    jB->setPlayerAdverse(jN);
    jN->setPlayerAdverse(jB);

    jB->put(this);
    jN->put(this);
}
//void Chessboard::savePartie(std::string nameFile)
//{
//    ofstream myfile;
//
//    myfile.open ("savedGames.txt",std::ios_base::app);
//    myfile << nameFile << endl;
//    myfile << tour << endl;
//
//    players[0]->savePlayer(myfile);
//    players[1]->savePlayer(myfile);
//
//    myfile.close();
//};

void Chessboard::savePartie(std::string nameFile)
{
    ofstream myfile;

    myfile.open ("Games.txt",std::ios_base::app);
    myfile << nameFile << endl;

    for(unsigned int i=0;i<listeBlows.size();i++)
    {
        myfile << listeBlows[i].caseDepart.x ;
        myfile << listeBlows[i].caseDepart.y ;
        myfile << listeBlows[i].caseArrivee.x ;
        myfile << listeBlows[i].caseArrivee.y <<"|";
    }
    myfile<< endl;

    myfile.close();
};

Player *Chessboard::getOpponent(bool colPlayer){
     if(colPlayer)
        return players[1];
     else
        return players[0];
}

void Chessboard::addBlow(Square cd,Square ca){
    listeBlows.push_back(Blow(cd,ca));
}


Blow Chessboard::getLastBlow(){
    if(listeBlows.size()>1)
        return listeBlows.back();
    else
        return Blow();
}
