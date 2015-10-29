#include "MainFrame.h"
#include "Utils.h"

MainFrame::MainFrame(Chessboard *e): chessboard(e)
{
	window     = new sf::RenderWindow(sf::VideoMode(700, 500), "SFML works!");
	background = std::vector<sf::Shape*>();
	foreground = std::vector<sf::Shape*>();
	pieces     = std::vector<sf::Sprite>();
	buttons    = std::vector<sf::Sprite>();
	texts      = std::vector<sf::Text>();
	selectedPiece = 0;

	if(!chestPieces.loadFromFile("ressources/chess.png"))
		std::cerr << "Error while loading chest pieces" << std::endl;

	if(!back.loadFromFile("ressources/back.png"))
		std::cerr << "Error while loading back icon" << std::endl;

	if(!save.loadFromFile("ressources/save.png"))
		std::cerr << "Error while loading save icon" << std::endl;

	if(!font.loadFromFile("ressources/OpenSans-Semibold.ttf"))
		std::cerr << "Error while loading OpenSans font" << std::endl;

	for (int i = 1; i < 9; ++i)
	{
		for (int j = 1; j < 9; ++j)
		{
			sf::RectangleShape *rc = new sf::RectangleShape(sf::Vector2f(60, 60));
			rc->setPosition(i*60-50, j*60-50);
			if ((i + j)%2 == 0)
				rc->setFillColor(sf::Color(64,63,62, 255));
			else
				rc->setFillColor(sf::Color::White);
			background.push_back(rc);
		}
	}

	whitePawnRectangle   = sf::IntRect(60, 0, 60, 60);
	whiteKnightRectangle = sf::IntRect(60, 60, 60, 60);
	whiteBishopRectangle = sf::IntRect(60, 120, 60, 60);
	whiteRookRectangle   = sf::IntRect(60, 180, 60, 60);
	whiteQueenRectangle  = sf::IntRect(60, 240, 60, 60);
	whiteKingRectangle   = sf::IntRect(60, 300, 60, 60);

	blackPawnRectangle    = sf::IntRect(0, 0, 60, 60);
	blackKnightRectangle  = sf::IntRect(0, 60, 60, 60);
	blackBishopRectangle  = sf::IntRect(0, 120, 60, 60);
	blackRookRectangle    = sf::IntRect(0, 180, 60, 60);
	blackQueenRectangle   = sf::IntRect(0, 240, 60, 60);
	blackKingRectangle    = sf::IntRect(0, 300, 60, 60);

	window->clear(sf::Color(191, 190, 187, 200));
}

MainFrame::~MainFrame()
{
	for (int i = 0; i < background.size(); ++i)
		delete background[i];

	background.clear();

	deleteForeground();

	pieces.clear();
	texts.clear();

	delete window;
}

void MainFrame::drawPieces()
{
	for (int i = 0; i < 64; ++i)
	{
		Piece *p = chessboard->getPiece(i);
		if(p != 0)
		{
			sf::Sprite s(chestPieces);
			if (p->isWhite())
			{
				if(dynamic_cast<Pawn*>(p))
					s.setTextureRect(whitePawnRectangle);
				else if(dynamic_cast<Queen*>(p))
					s.setTextureRect(whiteQueenRectangle);
				else if(dynamic_cast<King*>(p))
					s.setTextureRect(whiteKingRectangle);
				else if(dynamic_cast<Bishop*>(p))
					s.setTextureRect(whiteBishopRectangle);
				else if(dynamic_cast<Rook*>(p))
					s.setTextureRect(whiteRookRectangle);
				else if(dynamic_cast<Knight*>(p))
					s.setTextureRect(whiteKnightRectangle);
			}
			else
			{
				if(dynamic_cast<Pawn*>(p))
					s.setTextureRect(blackPawnRectangle);
				else if(dynamic_cast<Queen*>(p))
					s.setTextureRect(blackQueenRectangle);
				else if(dynamic_cast<King*>(p))
					s.setTextureRect(blackKingRectangle);
				else if(dynamic_cast<Bishop*>(p))
					s.setTextureRect(blackBishopRectangle);
				else if(dynamic_cast<Rook*>(p))
					s.setTextureRect(blackRookRectangle);
				else if(dynamic_cast<Knight*>(p))
					s.setTextureRect(blackKnightRectangle);
			}

			s.setScale(1, 1);
			s.setPosition(p->y()*60-50, p->x()*60-50);
			pieces.push_back(s);
		}
	}

	for (int i = 0; i < pieces.size(); ++i)
	window->draw(pieces[i]);
}

void MainFrame::drawEchecStatus()
{
	std::string content = "Echec du Player ";
	sf::Text t(content, font, 30);
	if(chessboard->statusPlayer(false))
	{
		content += "noir";
		t.setPosition(50, 710);
	}
	else
	{
		content += "blanc";
		t.setPosition(50, 680);
	}
	t.setString(content);
	t.setColor(sf::Color::Black);

	texts.push_back(t);
}

void MainFrame::drawLooserColor()
{
	std::string content = "Echec et mat ";
	if(chessboard->statusPlayer(true) == 2 && chessboard->statusPlayer(false) == 2)
	content = "Egalite !";
	else
	content += (chessboard->statusPlayer(false) == 2 ? "noir" : "blanc");

	sf::Text t(content, font, 50);
	t.setPosition(100, 350);
	t.setColor(sf::Color::Black);

	texts.push_back(t);
}

void MainFrame::drawText()
{
	for (int i = 0; i < texts.size(); ++i)
		window->draw(texts[i]);
}

