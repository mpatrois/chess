#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Echiquier.h"
#include "Pion.h"
#include "Roi.h"
#include "Fou.h"
#include "Cavalier.h"
#include "Tour.h"
#include "Reine.h"


class MainFrame
{
private:
	sf::RenderWindow *window;
	sf::Texture chestPieces;
	sf::Font font;

	std::vector<sf::Shape*> background;
	std::vector<sf::Shape*> foreground;
	std::vector<sf::Sprite> pieces;
	std::vector<sf::Text> texts;

	Echiquier * echiquier;
	Piece * selectedPiece;

	sf::IntRect pionNoirRectangle;
	sf::IntRect cavalierNoirRectangle;
	sf::IntRect reineNoirRectangle;
	sf::IntRect roiNoirRectangle;
	sf::IntRect fouNoirRectangle;
	sf::IntRect tourNoirRectangle;
	sf::IntRect pionBlancRectangle;
	sf::IntRect cavalierBlancRectangle ;
	sf::IntRect reineBlancRectangle;
	sf::IntRect roiBlancRectangle;
	sf::IntRect fouBlancRectangle;
	sf::IntRect tourBlancRectangle;

protected:
	bool isOnShape(sf::Shape *shape, sf::Vector2i *position);

public:
	MainFrame();
	MainFrame(Echiquier *e);
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
