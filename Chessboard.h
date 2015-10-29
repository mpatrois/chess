/**
 * Header de Chessboard.cxx
 *
 * @file Chessboard.h
 */

#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include "Utils.h"
#include "Piece.h"
#include <fstream>

class Piece;
class WhitePlayer;
class BlackPlayer;

class Chessboard
{
public:
  static const int m_size = 64;

private:
  Piece * m_cases[ m_size ];
  bool currentPlayer;
  int turn;

public:
  Chessboard();
  ~Chessboard();

  Piece* getPiece( int x, int y );
  Piece* getPiece( int place );

  bool getCurrentPlayer() const;
  bool placer( Piece* p );
  bool deplacer( Piece* p, int x, int y );
  void jouerPiece(Piece* p, int x, int y);
  void playGame(WhitePlayer *jb, BlackPlayer *jn);
  bool hasLost(Piece *p);
  Piece* enleverPiece( int x, int y );
  Piece* getKing(bool player);
  int statusPlayer(bool player);
  std::vector<sf::Vector2i>* availableMovements(Piece *p);
  std::vector<Piece*> getThreats();

  void savePartie(std::string nameFile);

  void affiche();
  void affichage();

};

#endif
