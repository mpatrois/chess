/**
 * Header de Echiquier.cxx
 *
 * @file Echiquier.h
 */

#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include "Utils.h"
#include "Piece.h"

class Piece;
class JoueurBlanc;
class JoueurNoir;

class Echiquier
{
public:
  static const int m_size = 64;

private:
  Piece * m_cases[ m_size ];
  bool currentPlayer;

public:
  Echiquier();
  ~Echiquier();

  Piece* getPiece( int x, int y );
  Piece* getPiece( int place );

  bool getCurrentPlayer() const;
  bool placer( Piece* p );
  bool deplacer( Piece* p, int x, int y );
  void jouerPiece(Piece* p, int x, int y);
  void playGame(JoueurBlanc *jb, JoueurNoir *jn);
  bool hasLost(Piece *p);
  Piece* enleverPiece( int x, int y );
  Piece* getRoi(bool player);
  int statusPlayer(bool player);


  void affiche();
  void affichage();

};

#endif
