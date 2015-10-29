#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Chessboard.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"


class MainFrame
{
private:
	sf::RenderWindow *window;
	sf::Texture chestPieces;
	sf::Texture back;
	sf::Texture save;
	sf::Font font;

	std::vector<sf::Shape*> background;
	std::vector<sf::Shape*> foreground;
	std::vector<sf::Sprite> pieces;
	std::vector<sf::Sprite> buttons;
	std::vector<sf::Text> texts;

	Chessboard * chessboard;
	Piece * selectedPiece;

	sf::IntRect blackPawnRectangle;
	sf::IntRect blackKnightRectangle;
	sf::IntRect blackQueenRectangle;
	sf::IntRect blackKingRectangle;
	sf::IntRect blackBishopRectangle;
	sf::IntRect blackRookRectangle;
	sf::IntRect whitePawnRectangle;
	sf::IntRect whiteKnightRectangle ;
	sf::IntRect whiteQueenRectangle;
	sf::IntRect whiteKingRectangle;
	sf::IntRect whiteBishopRectangle;
	sf::IntRect whiteRookRectangle;

protected:
	bool isOnShape(sf::Shape *shape, sf::Vector2i *position);

public:
	MainFrame();
	MainFrame(Chessboard *e);
	~MainFrame();

	void drawPieces();
	void drawEchecStatus();
	void drawLooserColor();
	void drawText();
	void addText();
	void hideText();
	Piece* pieceOnMouse(int coordinate, sf::Vector2i position);
	void buttonPressed();
	void mousePosition();
	void drawPossibleMoves(Piece * p, sf::Vector2i position);

	void eventLoop();
	void deleteForeground();

};

#endif
