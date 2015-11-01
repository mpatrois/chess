/**
 * Mise en oeuvre de Echiquier.h
 *
 * @file Echiquier.cxx
 */

#include "Echiquier.h"
#include "Joueur.h"
#include "JoueurBlanc.h"
#include "JoueurNoir.h"


using namespace std;

/**
 * Constructeur par défaut.
 * Initialise à vide l'echiquier.
 */
Echiquier::Echiquier()
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }

    Joueur *jB=new JoueurBlanc();
    Joueur *jN=new JoueurNoir();

    setJoueur(jB,jN);

    font.loadFromFile("dreamwalker.ttf");

    spriteJoueurEnCours=sf::Sprite(Piece::texturePiece);

    texturePlateau.loadFromFile("board.png");

    spritePlateau=sf::Sprite(texturePlateau);


}
Echiquier::Echiquier(Joueur *j1,Joueur *j2)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }

    setJoueur(j1,j2);

    font.loadFromFile("dreamwalker.ttf");

    spriteJoueurEnCours=sf::Sprite(Piece::texturePiece);

}
Echiquier::Echiquier(Partie p)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }
    tour=p.tour;

    Joueur *j1=new JoueurBlanc(utility::split(p.j1,","));
    Joueur *j2=new JoueurNoir(utility::split(p.j2,","));

    setJoueur(j1,j2);

    font.loadFromFile("dreamwalker.ttf");

    spriteJoueurEnCours=sf::Sprite(Piece::texturePiece);

    texturePlateau.loadFromFile("board.png");

    spritePlateau=sf::Sprite(texturePlateau);
}

Echiquier::Echiquier(PartieD p)
{
    for(unsigned int i=0; i<64; i++)
    {
        m_cases[i]=NULL;
    }
    tour=0;
    Joueur *jB=new JoueurBlanc();
    Joueur *jN=new JoueurNoir();
    setJoueur(jB,jN);

    std::vector<std::string> listeCoupsString=utility::split(p.coups,"|");

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

    spriteJoueurEnCours=sf::Sprite(Piece::texturePiece);

    texturePlateau.loadFromFile("board.png");

    spritePlateau=sf::Sprite(texturePlateau);
}
Echiquier::~Echiquier()
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
Piece* Echiquier::getPiece( int x, int y )
{
    if(utility::inPlateau(x,y))
        return m_cases[y*8+x];
    else
        return NULL;
}




/**
 * Place une piece sur l'echiquier, aux coordonnees specifiees dans la piece.
 *
 * @param p un pointeur vers une piece
 *
 * @return 'true' si le placement s'est bien passe, 'false' sinon
 * (case occupee, coordonnees invalides, piece vide )
 */
bool Echiquier::placer( Piece* p )
{
    if(p!=NULL)
    {
        if(utility::inPlateau(p->x(),p->y()))
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
 * Deplace une piece sur l'echiquier, des coordonnees specifiees
 * dans la piece aux coordonnees x,y.
 *
 * @param p un pointeur vers une piece
 * @param x un entier entre 1 et 8
 * @param y un entier entre 1 et 8
 *
 * @return 'true' si le placement s'est bien passe, 'false' sinon
 * (case occupee, coordonnees invalides, piece vide, piece pas
 * presente au bon endroit sur l'echiquier)
 */
bool Echiquier::deplacer( Piece* p, int x, int y )
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
void Echiquier::enleverPiece( int x, int y )
{
    if(utility::inPlateau(x,y))
        m_cases[y*8+x]=NULL;
}


/**
 * Affiche l'echiquier avec des # pour les cases noires et . pour
 * les blanches si elles sont vides, et avec B pour les pieces
 * blanches et N pour les pieces noires.
 */
void Echiquier::affiche()
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
Echiquier::afficheGraphique(sf::RenderWindow &app)
{
    sf::Text text;

    text.setFont(font);
    text.setString("Joueur en cours");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Underlined);
    text.setPosition(500,130);

    app.draw(text);

    if(joueurs[tour]->isWhite())
        spriteJoueurEnCours.setTextureRect(sf::IntRect(60, 60, 60, 60));
    else
        spriteJoueurEnCours.setTextureRect(sf::IntRect(0, 60, 60, 60));

    spriteJoueurEnCours.setPosition(500,160);

    app.draw(spritePlateau);
    app.draw(spriteJoueurEnCours);

    joueurs[0]->affichePieceJGraphique(app,this);
    joueurs[1]->affichePieceJGraphique(app,this);
}
bool Echiquier::click(int mx,int my)
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
void Echiquier::setJoueur(Joueur *jB,Joueur *jN)
{
    joueurs[0]=jB;
    joueurs[1]=jN;

    jB->setJoueurAdverse(jN);
    jN->setJoueurAdverse(jB);

    jB->placer(this);
    jN->placer(this);
}
//void Echiquier::savePartie(std::string nameFile)
//{
//    ofstream myfile;
//
//    myfile.open ("savedGames.txt",std::ios_base::app);
//    myfile << nameFile << endl;
//    myfile << tour << endl;
//
//    joueurs[0]->saveJoueur(myfile);
//    joueurs[1]->saveJoueur(myfile);
//
//    myfile.close();
//};

void Echiquier::savePartie(std::string nameFile)
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

Joueur *Echiquier::getAdverse(bool coulJoueur){
    if(coulJoueur == joueurs[tour]->isWhite())
        return joueurs[tour];
    else
        return joueurs[(tour+1)%2];
}

void Echiquier::addCoup(Case cd,Case ca){
    listeCoups.push_back(Coup(cd,ca));
}

//void Echiquier::openPartie()
//{
//    ifstream infile("example.txt");
//    string piecesJoueurBlanc;
//    string piecesJoueurNoir;
//    if(infile >> tour >> piecesJoueurBlanc >> piecesJoueurNoir)
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
//    joueurs[0]=new JoueurBlanc(utility::split(piecesJoueurBlanc,","));
//    joueurs[1]=new JoueurNoir(utility::split(piecesJoueurNoir,","));
//
//    setJoueur(joueurs[0],joueurs[1]);
//
//};
