/**
 * @file   pang.cpp
 * @brief  contains function definitions for pang game.
 * @author James Lasso/Logan Rostron/Josh
 * @date   2020-04-23
 */

#include "pang.h"

bool Player::pause = false;

/**
 * Paddle Class Contructor
 */
Paddle::Paddle()
{
    setFillColor(sf::Color::White);
    setPosition(sf::Vector2f(static_cast<float>(WINDOWX/20), static_cast<float>(WINDOWY/2)));
    setSize(sf::Vector2f(static_cast<float>(WINDOWX/25), static_cast<float>(WINDOWY/5)));
    setOrigin(getSize().x / 2, getSize().y / 2);
}

/*
*Paddle class Constructor*
    uses the input to determine
    the color of the paddle being
    created
*/
Paddle::Paddle(sf::Color pColor)
{
    setFillColor(pColor);
    setPosition(sf::Vector2f(static_cast<float>(WINDOWX/20), static_cast<float>(WINDOWY/2)));
    setSize(sf::Vector2f(static_cast<float>(WINDOWX/25), static_cast<float>(WINDOWY/5)));
    setOrigin(getSize().x / 2, getSize().y / 2);
}

/*
*Paddle class Constructor*
    uses the inputs to determine
    the color of the paddle being
    created and the side the paddle
    gets "spawned" on
*/
Paddle::Paddle(std::string side, sf::Color pColor)
{
    setFillColor(pColor);
    if (side == "left")
    {
        setPosition(sf::Vector2f(static_cast<float>(WINDOWX/20), static_cast<float>(WINDOWY/2)));
    }
    else if (side == "right")
    {
        setPosition(sf::Vector2f(static_cast<float>(WINDOWX - WINDOWX/20), static_cast<float>(WINDOWY/2)));
    }
    setSize(sf::Vector2f(static_cast<float>(WINDOWX/25), static_cast<float>(WINDOWY/5)));
    setOrigin(getSize().x / 2, getSize().y / 2);
}

// set the paddle's Y position
void Paddle::setYPosition(float here)
{
    setPosition(getPosition().x, here);
}

//  reset paddle position
void Paddle::reset()
{
    setYPosition(WINDOWY / 2);
}

/*
*Basic Ball class constructor*
    -sets ball color to white
    -resets ball position to mid-screen
    -sets the radius to a given size
    -sets the origin of the ball
*/
Ball::Ball()
{
    setFillColor(sf::Color::White);
    setPosition(sf::Vector2f(WINDOWX/2, WINDOWY/2));
    setRadius(radius);
    setOrigin(sf::Vector2f(getRadius(), getRadius()));
}

// sf::CircleShape Ball::getBall()
// {
//     return ball;
// }

//  returns the speed of the ball
sf::Vector2f Ball::getBallSpeed()
{
    return ballSpeed;
}

//  sets the ball's speed with the given parameter
void Ball::setBallSpeed(sf::Vector2f speed)
{
    ballSpeed = speed;
}

//  set's the ball's speed with the given X and Y parameters
void Ball::setBallSpeed(float xSpeed, float ySpeed)
{
    ballSpeed.x = xSpeed;
    ballSpeed.y = ySpeed;
}

//  set ball speed with a multiplier number (Increase ball speed X times faster)
void Ball::setBallSpeed(float multiplier)
{
    ballSpeed.x *= multiplier;
    ballSpeed.y *= multiplier;
}

//  reset ball position and speed
void Ball::reset()
{
    setPosition(sf::Vector2f(WINDOWX/2, WINDOWY/2));
    setBallSpeed(ballspeed,ballspeed);
}

// check if the ball bounced (return true/false)
bool Ball::isBounce()
{
    return bounced;
}

// set the bounced bool to the given input to see if ball has bounced
void Ball::setBounce(bool afterBounced)
{
    bounced = afterBounced;
}

/***************************************************************
 *  Default Player class constructor
 *  By default the side that the player is on is the left side
 *  Sets the player's score to zero
 *  Creates the player's paddle on the passed side
 ***************************************************************/
