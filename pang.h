/**
 * @file   pang.h
 * @brief  Contains prototypes for pang game.
 * @author James Lasso/Logan Rostron/Josh
 * @date   2020-04-23
 */

#ifndef PANG_H
#define PANG_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <sstream>
#include <iostream>

#include "Window.h"
#include "menu.h"

// Global Constants
const int WINDOWX = 640;
const int WINDOWY = 480;
static float ballspeed = 2;


/**
 * Paddle Class.
 */
class Paddle : public sf::RectangleShape
{
public:
    Paddle();
    Paddle(sf::Color pColor);
    Paddle(std::string side, sf::Color pColor = sf::Color::White);
    void setYPosition(float here);
    void reset();
    
private:
    
    
};

/**
 * Ball Class.
 */
class Ball : public sf::CircleShape
{
public:
    Ball();
    //sf::CircleShape getBall();
    sf::Vector2f getBallSpeed();
    void setBallSpeed(sf::Vector2f speed);
    void setBallSpeed(float xSpeed, float ySpeed);
    void setBallSpeed(float multiplier);
    void reset();
    bool isBounce();
    void setBounce(bool afterBounced);
    

private:
    //sf::CircleShape ball;
    float radius = 10; // 10
    sf::Vector2f ballSpeed = sf::Vector2f(ballspeed, ballspeed);
    bool bounced = false;

};



/**
 * Player Class.
 */
class Player
{
public:
    Player(std::string side = "left");
    Player(sf::Color pColor, std::string side = "left");
    ~Player(){}
    virtual void incrementScore();
    void setScore(int change);
    int getScore();
    sf::Text& getPlayerScore();
    char getConnectionType() const;
    void setConnectionType(char connect);
    static void pauseOI();
    static bool isPaused();
    virtual void reset();
    Paddle pPaddle;
protected:
    int score;
    static bool pause;
    sf::Text playerScore;
    sf::Font scoreFont;
    char connectionType = 'n';
};



class ComputerPlayer : public Player
{
public:
    ComputerPlayer(std::string side = "right");
    ComputerPlayer(sf::Color pColor, std::string side = "right");
    ~ComputerPlayer(){}
    virtual void incrementScore();
    virtual void reset();
    virtual sf::Text& getPlayerScore();
private:
    sf::Text computerScore;
};



#endif