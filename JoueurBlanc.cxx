#include <sstream>
#include "JoueurBlanc.h"

using namespace std;

JoueurBlanc::JoueurBlanc() : Joueur()
{
	m_white = true;
	int x;

	for (x = 0; x < 8; x++)
		m_pieces[x] = new Pion(x+1, 2, true);

	m_pieces[x++] = new Tour(1, 1, true);
	m_pieces[x++] = new Cavalier(2, 1, true);
	m_pieces[x++] = new Fou(3, 1, true);
	m_pieces[x++] = new Fou(6, 1, true);
	m_pieces[x++] = new Cavalier(7, 1, true);
	m_pieces[x++] = new Tour(8, 1, true);
	m_pieces[x++] = new Reine(true);
	m_pieces[x] = new Roi(true);
}

JoueurBlanc::~JoueurBlanc()
{}

string
JoueurBlanc::toString() const
{
	stringstream stream;
	stream << "========= Joueur Blanc =========\n";
	stream << Joueur::toString();
	stream << "================================\n";

	return stream.str();
}
