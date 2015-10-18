#include "Piece.h"

using namespace std;

Piece::Piece()
{
  availableMovements = new std::vector<sf::Vector2i>();
}

Piece::Piece(int x, int y, bool white): m_x(x), m_y(y), m_white(white) 
{
  availableMovements = new std::vector<sf::Vector2i>();
}

Piece::Piece(const Piece & p)
{
  m_x = p.m_x;
  m_y = p.m_y;
  m_white = p.m_white;
  cout << "Constructeur par copie piece" << endl;
}

Piece & Piece::operator= (const Piece & p)
{
  m_x = p.m_x;
  m_y = p.m_y;
  m_white = p.m_white;
  cout << "Constructeur par copie piece operator=" << endl;
  return *this;
}


Piece::~Piece() {
  delete availableMovements;
}

void
Piece::init( int x, int y, bool white )
{
  m_x = x;
  m_y = y;
  m_white = white;
}

void
Piece::move( int x, int y )
{
  m_x = x;
  m_y = y;
}

int
Piece::x() const
{
  return m_x;
}

int
Piece::y() const
{
  return m_y;
}

bool
Piece::isWhite() const
{
  return m_white;
}

bool
Piece::isAtTheSamePlace(Piece &p) const
{
	return m_y == p.y() && m_x == p.x();
}

std::vector<sf::Vector2i> * 
Piece::getAvailableMovements(Echiquier &e)
{
  availableMovements->clear();

  for (int i = 1; i < 9; ++i)
    for (int j = 1; j < 9; ++j)
      if(mouvementValide(e, i, j))
        availableMovements->push_back(sf::Vector2i(i, j));

  return availableMovements;
}

string
Piece::toString() const
{
	stringstream stream;
  stream << "\nx : " << m_x << "\ny : " << m_y << "\nCouleur : " << (m_white ? "Blanc\n" : "Noir\n");
	return stream.str();
}