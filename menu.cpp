/**
 * @file   pong.h
 * @brief  Contains prototypes for pong game.
 * @author James Lasso/Logan Rostron/Josh
 * @date   2020-04-23
 */
#include "menu.h"

Menu::Menu()
{
    font.loadFromFile("arial.ttf");
    option0Text.setString("Single Player");
    option0Text.setFont(font);
    option0Text.setCharacterSize(28);
    option1Text.setString("Host");
    option1Text.setFont(font);
    option1Text.setCharacterSize(28);
    option2Text.setString("Join");
    option2Text.setFont(font);
    option2Text.setCharacterSize(28);
    option3Text.setString("Exit Game");
    option3Text.setFont(font);
    option3Text.setCharacterSize(28);
    option4Text.setString("Instructions");
    option4Text.setFont(font);
    option4Text.setCharacterSize(28);
    option0.setSize(sf::Vector2f(WINDOWX/3, WINDOWY/10));
    option1.setSize(sf::Vector2f(WINDOWX/3, WINDOWY/10));
    option2.setSize(sf::Vector2f(WINDOWX/3, WINDOWY/10));
    option3.setSize(sf::Vector2f(WINDOWX/3, WINDOWY/10));
    option4.setSize(sf::Vector2f(WINDOWX/3, WINDOWY/10));
    option0.setPosition(sf::Vector2f(WINDOWX/3, (WINDOWY/7 * 2)));
    option1.setPosition(sf::Vector2f(WINDOWX/3, (WINDOWY/7 * 3)));
    option2.setPosition(sf::Vector2f(WINDOWX/3, (WINDOWY/7 * 4)));
    option3.setPosition(sf::Vector2f(WINDOWX/3, (WINDOWY/7 * 5)));
    option4.setPosition(sf::Vector2f(WINDOWX/3, (WINDOWY/7 * 6)));
    option0.setFillColor(color);
    option1.setFillColor(color);
    option2.setFillColor(color);
    option3.setFillColor(color);
    option4.setFillColor(color);
    option0.setOutlineColor(sf::Color::White);
    option1.setOutlineColor(sf::Color::White);
    option2.setOutlineColor(sf::Color::White);
    option3.setOutlineColor(sf::Color::White);
    option4.setOutlineColor(sf::Color::White);
    option0Text.setPosition(option0.getPosition());
    option1Text.setPosition(option1.getPosition());
    option2Text.setPosition(option2.getPosition());
    option3Text.setPosition(option3.getPosition());
    option4Text.setPosition(option4.getPosition());
    
    highlightOption(0);
}

int Menu::getCurrentOption()
{   
    return currentOption;
}

sf::RectangleShape& Menu::getOption0()
{
    return option0;
}

sf::RectangleShape& Menu::getOption1()
{
    return option1;
}

sf::RectangleShape& Menu::getOption2()
{
    return option2;
}

sf::RectangleShape& Menu::getOption3()
{
    return option3;
}

sf::RectangleShape& Menu::getOption4()
{
    return option4;
}

sf::Text& Menu::getOption0Text()
{
    return option0Text;
}

sf::Text& Menu::getOption1Text()
{
    return option1Text;
}

sf::Text& Menu::getOption2Text()
{
    return option2Text;
}

sf::Text& Menu::getOption3Text()
{
    return option3Text;
}

sf::Text& Menu::getOption4Text()
{
    return option4Text;
}

void Menu::optionUp()
{
    if (currentOption == 0)
    {
        unHighlightOption(currentOption);
        currentOption = 4;
        highlightOption(currentOption);
    }
    else
    {
        unHighlightOption(currentOption);
        currentOption--;
        highlightOption(currentOption);
    }
    
}

void Menu::optionDown()
{
    if (currentOption == 4)
    {
        unHighlightOption(currentOption);
        currentOption = 0;
        highlightOption(currentOption);
    }
    else
    {
        unHighlightOption(currentOption);
        currentOption++;
        highlightOption(currentOption);
    }
}

