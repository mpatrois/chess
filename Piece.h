/**
 * Header de Piece.cxx
 *
 * @file Piece.h
 */

#ifndef PIECE_H
#define PIECE_H

#include <sstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/System.hpp>
#include "Echiquier.h"

class Echiquier;

class Piece
{
private:
  int m_x;
  int m_y;
  bool m_white;
  std::vector<sf::Vector2i> *availableMovements;

public:
  Piece();
  Piece(int x, int y, bool white);
  Piece(const Piece & p);
  Piece & operator= (const Piece & p);
  ~Piece();

  void init( int x, int y, bool white );
  virtual void move( int x, int y );
  int x() const;
  int y() const;
  bool isWhite() const;
  bool isAtTheSamePlace(Piece &p) const;
  virtual bool mouvementValide(Echiquier & e, int x, int y) = 0;
  virtual char getChar() const = 0;
  virtual std::string toString() const;

  std::vector<sf::Vector2i>* getAvailableMovements(Echiquier &e);

};

#endif
