#include "MainFrame.h"
#include "Utils.h"

MainFrame::MainFrame(Echiquier *e): echiquier(e)
{
	window        = new sf::RenderWindow(sf::VideoMode(700, 750), "SFML works!");
	background    = std::vector<sf::Shape*>();
	foreground    = std::vector<sf::Shape*>();
	pieces        = std::vector<sf::Sprite>();
	texts		  = std::vector<sf::Text>();
	selectedPiece = 0;

	if(!chestPieces.loadFromFile("ressources/Chess_Pieces_Sprite.png"))
	std::cerr << "Error while loading chest pieces" << std::endl;

	if(!font.loadFromFile("ressources/OpenSans-Semibold.ttf"))
	std::cerr << "Error while loading OpenSans font" << std::endl;

	for (int i = 1; i < 9; ++i)
	{
		for (int j = 1; j < 9; ++j)
		{
			sf::RectangleShape *rc = new sf::RectangleShape(sf::Vector2f(80, 80));
			rc->setPosition(i*80-50, j*80-50);
			if ((i + j)%2 == 0)
			rc->setFillColor(sf::Color(64,63,62, 255));
			else
			rc->setFillColor(sf::Color::White);
			background.push_back(rc);
		}
	}

	roiBlancRectangle      = sf::IntRect(0, 0, 36, 36);
	reineBlancRectangle    = sf::IntRect(36, 0, 36, 36);
	fouBlancRectangle      = sf::IntRect(72, 0, 36, 36);
	cavalierBlancRectangle = sf::IntRect(108, 0, 36, 36);
	tourBlancRectangle     = sf::IntRect(144, 0, 36, 36);
	pionBlancRectangle     = sf::IntRect(182, 0, 36, 36);

	roiNoirRectangle       = sf::IntRect(0, 36, 36, 36);
	reineNoirRectangle     = sf::IntRect(36, 36, 36, 36);
	fouNoirRectangle       = sf::IntRect(72, 36, 36, 36);
	cavalierNoirRectangle  = sf::IntRect(108, 36, 36, 36);
	tourNoirRectangle      = sf::IntRect(144, 36, 36, 36);
	pionNoirRectangle      = sf::IntRect(182, 36, 36, 36);

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
		Piece *p = echiquier->getPiece(i);
		if(p != 0)
		{
			sf::Sprite s(chestPieces);
			if (p->isWhite())
			{
				if(dynamic_cast<Pion*>(p))
				s.setTextureRect(pionBlancRectangle);
				else if(dynamic_cast<Reine*>(p))
				s.setTextureRect(reineBlancRectangle);
				else if(dynamic_cast<Roi*>(p))
				s.setTextureRect(roiBlancRectangle);
				else if(dynamic_cast<Fou*>(p))
				s.setTextureRect(fouBlancRectangle);
				else if(dynamic_cast<Tour*>(p))
				s.setTextureRect(tourBlancRectangle);
				else if(dynamic_cast<Cavalier*>(p))
				s.setTextureRect(cavalierBlancRectangle);
			}
			else
			{
				if(dynamic_cast<Pion*>(p))
				s.setTextureRect(pionNoirRectangle);
				else if(dynamic_cast<Reine*>(p))
				s.setTextureRect(reineNoirRectangle);
				else if(dynamic_cast<Roi*>(p))
				s.setTextureRect(roiNoirRectangle);
				else if(dynamic_cast<Fou*>(p))
				s.setTextureRect(fouNoirRectangle);
				else if(dynamic_cast<Tour*>(p))
				s.setTextureRect(tourNoirRectangle);
				else if(dynamic_cast<Cavalier*>(p))
				s.setTextureRect(cavalierNoirRectangle);
			}

			s.setScale(2, 2);
			s.setPosition(p->y()*80-50, p->x()*80-50);
			pieces.push_back(s);
		}
	}

	for (int i = 0; i < pieces.size(); ++i)
	window->draw(pieces[i]);
}

void MainFrame::drawEchecStatus()
{
	std::string content = "Echec du joueur ";
	sf::Text t(content, font, 30);
	if(echiquier->statusPlayer(false))
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
	if(echiquier->statusPlayer(true) == 2 && echiquier->statusPlayer(false) == 2)
	content = "Egalite !";
	else
	content += (echiquier->statusPlayer(false) == 2 ? "noir" : "blanc");

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

	if (echiquier->statusPlayer(true) || echiquier->statusPlayer(false))
	{
		drawEchecStatus();
		if (echiquier->statusPlayer(true) == 2 || echiquier->statusPlayer(false) == 2)
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
		  return echiquier->getPiece(coordinate);
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
		if (p->isWhite() == echiquier->getCurrentPlayer())
		{
			selectedPiece = p;
			drawPossibleMoves(p, position);
		}
	}
	else
	{
		for (unsigned int i = 0; i < foreground.size(); ++i)
			delete foreground[i];

		foreground.clear();

		if(selectedPiece != 0)
		{
			std::vector<sf::Vector2i> *availables = selectedPiece->getAvailableMovements(*echiquier);
			for (int i = 0; i < availables->size(); ++i)
			if((*availables)[i].x == mouseToCoordinate(position.y) && (*availables)[i].y == mouseToCoordinate(position.x))
			{
				echiquier->jouerPiece(selectedPiece, mouseToCoordinate(position.y), mouseToCoordinate(position.x));
				addText();
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
			sf::RectangleShape rs(sf::Vector2f(80, 5));
			sf::RectangleShape rs1(sf::Vector2f(5, 80));
			sf::RectangleShape rs2(sf::Vector2f(80, 5));
			sf::RectangleShape rs3(sf::Vector2f(5, 80));

			rs.setPosition(s->getPosition().x, s->getPosition().y);
			rs.setFillColor(sf::Color::Green);
			rs1.setPosition(s->getPosition().x, s->getPosition().y);
			rs1.setFillColor(sf::Color::Green);
			rs2.setPosition(s->getPosition().x, s->getPosition().y+75);
			rs2.setFillColor(sf::Color::Green);
			rs3.setPosition(s->getPosition().x+75, s->getPosition().y);
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
			&& (shape->getPosition().x + 80) > position->x && (shape->getPosition().y + 80) > position->y);
}

void MainFrame::drawPossibleMoves(Piece* p, sf::Vector2i position)
{
	std::vector<sf::Vector2i> *v = p->getAvailableMovements(*echiquier);
	int x = position.x;
	int y = position.y;

	deleteForeground();

	for (int i = 0; i < v->size(); ++i)
	{
		int y = ((*v)[i].x-1)*80+30;
		int x = ((*v)[i].y-1)*80+30;

		sf::RectangleShape *rs  = new sf::RectangleShape(sf::Vector2f(80, 5));
		sf::RectangleShape *rs1 = new sf::RectangleShape(sf::Vector2f(5, 80));
		sf::RectangleShape *rs2 = new sf::RectangleShape(sf::Vector2f(80, 5));
		sf::RectangleShape *rs3 = new sf::RectangleShape(sf::Vector2f(5, 80));

		rs->setPosition(x, y);
		rs->setFillColor(sf::Color::Blue);
		rs1->setPosition(x, y);
		rs1->setFillColor(sf::Color::Blue);
		rs2->setPosition(x, y+75);
		rs2->setFillColor(sf::Color::Blue);
		rs3->setPosition(x+75, y);
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
