/**
 * @file   pong.h
 * @brief  Contains prototypes for pong game.
 * @author James Lasso/Logan Rostron/Josh
 * @date   2020-04-23
 */
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include "pang.h"

// Single Player, Host, Join, Exit
class Menu
{
public:
    Menu();
    int getCurrentOption(); // gets the current option
    sf::RectangleShape& getOption0();
    sf::RectangleShape& getOption1();
    sf::RectangleShape& getOption2();
    sf::RectangleShape& getOption3();
    sf::RectangleShape& getOption4();
    sf::Text& getOption0Text();
    sf::Text& getOption1Text();
    sf::Text& getOption2Text();
    sf::Text& getOption3Text();
    sf::Text& getOption4Text();
    void optionUp(); // currentOption--; if currentOption == 0 then go to 3
    void optionDown(); // currentOption++; if currentOption == 3 then go to 0
private:
    int currentOption = 0; // 0 = single; 1 = host; 2 = join; 3 = exit
    sf::RectangleShape option0;
    sf::RectangleShape option1;
    sf::RectangleShape option2;
    sf::RectangleShape option3;
    sf::RectangleShape option4;
    void highlightOption(int option);
    void unHighlightOption(int option);
    sf::Color color = sf::Color(63, 167, 233, 255);
    sf::Font font;
    sf::Text option0Text;
    sf::Text option1Text;
    sf::Text option2Text;
    sf::Text option3Text;
    sf::Text option4Text;
};

class PauseMenu
{
public:
    PauseMenu();
    int getCurrentOption();
    sf::RectangleShape& getOption0();
    sf::RectangleShape& getOption1();
    sf::Text& getOption0Text();
    sf::Text& getOption1Text();
    void optionUp();
    void optionDown();
private:
    int currentOption = 0;
    sf::RectangleShape option0; // Resume game
    sf::RectangleShape option1; // Exit to main menu
    void highlightOption(int option);
    void unHighlightOption(int option);
    sf::Color color = sf::Color(63, 167, 233, 255);
    sf::Font font;
    sf::Text option0Text;
    sf::Text option1Text;
};

class Instruction : public sf::Text
{
public:
    Instruction();
private:
    sf::Font font;
};

#endif