/**
 * Mise en oeuvre de Chessboard.h
 *
 * @file Chessboard.cxx
 */

#include <iostream>
#include <sstream>
#include "Chessboard.h"
#include "Utils.h"
#include "Pawn.h"
#include "King.h"


using namespace std;

Chessboard::Chessboard() : currentPlayer(true), turn(0)
{
	for (int i = 0; i < m_size; ++i) {
	   m_cases[i] = NULL;
  }
}

Chessboard::~Chessboard()
{}

Piece*
Chessboard::getPiece( int x, int y )
{
 	if(m_cases[matrixToArrayPosition(x, y)] != NULL)
 		return m_cases[matrixToArrayPosition(x, y)];

 	return 0;
}

Piece*
Chessboard::getPiece( int place )
{
  if(m_cases[place] != NULL)
 		return m_cases[place];

 	return 0;
}

bool
Chessboard::getCurrentPlayer() const
{
	return currentPlayer;
}

bool
Chessboard::placer( Piece* p )
{
 	if(p != NULL && (m_cases[matrixToArrayPosition(p->x(), p->y())] == NULL)
 		&& (p->x() > 0 && p->x() < 9 && p->y() > 0 && p->y() < 9))
 	{
 		m_cases[matrixToArrayPosition(p->x(), p->y())] = p;
 		return true;
 	}

 	return false;
}


bool
Chessboard::deplacer( Piece* p, int x, int y )
{
	m_cases[matrixToArrayPosition(p->x(), p->y())] = 0;
	p->move(x, y);
	return this->placer(p);
}


void
Chessboard::jouerPiece(Piece* p, int x, int y)
{
	Piece *current = enleverPiece(p->x(), p->y());
	turn++;

	if(getPiece(x, y) != 0 && getPiece(x, y)->isWhite() != p->isWhite())
	{
		enleverPiece(x, y);
	 	deplacer(current, x, y);
	}
	else
	{
	 	deplacer(current, x, y);
	}

	this->currentPlayer = !currentPlayer;
}


Piece*
Chessboard::getKing(bool blanc)
{
	for (int i = 0; i < m_size; ++i)
	{
		if(getPiece(i) != 0 )
		{
			if(dynamic_cast<King*>(getPiece(i)))
			{
				const King *r = dynamic_cast<King *>(getPiece(i));
				if(r->isWhite() == blanc )
					return m_cases[i];
			}
		}
	}

	return 0;
}

/**
* return 0 is not check nor checkmate
* return 1 is check
* return 2 is checkmate
*/
int Chessboard::statusPlayer(bool player)
{
	Piece *king = getKing(player);

	if(king != 0)
	{
		if(king->getAvailableMovements(*this)->size() == 0)
			return 2;

		for (int i = 0; i < m_size; ++i)
		{
			if(getPiece(i) != 0 && getPiece(i)->isWhite() != currentPlayer)
				if(getPiece(i)->mouvementValide(*this, king->x(), king->y()))
					return 1;
		}
	}

	return 0;
}

Piece*
Chessboard::enleverPiece( int x, int y )
{
 	Piece *p = getPiece(x, y);

 	m_cases[matrixToArrayPosition(x, y)] = 0;

 	return p;
}

vector<sf::Vector2i>*
Chessboard::availableMovements(Piece *p)
{
	if (statusPlayer(currentPlayer) != 0) {
		if (dynamic_cast<King *>(p)) {
			return p->getAvailableMovements(*this);
		} else {
			vector<Piece*> threats = getThreats();
			vector<sf::Vector2i>* availableMovements = new vector<sf::Vector2i>();
			for (int i = 0; i < threats.size(); i++) {
				if (p->mouvementValide(*this, threats[i]->x(), threats[i]->y())) {
					availableMovements->push_back(sf::Vector2i(threats[i]->x(), threats[i]->y()));
				}
			}
			return availableMovements;
		}
	}
	return p->getAvailableMovements(*this);
}

vector<Piece*>
Chessboard::getThreats()
{
	Piece *king = getKing(currentPlayer);
	vector<Piece*> threats;

	for (int i = 0; i < m_size; ++i)
	{
		if(getPiece(i) != 0 && getPiece(i)->isWhite() != currentPlayer)
			if(getPiece(i)->mouvementValide(*this, king->x(), king->y()))
				threats.push_back(getPiece(i));
	}

	return threats;
}

