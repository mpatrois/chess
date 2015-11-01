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
 * Constructeur par d�faut.
 * Initialise � vide l'chessboard.
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

    spritePlayerEnCours=sf::Sprite(Piece::texturePiece);

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

    spritePlayerEnCours=sf::Sprite(Piece::texturePiece);

}
Chessboard::Chessboard(Partie p)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }
    tour=p.tour;

    Player *j1=new WhitePlayer(Utility::split(p.j1,","));
    Player *j2=new BlackPlayer(Utility::split(p.j2,","));

    setPlayer(j1,j2);

    font.loadFromFile("ressources/dreamwalker.ttf");

    spritePlayerEnCours=sf::Sprite(Piece::texturePiece);

    texturePlateau.loadFromFile("ressources/board.png");

    spritePlateau=sf::Sprite(texturePlateau);
}

Chessboard::Chessboard(PartieD p)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }
    tour=0;
    Player *jB=new WhitePlayer();
    Player *jN=new BlackPlayer();
    setPlayer(jB,jN);

    std::vector<std::string> listeCoupsString=Utility::split(p.coups,"|");

    std::vector<Coup> listeCoupsCharge;


    for (unsigned int i=0;i<listeCoupsString.size();i++ )
    {
        int cseDepX=listeCoupsString[i][0]-'0';
        int cseDepY=listeCoupsString[i][1]-'0';
        int cseArvX=listeCoupsString[i][2]-'0';
        int cseArvY=listeCoupsString[i][3]-'0';

//         cout << cseDepX <<cseDepY << std::endl;

        Case caseDepart(cseDepX,cseDepY);
        Case caseArrivee(cseArvX,cseArvY);

        listeCoupsCharge.push_back(Coup(caseDepart,caseArrivee));
    }
//    std::cout << listeCoups.size() << std::endl;

    for (unsigned int i=0;i<listeCoupsCharge.size();i++ )
    {
//        std::cout << listeCoupsCharge.size() << i << std::endl;

//        cout << listeCoups[i].caseDepart.x << listeCoups[i].caseDepart.y << "|";
        joueurs[tour]->selectPiece(listeCoupsCharge[i].caseDepart.x,listeCoupsCharge[i].caseDepart.y,this);
        joueurs[tour]->move(listeCoupsCharge[i].caseArrivee.x,listeCoupsCharge[i].caseArrivee.y,this);

        tour=(tour+1)%2;
    }



    font.loadFromFile("dreamwalker.ttf");

    spritePlayerEnCours=sf::Sprite(Piece::texturePiece);

    texturePlateau.loadFromFile("board.png");

    spritePlateau=sf::Sprite(texturePlateau);
}
Chessboard::~Chessboard()
{
    delete joueurs[0];

    delete joueurs[1];
}

/**
 * Recupere la piece situee sur une case.
 *
 * @param x un entier entre 1 et 8
 * @param y un entier entre 1 et 8
 *
 * @return 0 si aucune piece n'est sur cette case et un pointeur
 * vers une piece sinon.
 */