void Menu::highlightOption(int option)
{
    if (option == 0)
    {
        option0.setOutlineThickness(-3);
        option0.setOutlineColor(sf::Color::White);
    }
    if (option == 1)
    {
        option1.setOutlineThickness(-3);
        option1.setOutlineColor(sf::Color::White);
    }
    if (option == 2)
    {
        option2.setOutlineThickness(-3);
        option2.setOutlineColor(sf::Color::White);
    }
    if (option == 3)
    {
        option3.setOutlineThickness(-3);
        option3.setOutlineColor(sf::Color::White);
    }
    if (option == 4)
    {
        option4.setOutlineThickness(-3);
        option4.setOutlineColor(sf::Color::White);
    }
}

void Menu::unHighlightOption(int option)
{
    if (option == 0)
    {
        option0.setOutlineThickness(-3);
        option0.setOutlineColor(sf::Color::Transparent);
    }
    if (option == 1)
    {
        option1.setOutlineThickness(-3);
        option1.setOutlineColor(sf::Color::Transparent);
    }
    if (option == 2)
    {
        option2.setOutlineThickness(-3);
        option2.setOutlineColor(sf::Color::Transparent);
    }
    if (option == 3)
    {
        option3.setOutlineThickness(-3);
        option3.setOutlineColor(sf::Color::Transparent);
    }
    if (option == 4)
    {
        option4.setOutlineThickness(-3);
        option4.setOutlineColor(sf::Color::Transparent);
    }
}

PauseMenu::PauseMenu()
{
    font.loadFromFile("arial.ttf");
    option0Text.setString("Resume Game");
    option0Text.setFont(font);
    option0Text.setCharacterSize(32);
    option1Text.setString("Exit to Menu");
    option1Text.setFont(font);
    option1Text.setCharacterSize(32);
    option0.setSize(sf::Vector2f(WINDOWX/3, WINDOWY/8));
    option1.setSize(sf::Vector2f(WINDOWX/3, WINDOWY/8));
    option0.setPosition(sf::Vector2f(WINDOWX/3, (WINDOWY/7 * 3)));
    option1.setPosition(sf::Vector2f(WINDOWX/3, (WINDOWY/7 * 4)));
    option0.setFillColor(color);
    option1.setFillColor(color);
    option0.setOutlineColor(sf::Color::White);
    option1.setOutlineColor(sf::Color::White);
    option0Text.setPosition(option0.getPosition());
    option1Text.setPosition(option1.getPosition());

    highlightOption(0);
}

int PauseMenu::getCurrentOption()
{
    return currentOption;
}

sf::RectangleShape& PauseMenu::getOption0()
{
    return option0;
}

sf::RectangleShape& PauseMenu::getOption1()
{
    return option1;
}

sf::Text& PauseMenu::getOption0Text()
{
    return option0Text;
}

sf::Text& PauseMenu::getOption1Text()
{
    return option1Text;
}

void PauseMenu::optionUp()
{
    if (currentOption == 0)
    {
        unHighlightOption(currentOption);
        currentOption = 1;
        highlightOption(currentOption);
    }
    else
    {
        unHighlightOption(currentOption);
        currentOption--;
        highlightOption(currentOption);
    }
}

void PauseMenu::optionDown()
{
    if (currentOption == 1)
    {
        unHighlightOption(currentOption);
        currentOption = 0;
        highlightOption(currentOption);
    }
    else
    {
        unHighlightOption(currentOption);
        currentOption++;
        highlightOption(currentOption);
    }
}

void PauseMenu::highlightOption(int option)
{
    if (option == 0)
    {
        option0.setOutlineThickness(-3);
        option0.setOutlineColor(sf::Color::White);
    }
    if (option == 1)
    {
        option1.setOutlineThickness(-3);
        option1.setOutlineColor(sf::Color::White);
    }
}

void PauseMenu::unHighlightOption(int option)
{
    if (option == 0)
    {
        option0.setOutlineThickness(-3);
        option0.setOutlineColor(sf::Color::Transparent);
    }
    if (option == 1)
    {
        option1.setOutlineThickness(-3);
        option1.setOutlineColor(sf::Color::Transparent);
    }
}

Instruction::Instruction()
{
    font.loadFromFile("arial.ttf");
    setFont(font);
    setCharacterSize(30);
    setString("-The Paddle moves with mouse\n-Escape key to pause\n-Up/Down arrow keys to navigate menus\n-Score points by bouncing the ball\n\toff the opposite wall\n-First to 10 points wins\n-HAVE FUN!!!");
    setPosition(sf::Vector2f(WINDOWX/20, WINDOWY/10));
}