void
Chessboard::savePartie(string nameGame)
{
    ofstream myfile;

    myfile.open ("savedGames.txt",std::ios_base::app);
    myfile << nameGame << endl;
    myfile << turn << endl;

    for(int i = 0; i<m_size; i++)
			if(getPiece(i) != 0)
				myfile << getPiece(i)->toString() << "|" << getPiece(i)->x() << "|" << getPiece(i)->y() << ",";

		myfile << endl;

    myfile.close();
};

/* Cmd game */
void
Chessboard::playGame(WhitePlayer *jb, BlackPlayer *jn)
{
 	int loosed = 0;
 	bool invalidMove = true;
 	int x=0, y=0;
 	Piece *currentPiece;
 	vector<sf::Vector2i> *av = new vector<sf::Vector2i>();

 	int scoreW=0, scoreB=0;

 	while(!loosed)
 	{
 		cout << "Au Player " << ((currentPlayer) ? "blanc" : "noir") << " de Player" << endl;
 		cout << "Quel pawn choisissez vous ?" << endl;

 		do
 		{
 			cout << "Mauvaise selection, reessayez" << endl;
 			do {
 				cout << "Entrez x" << endl;
 				cin >> x;
 			} while (x <1 || x>8);
 			do {
 				cout << "Entrez y" << endl;
 				cin >> y;
 			} while(y < 1 || y > 8);

 			if(getPiece(x, y) != 0)
 				av = getPiece(x, y)->getAvailableMovements(*this);

 		} while((getPiece(x, y)->isWhite() != currentPlayer) || av->size() == 0 && getPiece(x, y) == 0);

 		currentPiece = enleverPiece(x, y);

 		while(invalidMove)
 		{

 			for (int i = 0; i < av->size(); ++i)
 			{
 				sf::Vector2i coor = (*av)[i];
 				cout << "x : " << coor.x << " y : " << coor.y << endl;
 			}

 			cout << "Entrez la case de destination: " << endl;

 			do {
 				cout << "Entrez x" << endl;
 				cin >> x;
 			} while (x <1 || x>8);
 			do {
 				cout << "Entrez y" << endl;
 				cin >> y;
 			} while(y < 1 || y > 8);

 			for (int i = 0; i < av->size(); ++i)
 			{
 				sf::Vector2i coor = (*av)[i];
 				if(x == coor.x && y == coor.y)
 					invalidMove = false;
 			}
 		}

 		if(getPiece(x, y) != NULL)
 			enleverPiece(x, y);

 		deplacer(currentPiece, x, y);

 		currentPlayer = !currentPlayer;

 		affiche();

 		invalidMove = true;
 		currentPiece = 0;
 		x = 0;
 		y = 0;
 		av->clear();
 	}
}

void
Chessboard::affiche()
{
 	stringstream stream;
 	stream << "\n" << "  12345678" << "\n";
 	for ( int y = 1; y <= 8; ++y )
 	{
 		stream << y << " ";
 		for ( int x = 1; x <= 8; ++x )
 		{
 			char c;
 			Piece* p = getPiece( x, y );
 			if ( p == 0 )
 				c = ( ( x + y ) % 2 ) == 0 ? '#' : '.';
 			else
 				c = p->getChar();
 			stream << c;
 		}
 		stream << " " << y << "\n";
 	}
 	stream << "  12345678" << "\n";

 	cout << stream.str() << endl;
}

void
Chessboard::affichage()
{
 	stringstream stream;
 	stream << "\n" << "  12345678" << "\n";
 	for ( int y = 1; y <= 8; ++y )
 	{
 		stream << y << " ";
 		for ( int x = 1; x <= 8; ++x )
 		{
 			char c;
 			Piece* p = getPiece( x, y );
 			if ( p == 0 )
 				c = '0';
 			else
 				c = '1';
 			stream << c;
 		}
 		stream << " " << y << "\n";
 	}
 	stream << "  12345678" << "\n";

 	cout << stream.str() << endl;
 }
