//#include <SFML/Graphics.hpp>
//
//#ifndef Dialogs_h
//#define Dialogs_h
//
//class OkDialog : public sf::RenderWindow
//{
//
//private:
//    std::string message;
//    sf::Font font;
//
//public:
//
//    OkDialog(std::string mess,sf::Font fon):sf::RenderWindow()
//    {
//        message=mess;
//        font=fon;
//    };
//
//    void showDialog()
//    {
//        sf::Event event;
//
//        sf::Text messageText(message,font,30);
//        sf::Text pressAkey("Appuyez sur une touche",font,30);
//
//        messageText.setPosition(200-messageText.getGlobalBounds().width/2,100);
//        pressAkey.setPosition(50,350);
//        messageText.setColor(sf::Color::Black);
//        pressAkey.setColor(sf::Color::Black);
//
//        bool quit=false;
//
//        this->create(sf::VideoMode(400, 400), "Echec et mat");
//        this->clear(sf::Color(238,238,238));
//        this->draw(messageText);
//        this->draw(pressAkey);
//        this->display();
//
//        while (this->isOpen() && !quit)
//            while (this->pollEvent(event))
//            {
//                if (event.type == sf::Event::Closed)
//                {
//                    quit=true;
//                }
//
//                if (event.type ==sf::Event::KeyPressed && sf::Keyboard::Return==event.key.code)
//                {
//                    quit=true;
//                }
//            }
//    }
//};
//
//class InputDialog : public sf::RenderWindow
//{
//
//private:
//    sf::Font font;
//
//public:
//
//    InputDialog(sf::Font fon):sf::RenderWindow() {
//    font=fon;
//    };
//
//    std::string showDialog()
//    {
//        sf::Event event;
//
//
//        sf::Text enterName("Enter a name",font,40);
//        sf::Text nameEntered("",font,40);
//
//        enterName.setPosition(200-enterName.getGlobalBounds().width/2,100);
//        nameEntered.setPosition(200-enterName.getGlobalBounds().width/2,150);
//        enterName.setColor(sf::Color::Black);
//        nameEntered.setColor(sf::Color::Black);
//
//        bool quit=false;
//
//        this->create(sf::VideoMode(400, 400), "Choississez un nom");
//        this->clear(sf::Color(238,238,238));
//        this->draw(enterName);
//        this->draw(nameEntered);
//        this->display();
//
//        while (this->isOpen() && !quit)
//            while (this->pollEvent(event))
//            {
//                if (event.type == sf::Event::Closed)
//                {
//                    quit=true;
//                }
//                else if (event.type ==sf::Event::TextEntered)
//                {
//
//
//                    if(event.text.unicode>65 && event.text.unicode<122)
//                    {
//                        std::string tex=nameEntered.getString();
//
//                        if(tex.size()<12)
//                        {
//                            tex+=(char)event.text.unicode;
//                            nameEntered.setString(tex);
//                        }
//                    }
//
//
//                }
//                else if (event.type ==sf::Event::KeyPressed && sf::Keyboard::BackSpace==event.key.code)
//                {
//                    std::string tex=nameEntered.getString();
//                    if(sf::Keyboard::BackSpace==event.key.code)
//                    {
//                        if(tex.size()>0)
//                        {
//                            tex.erase(tex.size()-1);
//                            nameEntered.setString(tex);
//                        }
//                    }
//
//                }
//                else if (event.type ==sf::Event::KeyPressed && sf::Keyboard::Return==event.key.code && nameEntered.getString().getSize()>1)
//                {
//                    quit=true;
//                }
//
//                this->clear(sf::Color(238,238,238));
//                this->draw(enterName);
//                this->draw(nameEntered);
//                this->display();
//            }
//        return nameEntered.getString();
//    }
//};
//#endif
