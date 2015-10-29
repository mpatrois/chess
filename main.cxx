/**
 * Programme test de Piece
 *
 * @file testPiece.cxx
 */

// Utile pour l'affichage
#include <iostream>
#include "Chessboard.h"
#include "Player.h"
#include "BlackPlayer.h"
#include "WhitePlayer.h"
#include "MainFrame.h"

// Pour utiliser les flux de iostream sans mettre "std::" tout le temps.
using namespace std;

/**
 * Programme principal
 */
int main()
{

  Chessboard *ec = new Chessboard();
  MainFrame *f = new MainFrame(ec);

  // On l'affiche
	BlackPlayer black;
	WhitePlayer white;

	black.placeEveryPiecesOn(ec);
	white.placeEveryPiecesOn(ec);

  //bouge certaines pieces blanches
  ec->deplacer(ec->getPiece(3, 2), 3, 6);
  ec->deplacer(ec->getPiece(2, 1), 4, 5);
  ec->deplacer(ec->getPiece(5, 2), 5, 4);
  ec->deplacer(ec->getPiece(5, 1), 6, 5);


  //bouge certaines pieces noirs
  ec->deplacer(ec->getPiece(7, 7), 7, 5);
  ec->deplacer(ec->getPiece(5, 7), 5, 4);
  ec->deplacer(ec->getPiece(5, 8), 4, 6);
	// ec->affiche();
  // ec->playGame(&white, &black);

  f->eventLoop();

  delete f;
  delete ec;


  // les objets definis dans cette fonction sont automatiquement d�truits.
  // Ex : p1
  return 0;
}
