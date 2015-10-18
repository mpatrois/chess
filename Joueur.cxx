#include <sstream>
#include "Joueur.h"

using namespace std;

Joueur::Joueur(): m_pieces(18)
{}

Joueur::~Joueur()
{
	cout << "Destructeur joueur" << endl;
	for (int i = 0; i < m_pieces.size(); ++i)
		if(m_pieces[i] != NULL)
			delete m_pieces[i];
}

bool
Joueur::placeEveryPiecesOn(Echiquier *ec)
{
	cout << "placeEveryPiecesOn" << endl;
	for (int i = 0; i < m_pieces.size(); ++i)
		if(ec->placer(m_pieces[i]) != true)
			return false;
}

bool
Joueur::alreadyHasAPiece(Piece *p) const
{
	for (int i = 0; i < m_pieces.size(); ++i)
		if(m_pieces[i]->isAtTheSamePlace(*p))
			return true;

	return false;
}

string
Joueur::toString() const
{
	stringstream stream;

	for(int i = 0; i < m_pieces.size(); i++)
		stream << m_pieces[i]->toString();

	return stream.str();
}
