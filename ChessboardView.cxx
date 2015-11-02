/**
 * Mise en oeuvre de Chessboard.h
 *
 * @file Chessboard.cxx
 */

#include "ChessboardView.h"
#include "Chessboard.h"
#include "Player.h"


using namespace std;

ChessboardView::ChessboardView(Chessboard *chessB)
{
    chessboardModel=chessB;

    font.loadFromFile("ressources/dreamwalker.ttf");

    texturePiece.loadFromFile("ressources/chess.png");

    spritePieces=sf::Sprite(texturePiece);
}

ChessboardView::~ChessboardView(){

};

void
ChessboardView::graphicDisplay(sf::RenderWindow &app)
{
    sf::Text text;

    text.setFont(font);
    text.setString("Player en cours");
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Underlined);
    text.setPosition(500,130);

    app.draw(text);

    sf::Sprite spritePlayerEnCours=spritePieces;
    spritePlayerEnCours.setTextureRect(chessboardModel->getCurrentPlayer()->getKing()->getRectPiece());
    spritePlayerEnCours.setPosition(500,160);
    app.draw(spritePlayerEnCours);

    sf::RectangleShape rc = sf::RectangleShape(sf::Vector2f(60, 60));

    for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			rc.setPosition(i*60, j*60);
			if ((i + j)%2 == 0)
				rc.setFillColor(sf::Color(139,155,181));
			else
				rc.setFillColor(sf::Color::White);

            app.draw(rc);
		}
	}

    drawJoueur(app,chessboardModel->getPlayerWhite());
    drawJoueur(app,chessboardModel->getPlayerBlack());
}

void ChessboardView::setModel(Chessboard *chessB){
    chessboardModel=chessB;
}

void ChessboardView::drawJoueur(sf::RenderWindow &app,Player *player){

    if(player->isEchec(chessboardModel))
    {
        sf::CircleShape circle(30);

        circle.setFillColor(sf::Color::Red);
        circle.setPosition(player->getKing()->x()*60,player->getKing()->y()*60);

        app.draw(circle);
    }

    if(player->getPieceSelected()!=NULL)
    {
        sf::RectangleShape rectangle;

        rectangle.setSize(sf::Vector2f(60, 60));
        rectangle.setFillColor(sf::Color(81,124,102));
        rectangle.setPosition(player->getPieceSelected()->x()*60,player->getPieceSelected()->y()*60);

        app.draw(rectangle);

        std::vector<Square> listCase=player->listeMouvementPossible(chessboardModel);

        for (unsigned int j=0; j<listCase.size(); j++)
        {
            if(! player->willBeEchec(listCase[j].x,listCase[j].y) )
            {
                sf::CircleShape circle(26);

                circle.setFillColor(sf::Color(81,124,102,0));
                circle.setOutlineColor(sf::Color(81,124,102));
                circle.setOutlineThickness(2);

                circle.setPosition(listCase[j].x*60+4,listCase[j].y*60+4);

                app.draw(circle);
            }
        }
    }

    vector<Piece *> playerPieces=player->getPieces();
    for (unsigned int x=0; x<playerPieces.size(); x++)
    {
        spritePieces.setTextureRect(playerPieces[x]->getRectPiece());
        spritePieces.setPosition(playerPieces[x]->x()*60+1,playerPieces[x]->y()*60);
        app.draw(spritePieces);
    }
}

Partie ChessboardView::chargerPartie(sf::RenderWindow &app,sf::Sprite sprite,sf::Font font)
{
    bool choose=false;

    unsigned int choice=0;

    vector<Partie> listParties=Utility::listePartie();

    listParties.push_back(Partie("Annuler","Annuler"));

    sf::Event event;

    while(!choose)
    {
        while (app.pollEvent(event))
        {

            if (event.type==sf::Event::KeyPressed)
            {
                if(sf::Keyboard::Up==event.key.code)
                {
                    if(choice>0)
                    {
                        choice--;
                    }
                }
                else if(sf::Keyboard::Down==event.key.code)
                {
                    if(choice<listParties.size()-1)
                    {
                        choice++;
                    }
                }
                else if(sf::Keyboard::Return==event.key.code)
                    choose=true;
            }
        }

        app.clear(sf::Color(238,238,238));
        app.draw(sprite);

        for(unsigned int i=0; i<listParties.size(); i++)
        {
            sf::Text text(listParties[i].name,font,40);

            text.setColor(sf::Color::White);

            if(i==choice)
                text.setStyle(sf::Text::Underlined);

            text.setPosition(360,100+i*60);

            app.draw(text);
        }
        app.display();
    }
    return listParties[choice];
}

int ChessboardView::menu(sf::RenderWindow &app,sf::Sprite sprite,sf::Font font)
{
    bool choose=false;
    int choice=0;

    sf::Text texts[3];

    texts[0]=sf::Text("Jouer",font,40);
    texts[1]=sf::Text("Charger",font,40);
    texts[2]=sf::Text("Quitter",font,40);


    sf::Event event;

    while(!choose)
    {
        while (app.pollEvent(event))
        {

            if (event.type==sf::Event::KeyPressed)
            {
                if(sf::Keyboard::Up==event.key.code)
                {
                    if(choice>0)
                    {
                        choice--;
                    }
                }
                else if(sf::Keyboard::Down==event.key.code)
                {
                    if(choice<2)
                    {
                        choice++;
                    }
                }
                else if(sf::Keyboard::Return==event.key.code)
                    choose=true;

            }

        }
        app.clear(sf::Color(238,238,238));
        app.draw(sprite);
        for(int i=0; i<3; i++)
        {
            texts[i].setColor(sf::Color::White);
            if(i==choice)
                texts[i].setStyle(sf::Text::Underlined);
            else
                texts[i].setStyle(sf::Text::Regular);

            texts[i].setPosition(360,100+i*60);
            app.draw(texts[i]);

        }
        app.display();
    }
    return choice;
}