Player::Player(std::string side)
{
    if (side == "left")
    {
        score = -1;
    }
    else
        score = 0;
    std::ostringstream scr;
    scr << score;
    scoreFont.loadFromFile("arial.ttf");
    playerScore.setString(scr.str());
    playerScore.setFont(scoreFont);
    if (side == "left")
    {
        playerScore.setPosition(sf::Vector2f(WINDOWX/2 - WINDOWX/10, WINDOWY/20));
    }
    else
    {
        playerScore.setPosition(sf::Vector2f(WINDOWX/2 + WINDOWX/20, WINDOWY/20));
    }
    pPaddle = Paddle(side);
}

/*
 *Player class constructor with 2 inputs*
    Constructs the player class with the 
    given specifications --
    player color and side of the board(left/right)
*/
Player::Player(sf::Color pColor, std::string side)
{
    if (side == "left")
    {
        score = -1;
    }
    else
        score = 0;
    std::ostringstream scr;
    scr << score;
    scoreFont.loadFromFile("arial.ttf");
    playerScore.setString(scr.str());
    playerScore.setFont(scoreFont);
    if (side == "left")
    {
        playerScore.setPosition(sf::Vector2f(WINDOWX/2 - WINDOWX/10, WINDOWY/20));
    }
    else
    {
        playerScore.setPosition(sf::Vector2f(WINDOWX/2 + WINDOWX/20, WINDOWY/20));
    }
    pPaddle = Paddle(side, pColor);
}

// Increment the player's score by one point and update the corresponding values
void Player::incrementScore()
{
    score += 1;
    std::ostringstream scr;
    scr << score;
    playerScore.setString(scr.str());
}

void Player::setScore(int change)
{
    score = change;
    std::ostringstream scr;
    scr << score;
    playerScore.setString(scr.str());
}


// Return's player's score (Numerical)
int Player::getScore()
{
    return score;
}

// Return's player's score  (used for: Text Display)
sf::Text& Player::getPlayerScore()
{
    return playerScore;
}

//  gets the player's connection type
char Player::getConnectionType() const
{
    return connectionType;
}

// set the player's connection type
void Player::setConnectionType(char connect)
{
    connectionType = connect;
}

void Player::pauseOI()
{
    pause = !pause;
}

bool Player::isPaused()
{
    return pause;
}

//  reset's the player's score and paddle position
void Player::reset()
{
    score = 0;
    pPaddle.reset();
    std::ostringstream scr;
    scr << score;
    playerScore.setString(scr.str());
}



/***************************************************************
 *  Default ComputerPlayer class constructor
 *  By default the side that the computer is on is the right side
 *  Sets the computer's score to zero
 *  Creates the computer's paddle on the passed side
 ***************************************************************/
ComputerPlayer::ComputerPlayer(std::string side)
{
    score = 0;
    std::ostringstream scr;
    scr << score;
    scoreFont.loadFromFile("arial.ttf");
    computerScore.setString(scr.str());
    computerScore.setFont(scoreFont);
    if (side == "left")
    {
        computerScore.setPosition(sf::Vector2f(WINDOWX/2 - WINDOWX/10, WINDOWY/20));
    }
    else
    {
        computerScore.setPosition(sf::Vector2f(WINDOWX/2 + WINDOWX/20, WINDOWY/20));
    }
    pPaddle = Paddle(side);
}

/*
 *Player class constructor with 2 inputs*
    Constructs the player class with the 
    given specifications --
    player color and side of the board(left/right)
*/
ComputerPlayer::ComputerPlayer(sf::Color pColor, std::string side)
{
    score = 0;
    std::ostringstream scr;
    scr << score;
    scoreFont.loadFromFile("arial.ttf");
    computerScore.setString(scr.str());
    computerScore.setFont(scoreFont);
    if (side == "left")
    {
        computerScore.setPosition(sf::Vector2f(WINDOWX/2 - WINDOWX/10, WINDOWY/20));
    }
    else
    {
        computerScore.setPosition(sf::Vector2f(WINDOWX/2 + WINDOWX/20, WINDOWY/20));
    }
    pPaddle = Paddle(side, pColor);
}

// Increment the computer's score by one point and update the corresponding values
void ComputerPlayer::incrementScore()
{
    score += 1;
    std::ostringstream scr;
    scr << score;
    computerScore.setString(scr.str());
}

//  reset's the computer's score and paddle position
void ComputerPlayer::reset()
{
    score = 0;
    pPaddle.reset();
    std::ostringstream scr;
    scr << score;
    computerScore.setString(scr.str());
}
sf::Text& ComputerPlayer::getPlayerScore()
{
    return computerScore;
}