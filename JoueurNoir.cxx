#include <sstream>
#include "JoueurNoir.h"

using namespace std;

JoueurNoir::JoueurNoir() : Joueur()
{
	m_white = false;
	int x;

	for (x = 0; x < 8; x++)
		m_pieces[x] = new Pion(x+1, 7, false);

	m_pieces[x++] = new Tour(1, 8, false);
	m_pieces[x++] = new Tour(8, 8, false);
	m_pieces[x++] = new Cavalier(7, 8, false);
	m_pieces[x++] = new Cavalier(2, 8, false);
	m_pieces[x++] = new Fou(6, 8, false);
	m_pieces[x++] = new Fou(3, 8, false);
	m_pieces[x++] = new Reine(false);
	m_pieces[x] = new Roi(false);

}

JoueurNoir::~JoueurNoir()
{}

string
JoueurNoir::toString() const
{
	stringstream stream;
	stream << "========= Joueur Noir =========\n";
	stream << Joueur::toString();
	stream << "================================\n";

	return stream.str();
}
