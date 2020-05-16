/**
 * @file   main.cpp
 * @brief  Contains game loop/logic
 * @author James Lasso/Logan Rostron/Josh Bohannan
 * @date   2020-04-23
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <SFML/Network.hpp> // Network

#include "pang.h"
#include "menu.h"
//C:\Users\walie\Desktop\SchoolThings\cs151\firstSFMLProject
//g++ -std=c++11 main.cpp pang.cpp menu.cpp -o main.exe -LC:/sfml/lib/ -IC:/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
//g++ -std=c++11 main.cpp pang.cpp menu.cpp -o main.exe -LC:/Users/walie/Desktop/SchoolThings/cs151/firstSFMLProject/sfml/lib -IC:/Users/walie/Desktop/SchoolThings/cs151/firstSFMLProject/sfml/include/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
int main()
{

    sf::Clock clock;
    float deltaTime;
    bool soloPlay = false;
    int currentScreen = 0; // 0 = mainmenu; 1 = gamescreen; 2 = pausemenu

    // Network Code work Area START
    sf::IpAddress ip = sf::IpAddress::getPublicAddress();
    
    sf::TcpSocket socket;
    socket.setBlocking(true);
    std::string conDisplayName;
    char connectionType;

    // Menu creations
    Menu mainMenu;
    PauseMenu pauseMenu;
    Instruction instruction;

    // Bounce sound
    sf::SoundBuffer boopSrc;
    boopSrc.loadFromFile("audio/boop.wav");
    sf::Sound boop(boopSrc);
    sf::SoundBuffer beepSrc;
    beepSrc.loadFromFile("audio/beep.wav");
    sf::Sound beep(beepSrc);
    beep.setVolume(50);
    boop.setVolume(60);
    beep.setPitch(.575);
    boop.setPitch(.7);
    
    // Music
    sf::Music music;
    if (!music.openFromFile("audio/Impulse.ogg"))
        return EXIT_FAILURE;

    music.setVolume(4);
    
    // Creating the window
    sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "Pang Time");

    // Spawn Player
    Player player1(sf::Color::Cyan, "left");
    sf::Vector2f prevP1Position;
    // Player player2(sf::Color::Magenta, "right");;
    Player playerPh(sf::Color::Magenta, "right");
    ComputerPlayer computerPh(sf::Color::Magenta, "right");
    Player* player2 = &computerPh;
    sf::Vector2f prevP2Position;

    // Spawn Ball
    Ball ball;

    // Start music
    music.play();

    // Game Logic
    bool update = false; // This is to determine if window should be updated or not based on current focus
    
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close(); // close game on window close

            if (currentScreen == 0)
            {
                // Menu screen stuff
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
                {
                    mainMenu.optionUp();
                }

                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
                {
                    mainMenu.optionDown();
                }

                else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
                {
                    int selection = mainMenu.getCurrentOption();

                    if (selection == 0)
                    {
                        // Play solo
                        soloPlay = true;
                        currentScreen = 1;
                        ComputerPlayer cp(sf::Color::Magenta);
                        Player* player2 = &cp;
                        player2 = &computerPh;
                    }
                    else if (selection == 1)
                    {
                        soloPlay = false;
                        // Wait for someone to enter your ip -- Server
                        sf::TcpListener listener;
                        listener.listen(54000);
                        window.setTitle("Pang - " + conDisplayName + " " + ip.toString());
                        listener.accept(socket);
                        conDisplayName = "Server";
                        connectionType = 's';
                        // window.setTitle("Pang - " + conDisplayName + " " + ip.toString());
                        currentScreen = 1;
                        player2 = &playerPh;
                    }
                    else if (selection == 2)
                    {
                        soloPlay = false;
                        // Go to the enter ip stuff -- Client
                        std::string strIp;
                        std::cout << "Enter an ip to connect to: ";
                        std::cin >> strIp;
                        socket.connect(strIp, 54000);
                        // socket.connect(ip, 2000);
                        conDisplayName = "Client";
                        connectionType = 'c';
                        window.setTitle("Pang - " + conDisplayName);
                        currentScreen = 1;
                        player2 = &playerPh;
                    }
                    else if (selection == 3)
                    {
                        // Exit game
                        window.close();
                    }
                    else
                    {
                        // Instructions
                        currentScreen = 3;
                    }      
                }
            }
            else if (currentScreen == 1)
            {
                // Game screen stuff
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                {
                    currentScreen = 2;
                    Player::pauseOI();
                }

                if (Player::isPaused())
                {
                    currentScreen = 2;
                }

                if (soloPlay == false)
                {    
                    if (connectionType == 's')
                    {
                        player1.pPaddle.setYPosition(sf::Mouse::getPosition(window).y);
                    }
                    else if (connectionType == 'c')
                    {
                        player2->pPaddle.setYPosition(sf::Mouse::getPosition(window).y);
                    }
                }
                else
                {
                    player1.pPaddle.setYPosition(sf::Mouse::getPosition(window).y);
                    
                } 
            }
            else if (currentScreen == 2)
            {
                //Pause screen stuff
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                {
                    currentScreen = 1;
                    Player::pauseOI();
                }

                if (!Player::isPaused())
                {
                    currentScreen = 1;
                }

                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
                {
                    pauseMenu.optionUp();
                }

                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
                {
                    pauseMenu.optionDown();
                }
                
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
                {
                    int selection = pauseMenu.getCurrentOption();

                    if (selection == 0)
                    {
                        currentScreen = 1;
                        Player::pauseOI();
                    }
                    else 
                    {
                        ball.reset();
                        player1.reset();
                        player2->reset();
                        currentScreen = 0;
                    }
                }
            }
            else if (currentScreen == 3)
            {
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                {
                    currentScreen = 0;
                }
            }
        }
        // Computer movement in solo play
        if (soloPlay == true)
        {
            player2->pPaddle.setYPosition(ball.getPosition().y);
        }
        // Setting previous position******************************************************************************************************
        sf::Vector2f prevBallPosition = ball.getPosition(); //<-- move after this
        
        //ball.setPosition(ball.getPosition().x + ball.getBallSpeed().x, ball.getPosition().y + ball.getBallSpeed().y);
        if (currentScreen == 1 && !Player::isPaused())
        {
            float deltaTime = clock.restart().asSeconds();
            const int pixelsToMovePerSec = 100;
            const float frameMovement = pixelsToMovePerSec * deltaTime;
            ball.move(ball.getBallSpeed().x * frameMovement, ball.getBallSpeed().y * frameMovement);
            
            // Ball Bouncing Start **************************************************************************************************************
            // right wall
            if (ball.getPosition().x >= WINDOWX - (ball.getRadius()))
            {
                // increment player 1 score AND RESET BAWLS TO MADDLE // wat no no. 
                ball.setBallSpeed(ball.getBallSpeed().x * -1, ball.getBallSpeed().y);
                ball.reset();
                player1.incrementScore();
                if (player1.getScore() == 10)
                {
                    exit(0);
                }
            }
            // bottom wall
            if (ball.getPosition().y >= WINDOWY - ball.getRadius())
            {
                ball.setBallSpeed(ball.getBallSpeed().x, ball.getBallSpeed().y * -1);
            }
            // left wall
            if (ball.getPosition().x <= WINDOWX - WINDOWX + ball.getRadius())
            {
                // increment P2 points and reset ball position to middle // check score -- declare winner  // reset game options
                ball.setBallSpeed(ball.getBallSpeed().x * -1, ball.getBallSpeed().y);
                ball.reset();
                player2->incrementScore();
                if (player2->getScore() == 10)
                {
                    exit(0);
                }
            }
            // top wall
            if (ball.getPosition().y <= WINDOWY - WINDOWY + ball.getRadius())
            {
                ball.setBallSpeed(ball.getBallSpeed().x, ball.getBallSpeed().y * -1);
            }
            
            // Player 1 paddle face bounce
            if (!ball.isBounce() && ((ball.getPosition().y <= (player1.pPaddle.getPosition().y + player1.pPaddle.getSize().y / 2)) 
                && (ball.getPosition().y >= (player1.pPaddle.getPosition().y - player1.pPaddle.getSize().y / 2)))
                && ((ball.getPosition().x - ball.getRadius()) <= (player1.pPaddle.getPosition().x + player1.pPaddle.getSize().x / 2)))
            {
                ball.setBallSpeed(ball.getBallSpeed().x * -1, ball.getBallSpeed().y);
                ball.setBounce(true);
                ball.setBallSpeed(1.05);
                boop.play();
            }
            // Player 2 paddle face bounce
            if (!ball.isBounce() && ((ball.getPosition().y <= (player2->pPaddle.getPosition().y + player2->pPaddle.getSize().y / 2)) 
                && (ball.getPosition().y >= (player2->pPaddle.getPosition().y - player2->pPaddle.getSize().y / 2)))
                && ((ball.getPosition().x + ball.getRadius()) >= (player2->pPaddle.getPosition().x - player2->pPaddle.getSize().x / 2)))
            {
                ball.setBallSpeed(ball.getBallSpeed().x * -1, ball.getBallSpeed().y);
                ball.setBounce(true);
                ball.setBallSpeed(1.05);
                beep.play();
            }

            // Making sure the ball only bounces off a paddle once
            if (ball.getPosition().x > WINDOWX/10 && ball.getPosition().x < (WINDOWX - WINDOWX/10))
            {
                ball.setBounce(false);
            }
        }
        // Ball bouncing end *****************************************************************************************************************

        // Network Updating stuff
        // update ball position START
        // create packet
        
        sf::Packet ballPacket;
        sf::Packet player1Packet;
        sf::Packet player2Packet;
        sf::Vector2f ballPosition;
        sf::Vector2f p1Position;
        sf::Vector2f p2Position;
        sf::Packet scorePacket;
        int p1Score;
        int p2Score;

        //Server Sends Ball Packet
        ballPacket << ball.getPosition().x << ball.getPosition().y;
        socket.send(ballPacket);
        
        //Client Receives Ball Packet
        socket.receive(ballPacket);
        if(connectionType == 'c' && ballPacket >> ballPosition.x >> ballPosition.y)
        {
            ball.setPosition(ballPosition);  
        }

        //Server Sends Score Packet
        scorePacket << player1.getScore() << player2->getScore();
        socket.send(scorePacket);

        //client receive score packet
        socket.receive(scorePacket);
        if (connectionType == 'c' && scorePacket >> p1Score >> p2Score)
        {
            player1.setScore(p1Score);
            player2->setScore(p2Score);
        }

        // Send/Receive Player 1 Paddle Packet
        player1Packet << player1.pPaddle.getPosition().x << player1.pPaddle.getPosition().y;
        socket.send(player1Packet);
        socket.receive(player1Packet);

        // Update Based on connection type player 1
        if(connectionType == 'c' && player1Packet >> p1Position.x >> p1Position.y)
        {
            player1.pPaddle.setPosition(p1Position);
        }

        // Send/Receive Player 2 Paddle Packet
        player2Packet << player2->pPaddle.getPosition().x << player2->pPaddle.getPosition().y;
        socket.send(player2Packet);
        socket.receive(player2Packet);

        // Update based on connection type player 2
        if(connectionType == 's' && player2Packet >> p2Position.x >> p2Position.y)
        {
            player2->pPaddle.setYPosition(p2Position.y);
        }
                

        // Clear Window
        window.clear(sf::Color::Black);
        
        // Draw things
        if (currentScreen == 0)
        {
            // Main Menu
            window.draw(mainMenu.getOption0());
            window.draw(mainMenu.getOption1());
            window.draw(mainMenu.getOption2());
            window.draw(mainMenu.getOption3());
            window.draw(mainMenu.getOption4());
            window.draw(mainMenu.getOption0Text());
            window.draw(mainMenu.getOption1Text());
            window.draw(mainMenu.getOption2Text());
            window.draw(mainMenu.getOption3Text());
            window.draw(mainMenu.getOption4Text());
        }
        if (currentScreen == 1)
        {
            // Draw paddles
            window.draw(player1.pPaddle);
            window.draw(player2->pPaddle);

            // Draw Scores
            window.draw(player1.getPlayerScore());
            // window.draw(player2->getPlayerScore());
            if (soloPlay == true)
            {
                window.draw(computerPh.getPlayerScore());
            }
            else
            {
                window.draw(player2->getPlayerScore());
            }
            

            // Draw Ball
            window.draw(ball);
        }
        if (currentScreen == 2)
        {
            // Pause Menu
            window.draw(pauseMenu.getOption0());
            window.draw(pauseMenu.getOption1());
            window.draw(pauseMenu.getOption0Text());
            window.draw(pauseMenu.getOption1Text());
        }
        if (currentScreen == 3)
        {
            window.draw(instruction);
        }

        window.display();
    }
    return 0;
}