Piece* Chessboard::getPiece( int x, int y )
{
    if(Utility::inPlateau(x,y))
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
 * (case occupee, coordonnees invalides, piece vide )
 */
bool Chessboard::placer( Piece* p )
{
    if(p!=NULL)
    {
        if(Utility::inPlateau(p->x(),p->y()))
        {
            int pos=p->y()*8+p->x();

            if(m_cases[pos]==NULL)
            {
                m_cases[pos]=p;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


/**
 * Deplace une piece sur l'chessboard, des coordonnees specifiees
 * dans la piece aux coordonnees x,y.
 *
 * @param p un pointeur vers une piece
 * @param x un entier entre 1 et 8
 * @param y un entier entre 1 et 8
 *
 * @return 'true' si le placement s'est bien passe, 'false' sinon
 * (case occupee, coordonnees invalides, piece vide, piece pas
 * presente au bon endkingt sur l'chessboard)
 */
bool Chessboard::deplacer( Piece* p, int x, int y )
{
    return false;
}


/**
 * Enleve la piece situee sur une case (qui devient vide).
 *
 * @param x un entier entre 1 et 8
 * @param y un entier entre 1 et 8
 *
 * @return 0 si aucune piece n'est sur cette case et le pointeur
 * vers la piece enlevee sinon.
 */
void Chessboard::enleverPiece( int x, int y )
{
    if(Utility::inPlateau(x,y))
        m_cases[y*8+x]=NULL;
}


/**
 * Affiche l'chessboard avec des # pour les cases noires et . pour
 * les blanches si elles sont vides, et avec B pour les pieces
 * blanches et N pour les pieces noires.
 */
void Chessboard::affiche()
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
Chessboard::afficheGraphique(sf::RenderWindow &app)
{
    sf::Text text;

    text.setFont(font);
    text.setString("Player en cours");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Underlined);
    text.setPosition(500,130);

    app.draw(text);

    if(joueurs[tour]->isWhite())
        spritePlayerEnCours.setTextureRect(sf::IntRect(60, 60, 60, 60));
    else
        spritePlayerEnCours.setTextureRect(sf::IntRect(0, 60, 60, 60));

    spritePlayerEnCours.setPosition(500,160);

    app.draw(spritePlateau);
    app.draw(spritePlayerEnCours);

    joueurs[0]->affichePieceJGraphique(app,this);
    joueurs[1]->affichePieceJGraphique(app,this);
}
bool Chessboard::click(int mx,int my)
{
//    cout << tour << "inCli" <<endl;
    int caseX=mx/60;
    int caseY=my/60;

    bool echecEtMath=false;

    if(joueurs[tour]->move(caseX,caseY,this))
    {
        joueurs[tour]->isEchec(this);
        joueurs[(tour+1)%2]->isEchec(this);

        tour=(tour+1)%2;

        echecEtMath=joueurs[tour]->isChessMath(this);
    }
    return echecEtMath;
}
void Chessboard::setPlayer(Player *jB,Player *jN)
{
    joueurs[0]=jB;
    joueurs[1]=jN;

    jB->setPlayerAdverse(jN);
    jN->setPlayerAdverse(jB);

    jB->placer(this);
    jN->placer(this);
}
//void Chessboard::savePartie(std::string nameFile)
//{
//    ofstream myfile;
//
//    myfile.open ("savedGames.txt",std::ios_base::app);
//    myfile << nameFile << endl;
//    myfile << tour << endl;
//
//    joueurs[0]->savePlayer(myfile);
//    joueurs[1]->savePlayer(myfile);
//
//    myfile.close();
//};

void Chessboard::savePartie(std::string nameFile)
{
    ofstream myfile;

    myfile.open ("Games.txt",std::ios_base::app);
    myfile << nameFile << endl;

    for(unsigned int i=0;i<listeCoups.size();i++)
    {
        myfile << listeCoups[i].caseDepart.x ;
        myfile << listeCoups[i].caseDepart.y ;
        myfile << listeCoups[i].caseArrivee.x ;
        myfile << listeCoups[i].caseArrivee.y <<"|";
    }
    myfile<< endl;

    myfile.close();
};

Player *Chessboard::getAdverse(bool colPlayer){
     if(colPlayer){
        return joueurs[1];
    }else
        return joueurs[0];
}

void Chessboard::addCoup(Case cd,Case ca){
    listeCoups.push_back(Coup(cd,ca));
}

//void Chessboard::openPartie()
//{
//    ifstream infile("example.txt");
//    string piecesWhitePlayer;
//    string piecesBlackPlayer;
//    if(infile >> tour >> piecesWhitePlayer >> piecesBlackPlayer)
//    {
//
//    }
//    else
//    {
//        cout << "Fichier non valide" << endl;
//    }
//    infile.close();
//
//    if(joueurs[0]!=NULL)
//        delete joueurs[0];
//
//    if(joueurs[1]!=NULL)
//        delete joueurs[1];
//
//    joueurs[0]=new WhitePlayer(Utility::split(piecesWhitePlayer,","));
//    joueurs[1]=new BlackPlayer(Utility::split(piecesBlackPlayer,","));
//
//    setPlayer(joueurs[0],joueurs[1]);
//
//};
