#include <SFML/Graphics.hpp>
#include "Chessboard.h"
#include "ChessboardView.h"
#include "Actions.h"

using namespace std;

sf::Font font;
sf::Texture texture;

class OkDialog : public sf::RenderWindow
{

private:
    string message;

public:

    OkDialog(string mess):sf::RenderWindow()
    {
        message=mess;
    };

    void showDialog()
    {
        sf::Event event;

        sf::Text messageText(message,font,30);
        sf::Text pressAkey("Appuyez sur une touche",font,30);

        messageText.setPosition(200-messageText.getGlobalBounds().width/2,100);
        pressAkey.setPosition(50,350);
        messageText.setColor(sf::Color::Black);
        pressAkey.setColor(sf::Color::Black);

        bool quit=false;

        this->create(sf::VideoMode(400, 400), "Echec et mat");
        this->clear(sf::Color(238,238,238));
        this->draw(messageText);
        this->draw(pressAkey);
        this->display();

        while (this->isOpen() && !quit)
            while (this->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    quit=true;
                }

                if (event.type ==sf::Event::KeyPressed && sf::Keyboard::Return==event.key.code)
                {
                    quit=true;
                }
            }
    }
};

class InputDialog : public sf::RenderWindow
{

public:

    InputDialog():sf::RenderWindow() {};

    std::string showDialog()
    {
        sf::Event event;


        sf::Text enterName("Enter a name",font,40);
        sf::Text nameEntered("",font,40);

        enterName.setPosition(200-enterName.getGlobalBounds().width/2,100);
        nameEntered.setPosition(200-enterName.getGlobalBounds().width/2,150);
        enterName.setColor(sf::Color::Black);
        nameEntered.setColor(sf::Color::Black);

        bool quit=false;

        this->create(sf::VideoMode(400, 400), "Choississez un nom");
        this->clear(sf::Color(238,238,238));
        this->draw(enterName);
        this->draw(nameEntered);
        this->display();

        while (this->isOpen() && !quit)
            while (this->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    quit=true;
                }
                else if (event.type ==sf::Event::TextEntered)
                {


                    if(event.text.unicode>65 && event.text.unicode<122)
                    {
                        std::string tex=nameEntered.getString();

                        if(tex.size()<12)
                        {
                            tex+=(char)event.text.unicode;
                            nameEntered.setString(tex);
                        }
                    }


                }
                else if (event.type ==sf::Event::KeyPressed && sf::Keyboard::BackSpace==event.key.code)
                {
                    std::string tex=nameEntered.getString();
                    if(sf::Keyboard::BackSpace==event.key.code)
                    {
                        if(tex.size()>0)
                        {
                            tex.erase(tex.size()-1);
                            nameEntered.setString(tex);
                        }
                    }

                }
                else if (event.type ==sf::Event::KeyPressed && sf::Keyboard::Return==event.key.code && nameEntered.getString().getSize()>1)
                {
                    quit=true;
                }

                this->clear(sf::Color(238,238,238));
                this->draw(enterName);
                this->draw(nameEntered);
                this->display();
            }
        return nameEntered.getString();
    }
};

class Action
{
public:
    Action () {};
    virtual void operator()() const=0;
};

class ActionClose : public Action
{
public:
    ActionClose (bool *backMe):Action()
    {
        backMenu=backMe;
    };
    virtual void operator()() const
    {
        *backMenu=true;
    };
private:
    bool *backMenu;
};

class ActionSave : public Action
{
public:
    ActionSave (Chessboard **ech):Action()
    {
        e=ech;
    };
    virtual void operator()() const
    {
        InputDialog inp;
        std::string nameGame=inp.showDialog();
        if(nameGame.size()>0)
            (*e)->savePartie(nameGame);
    };
private:
    Chessboard **e;
};

class ActionUndo : public Action
{
    public:

    ActionUndo(Chessboard **ech):Action()
    {
        e=ech;
    };
    virtual void operator()() const
    {
        (*e)->undo();
    };
private:
    Chessboard **e;
//    ChessboardView *ev;
};

class Button
{

private:
    sf::Sprite spriteButton;
    sf::Texture textureButton;
public:
    Button(string srcButton,int x,int y)
    {
        textureButton.loadFromFile(srcButton);
        spriteButton=sf::Sprite(textureButton);
        spriteButton.setPosition(x,y);
    }
    void drawButton(sf::RenderWindow &app)
    {
        app.draw(spriteButton);
    }
    bool containMouse(int x,int y)
    {
        return spriteButton.getGlobalBounds().contains(x,y);
    }
    Action *actionPerformed;
};

int main()
{
    sf::RenderWindow app(sf::VideoMode(840, 480), "SFML window");

    texture.loadFromFile("ressources/fischer.png");

    sf::Sprite sprite(texture);

    font.loadFromFile("ressources/dreamwalker.ttf");

    bool quitGame=false;
    bool backMenu=false;

    Chessboard *e;
    ChessboardView ev=ChessboardView(e);

    Button bBackGame("ressources/quit.png",550,10);
    bBackGame.actionPerformed = new ActionClose(&backMenu);

    Button bSave("ressources/save.png",500,10);
    bSave.actionPerformed = new ActionSave(&e);

    Button bUndo("ressources/retour.png",500,300);
    bUndo.actionPerformed = new ActionUndo(&e);

    vector<Button> listButton;

    listButton.push_back(bBackGame);
    listButton.push_back(bSave);
    listButton.push_back(bUndo);

    while (!quitGame)
    {
        e=new Chessboard();

        switch (ev.menu(app,sprite,font))
        {
            case 0:break;

            case 1:
            {
                Partie partieCharge = ev.chargerPartie(app,sprite,font);
                if(partieCharge.name=="Annuler" && partieCharge.blows=="Annuler")
                    backMenu=true;
                else
                {
                    e->loadPartie(partieCharge);
                }

                break;
            }

            case 2:
                quitGame=true;
            break;

        }

        if(!quitGame && !backMenu)
        {
            ev.setModel(e);
            app.clear(sf::Color(238,238,238));
            ev.graphicDisplay(app);

            for(unsigned int i=0; i<listButton.size(); i++)
            {
                listButton[i].drawButton(app);
            }

            app.display();
            while (app.isOpen() && !backMenu)
            {
                sf::Event event;
                while (app.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        quitGame=true;
                        backMenu=true;
                    }


                    if(event.type==sf::Event::MouseButtonPressed)
                    {
                        backMenu=e->click(event.mouseButton.x, event.mouseButton.y);

                        if(backMenu)
                        {
                            OkDialog okdia("Echec et mat!");
                            okdia.showDialog();
                        }

                        app.clear(sf::Color(238,238,238));
                        for(unsigned int i=0; i<listButton.size(); i++)
                        {
                            listButton[i].drawButton(app);

                            if(listButton[i].containMouse(event.mouseButton.x, event.mouseButton.y))
                            {
                                (*listButton[i].actionPerformed)();
                            }
                        }


                        ev.graphicDisplay(app);
                        app.display();
                    }
                }
            }
                delete e;
            }
        backMenu=false;
    }
    return EXIT_SUCCESS;
}
