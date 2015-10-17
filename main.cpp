#include <SFML/Graphics.hpp>
#include "Echiquier.h"
#include "util.h"

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
                // Close window : exit
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
    ActionSave (Echiquier **ech):Action()
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
    Echiquier **e;
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

    std::function<void(void)> *action;
};
int Menu(sf::RenderWindow &app,sf::Sprite sprite,sf::Font font)
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
            // Close window : exit
//            if (event.type == sf::Event::Closed)
//                app.close();

            if (event.type==sf::Event::KeyPressed)
            {

//                        std::cout << "ta mere" << std::endl;
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

Partie ChargerPartie(sf::RenderWindow &app,sf::Sprite sprite,sf::Font font)
{
    bool choose=false;

    unsigned int choice=0;

    vector<Partie> listParties=utility::listeParties();

    listParties.push_back(Partie("Annuler",0,"",""));

    sf::Event event;

    while(!choose)
    {
        while (app.pollEvent(event))
        {

            if (event.type==sf::Event::KeyPressed)
            {
                //                        std::cout << "ta mere" << std::endl;
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
                else if(sf::Keyboard::BackSlash)
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

int main()
{
    Piece::initImage();

    sf::RenderWindow app(sf::VideoMode(840, 480), "SFML window");

    texture.loadFromFile("fischer.png");

    sf::Sprite sprite(texture);

    font.loadFromFile("dreamwalker.ttf");

    bool quitGame=false;
    bool backMenu=false;

    Echiquier *e;

    Button bBackGame("retour.png",550,10);
    bBackGame.actionPerformed=new ActionClose(&backMenu);

    Button bSave("save.png",500,10);
    bSave.actionPerformed=new ActionSave(&e);

    vector<Button> listButton;

    listButton.push_back(bBackGame);
    listButton.push_back(bSave);

    while (!quitGame)
    {
        switch (Menu(app,sprite,font))
        {
            case 0:
            {
                e=new Echiquier();
            }
            break;

            case 1:
            {
                Partie partieCharge=ChargerPartie(app,sprite,font);
                if(partieCharge.name=="Annuler")
                    backMenu=true;
                else
                    e=new Echiquier(partieCharge);
            };break;

            case 2:
            {
                quitGame=true;
            };break;
        }
        if(!quitGame && !backMenu)
        {
            app.clear(sf::Color(238,238,238));
            e->afficheGraphique(app);

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
                        e->afficheGraphique(app);

                        for(unsigned int i=0; i<listButton.size(); i++)
                        {
                            listButton[i].drawButton(app);

                            if(listButton[i].containMouse(event.mouseButton.x, event.mouseButton.y))
                            {
                                (*listButton[i].actionPerformed)();
                            }
                        }
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