void MainFrame::addText()
{
	texts.clear();

	if (chessboard->statusPlayer(true) || chessboard->statusPlayer(false))
	{
		drawEchecStatus();
		if (chessboard->statusPlayer(true) == 2 || chessboard->statusPlayer(false) == 2)
			drawLooserColor();
	}
}

void MainFrame::hideText()
{
	sf::RectangleShape rs(sf::Vector2f(400, 100));
	rs.setPosition(40, 680);
	rs.setFillColor(sf::Color(191, 190, 187, 255));

	window->draw(rs);
}

Piece* MainFrame::pieceOnMouse(int coordinate, sf::Vector2i position)
{
	for (int i = 0; i < background.size(); ++i)
	{
		sf::Shape* s = background[i];
		if(isOnShape(s, &position))
		  return chessboard->getPiece(coordinate);
	}
}

void MainFrame::buttonPressed()
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);
	Piece *p = 0;
	int coordinate = mouseCoordinatesToPosition(position.x, position.y, window->getSize().x);

	deleteForeground();

	p = pieceOnMouse(coordinate, position);

	if(p != 0 && p != NULL && selectedPiece == 0)
	{
		if (p->isWhite() == chessboard->getCurrentPlayer())
		{
			selectedPiece = p;
			drawPossibleMoves(p, position);
		}
	}
	else
	{
		deleteForeground();

		if(selectedPiece != 0)
		{
			std::vector<sf::Vector2i> *availables = selectedPiece->getAvailableMovements(*chessboard);
			for (int i = 0; i < availables->size(); ++i)
			{
				if((*availables)[i].x == mouseToCoordinate(position.y) && (*availables)[i].y == mouseToCoordinate(position.x))
				{
					chessboard->jouerPiece(selectedPiece, mouseToCoordinate(position.y), mouseToCoordinate(position.x));
					addText();
				}
			}

			selectedPiece = 0;

			availables->clear();
		}
	}
}

void MainFrame::mousePosition()
{
	sf::Vector2i position = sf::Mouse::getPosition(*window);

	for (int i = 0; i < background.size(); ++i)
	{
		sf::Shape* s = background[i];
		if(isOnShape(s, &position))
		{
			sf::RectangleShape rs(sf::Vector2f(60, 5));
			sf::RectangleShape rs1(sf::Vector2f(5, 60));
			sf::RectangleShape rs2(sf::Vector2f(60, 5));
			sf::RectangleShape rs3(sf::Vector2f(5, 60));

			rs.setPosition(s->getPosition().x, s->getPosition().y);
			rs.setFillColor(sf::Color::Green);
			rs1.setPosition(s->getPosition().x, s->getPosition().y);
			rs1.setFillColor(sf::Color::Green);
			rs2.setPosition(s->getPosition().x, s->getPosition().y+55);
			rs2.setFillColor(sf::Color::Green);
			rs3.setPosition(s->getPosition().x+55, s->getPosition().y);
			rs3.setFillColor(sf::Color::Green);

			window->draw(rs);
			window->draw(rs1);
			window->draw(rs2);
			window->draw(rs3);
		}
	}
}

bool MainFrame::isOnShape(sf::Shape *shape, sf::Vector2i *position)
{
	return (shape->getPosition().x < position->x && shape->getPosition().y < position->y
			&& (shape->getPosition().x + 60) > position->x && (shape->getPosition().y + 60) > position->y);
}

void MainFrame::drawPossibleMoves(Piece* p, sf::Vector2i position)
{
	std::vector<sf::Vector2i> *v = chessboard->availableMovements(p);
	int x = position.x;
	int y = position.y;

	deleteForeground();

	for (int i = 0; i < v->size(); ++i)
	{
		int y = ((*v)[i].x-1)*60+10;
		int x = ((*v)[i].y-1)*60+10;

		sf::RectangleShape *rs  = new sf::RectangleShape(sf::Vector2f(60, 5));
		sf::RectangleShape *rs1 = new sf::RectangleShape(sf::Vector2f(5, 60));
		sf::RectangleShape *rs2 = new sf::RectangleShape(sf::Vector2f(60, 5));
		sf::RectangleShape *rs3 = new sf::RectangleShape(sf::Vector2f(5, 60));

		rs->setPosition(x, y);
		rs->setFillColor(sf::Color::Blue);
		rs1->setPosition(x, y);
		rs1->setFillColor(sf::Color::Blue);
		rs2->setPosition(x, y+55);
		rs2->setFillColor(sf::Color::Blue);
		rs3->setPosition(x+55, y);
		rs3->setFillColor(sf::Color::Blue);

		foreground.push_back(rs);
		foreground.push_back(rs1);
		foreground.push_back(rs2);
		foreground.push_back(rs3);
	}
}

void MainFrame::eventLoop()
{
	sf::Clock clock;
	sf::Time elapsed;

	addText();

	while (window->isOpen())
	{
		elapsed = clock.getElapsedTime();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window->close();
		}

		for (unsigned int i = 0; i < background.size(); ++i)
			window->draw(*background[i]);

		for(unsigned int i = 0; i < foreground.size(); ++i)
			window->draw(*foreground[i]);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && elapsed.asMilliseconds() > 100)
		{
			elapsed = clock.restart();
			buttonPressed();
		}

		mousePosition();
		drawPieces();
		hideText();
		drawText();

		window->display();

		pieces.clear();
	}
}

void
MainFrame::deleteForeground()
{
	for (unsigned int i = 0; i < foreground.size(); ++i)
		delete foreground[i];

	foreground.clear();
}
