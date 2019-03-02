//
//  Game.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/19/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Game.h"

void Game::Start(void)
{
    if (_gameState != Uninitialized)
    {
        return;
    }
    
    _mainWindow.create(sf::VideoMode(1024, 768), "Dimension");
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png"))
    {
        EXIT_FAILURE;
    }
    _mainWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    _gameState = Game::ShowingSplash;
    
    while (!IsExiting())
    {
        GameLoop();
    }
    
    _mainWindow.close();
}

bool Game::IsExiting()
{
    if (_gameState == Game::Exiting)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    splashScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    
    switch (result)
    {
        case MainMenu::Exit:
            _gameState = Game::Exiting;
            break;
            
        case MainMenu::Play:
            _gameState = Game::Playing;
            break;
            
        default:
            break;
    }
}

void Game::PlayGame()
{
    image_manager img_mgr;
    
    ClockManager clockManager;
    
    bool gameOver= false;
    bool gameOverMessage = false;
    bool sendGameOver = false;
    bool isPaused = false;
    bool quitMessage = false;
    bool respawnLoop = false;
    bool toMainMenu = false;
    
    sf::View defaultView;
    defaultView.setSize(1024, 768);
    defaultView.setCenter(512, 384);
    
    //load a texture to place into background
    
    sf::Texture pauseTexture = img_mgr.getTexture(resourcePath() + "pause.png");
    sf::Sprite pauseSprite(pauseTexture);
    pauseSprite.setOrigin(pauseTexture.getSize().x/2, pauseTexture.getSize().y/2);
    
    sf::Texture boolQuitTexture = img_mgr.getTexture(resourcePath() + "quitmessage.png");
    sf::Sprite boolQuitSprite(boolQuitTexture);
    boolQuitSprite.setOrigin(boolQuitTexture.getSize().x/2, boolQuitTexture.getSize().y/2);
    boolQuitSprite.setColor(sf::Color(224, 224, 224));
    
    sf::Texture yesQuit = img_mgr.getTexture(resourcePath() + "yes.png");
    sf::Texture noQuit = img_mgr.getTexture(resourcePath() + "no.png");
    sf::Sprite yesQuitSpr(yesQuit), noQuitSpr(noQuit);
    yesQuitSpr.setOrigin(yesQuit.getSize().x/2, yesQuit.getSize().y/2);
    noQuitSpr.setOrigin(noQuit.getSize().x/2, noQuit.getSize().y/2);
    
    Player thePlayer; //Player is a class derived from sf::Sprite
    
    MonsterSpawner monsterSpawner(thePlayer);
    std::vector<Monster> monsterArray;
    thePlayer.writeWave(monsterSpawner);
    
    //run the program as long as the window is open
    while (!IsExiting() && !toMainMenu && !gameOver)
    {
        sf::Event event;
        //check all events triggered within the window since the last iteration of loop
        
        while (_mainWindow.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    _gameState = Game::Exiting;
                }
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        if (quitMessage)
                        {
                            if (sf::Mouse::getPosition().x < _mainWindow.getView().getSize().x - 175
                                && sf::Mouse::getPosition().x > _mainWindow.getView().getSize().x - 346
                                && sf::Mouse::getPosition().y < _mainWindow.getView().getSize().y - 363
                                && sf::Mouse::getPosition().y > _mainWindow.getView().getSize().y - 421)
                            {
                                quitMessage = !quitMessage;
                            }
                            
                            else if (sf::Mouse::getPosition().x < _mainWindow.getView().getSize().x - 420
                             && sf::Mouse::getPosition().x > _mainWindow.getView().getSize().x - 594
                             && sf::Mouse::getPosition().y < _mainWindow.getView().getSize().y - 363
                             && sf::Mouse::getPosition().y > _mainWindow.getView().getSize().y - 421)
                            {
                                toMainMenu = true;
                            }
                        }
                        else
                        {
                            if (sf::Mouse::getPosition().x < _mainWindow.getView().getSize().x + 112
                                && sf::Mouse::getPosition().x > _mainWindow.getView().getSize().x + 80
                                && sf::Mouse::getPosition().y < _mainWindow.getView().getSize().y - 116
                                && sf::Mouse::getPosition().y > _mainWindow.getView().getSize().y - 144)
                            {
                                isPaused = !isPaused;
                            }
                            
                            else if (sf::Mouse::getPosition().x < _mainWindow.getView().getSize().x + 112
                                     && sf::Mouse::getPosition().x > _mainWindow.getView().getSize().x + 80
                                     && sf::Mouse::getPosition().y < _mainWindow.getView().getSize().y - 71
                                     && sf::Mouse::getPosition().y > _mainWindow.getView().getSize().y - 104)
                            {
                                quitMessage = !quitMessage;
                            }
                        }
                    }
                }
                    break;
                case sf::Event::KeyPressed: //check for keys pressed
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                    {
                        if (!quitMessage && !gameOverMessage)
                            isPaused = !isPaused;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        if (!isPaused && !quitMessage && !gameOverMessage)
                        {
                            //check for collisions with all obstacle objects
                            int obCount = 0;
                            for (int i = 0; i < monsterSpawner.getObstacleArray().size(); ++i)
                            {
                                if (!(Collision::BoundingBoxTest(thePlayer.getSprite(), monsterSpawner.getObstacleArray()[i].getSprite())
                                      && thePlayer.getSprite().getPosition().y > monsterSpawner.getObstacleArray()[i].getSprite().getPosition().y))
                                {
                                    obCount++;
                                }
                            }
                            if (obCount == monsterSpawner.getObstacleArray().size())
                            {
                               thePlayer.moveUp();
                            }
                            else
                            {
                                thePlayer.move(0, 0);
                            }
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    {
                        if (!isPaused && !quitMessage && !gameOverMessage)
                        {
                            int obCount = 0;
                            for (int i = 0; i < monsterSpawner.getObstacleArray().size(); ++i)
                            {
                                if (!(Collision::BoundingBoxTest(thePlayer.getSprite(), monsterSpawner.getObstacleArray()[i].getSprite())
                                      && thePlayer.getSprite().getPosition().y < monsterSpawner.getObstacleArray()[i].getSprite().getPosition().y))
                                {
                                    obCount++;
                                }
                            }
                            if (obCount == monsterSpawner.getObstacleArray().size())
                            {
                                thePlayer.moveDown();
                            }
                            else
                            {
                                thePlayer.move(0, 0);
                            }
                        }

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        if (!isPaused && !quitMessage && !gameOverMessage)
                        {
                            int obCount = 0;
                            for (int i = 0; i < monsterSpawner.getObstacleArray().size(); ++i)
                            {
                                if (!(Collision::BoundingBoxTest(thePlayer.getSprite(), monsterSpawner.getObstacleArray()[i].getSprite())
                                      && thePlayer.getSprite().getPosition().x > monsterSpawner.getObstacleArray()[i].getSprite().getPosition().x))
                                {
                                    obCount++;
                                }
                            }
                            if (obCount == monsterSpawner.getObstacleArray().size())
                            {
                                thePlayer.moveLeft();
                            }
                            else
                            {
                                thePlayer.move(0, 0);
                            }
                        }

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    {
                        if (!isPaused && !quitMessage && !gameOverMessage)
                        {
                            int obCount = 0;
                            for (int i = 0; i < monsterSpawner.getObstacleArray().size(); ++i)
                            {
                                if (!(Collision::BoundingBoxTest(thePlayer.getSprite(), monsterSpawner.getObstacleArray()[i].getSprite())
                                      && thePlayer.getSprite().getPosition().x < monsterSpawner.getObstacleArray()[i].getSprite().getPosition().x))
                                {
                                    obCount++;
                                }
                            }
                            if (obCount == monsterSpawner.getObstacleArray().size())
                            {
                                thePlayer.moveRight();
                            }
                            else
                            {
                                thePlayer.move(0, 0);
                            }
                        }

                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        if (!isPaused && !quitMessage && !gameOverMessage)
                        {
                            if (clockManager.mCoolDownTime() >= 0.5)
                            {
                                thePlayer.meleeAttack(_mainWindow);
                                clockManager.resetMeleeTime();
                                clockManager.resetMeleeCoolDown();
                            }
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    {
                        if (gameOverMessage)
                        {
                            sendGameOver = true;
                        }
                        else if (!isPaused && !quitMessage && !gameOverMessage)
                        {
                            if (clockManager.rCoolDownTime() >= 0.5)
                            {
                                thePlayer.rangedAttack(_mainWindow);
                                clockManager.resetRangedCoolDown();
                            }
                        }
                    }
                }
                    break;
                    
                case sf::Event::LostFocus:
                {
                    isPaused = true;
                }
                    break;
                    
                case sf::Event::GainedFocus:
                {
                    isPaused = !isPaused;
                }
                    break;
                default:
                    break;
            }
        }
        
        if (!isPaused && !quitMessage && !gameOverMessage)
        {
            for (int i = 0; i < monsterArray.size(); ++i)
            {
                monsterArray[i].move(monsterSpawner.getObstacleArray());
            }
            
            for (int i = 0; i < thePlayer.getRAttackVec().size(); ++i)
            {
                if (thePlayer.getRAttackVec()[i].getPosition().y < 0 || thePlayer.getRAttackVec()[i].getPosition().y > 1536)
                {
                    thePlayer.getRAttackVec().erase(thePlayer.getRAttackVec().begin() + i);
                }
            }
            
            if (clockManager.meleeTime() >= 0.2)
            {
                thePlayer.clearAttack();
            }
            
            for (int i = 0; i < monsterArray.size(); ++i) //check for attacked collisions
            {
                thePlayer.attacked(monsterArray[i]);
                monsterArray[i].mAttacked(thePlayer.getMAttackVec(), thePlayer.getDirection());
                monsterArray[i].rAttacked(thePlayer.getRAttackVec(), thePlayer.getDirection());
            }
            
            _mainWindow.clear(sf::Color(200, 255, 255)); //clear the screen per refresh
            _mainWindow.draw(monsterSpawner.getBackground()); //draw the sprite
            for (int i = 0; i < monsterSpawner.getObstacleArray().size(); ++i)
            {
                monsterSpawner.getObstacleArray()[i].Draw(_mainWindow);
            }
            
            for (int i = 0; i < monsterArray.size(); ++i)
            {
                monsterArray[i].Draw(_mainWindow);
                if (monsterArray[i].isDead())
                {
                    thePlayer.incrementKill();
                    monsterArray.erase(monsterArray.begin() + i);
                }
            }
            
            thePlayer.healHealth();
            
            if (monsterArray.empty() && !respawnLoop)
            {
                monsterSpawner.update();
                clockManager.resetRespawn();
                respawnLoop = true;
            }
            
            if (monsterArray.empty() && respawnLoop)
            {
                thePlayer.waveCountDown(clockManager);
                if (clockManager.respawnTime() >= 5.0)
                {
                    thePlayer.writeWave(monsterSpawner);
                    monsterSpawner.copyToVec(monsterArray);
                    respawnLoop = false;
                }
            }
            
            thePlayer.updateMana();
            thePlayer.Draw(_mainWindow);
            _mainWindow.setView(thePlayer.getView());
            
            if (thePlayer.isDead())
            {
                clockManager.resetGameOver();
                while (clockManager.gameOverTime() < 5.0f){}
                gameOverMessage = true;
            }

        }
        else if (isPaused)
        {
            pauseSprite.setPosition(thePlayer.getView().getCenter().x, thePlayer.getView().getCenter().y - 96);
            _mainWindow.draw(pauseSprite); //the draw function draws the sprite's current position for every update: the sprite stays in its position because there is no update on the sprite's position
        }
        else if (quitMessage)
        {
            boolQuitSprite.setPosition(thePlayer.getView().getCenter().x, thePlayer.getView().getCenter().y - 96);
            yesQuitSpr.setPosition(thePlayer.getView().getCenter().x - 125, thePlayer.getView().getCenter().y - 12);
            noQuitSpr.setPosition(thePlayer.getView().getCenter().x + 122, thePlayer.getView().getCenter().y - 12);
            _mainWindow.draw(boolQuitSprite);
            _mainWindow.draw(yesQuitSpr);
            _mainWindow.draw(noQuitSpr);
        }
        else if (gameOverMessage)
        {
            sf::Font font;
            if (!font.loadFromFile(resourcePath() + "sansation.ttf"))
            {
                EXIT_FAILURE;
            }
            
            sf::Text goText, messageText, finalScore;
            goText.setString("Game Over");
            goText.setFont(font);
            goText.setCharacterSize(144);
            goText.setOrigin(goText.getGlobalBounds().width/2, goText.getGlobalBounds().height/2);
            goText.setPosition(thePlayer.getView().getCenter().x, thePlayer.getView().getCenter().y - 250);
            goText.setColor(sf::Color(92, 0, 0));
            
            messageText.setString("Press enter to continue");
            messageText.setFont(font);
            messageText.setCharacterSize(80);
            messageText.setOrigin(messageText.getGlobalBounds().width/2, messageText.getGlobalBounds().height/2);
            messageText.setPosition(thePlayer.getView().getCenter().x, thePlayer.getView().getCenter().y);
            messageText.setColor(sf::Color(92, 0, 0));
            
            finalScore.setString("Final score: " + std::to_string(thePlayer.getScore()));
            finalScore.setFont(font);
            finalScore.setCharacterSize(40);
            finalScore.setOrigin(finalScore.getGlobalBounds().width/2, finalScore.getGlobalBounds().height/2);
            finalScore.setPosition(thePlayer.getView().getCenter().x, thePlayer.getView().getCenter().y - 100);
            finalScore.setColor(sf::Color(92, 0, 0));
            
            if (sendGameOver)
            {
                gameOver = true;
            }
            
            _mainWindow.draw(goText);
            _mainWindow.draw(messageText);
            _mainWindow.draw(finalScore);
        }
        
        _mainWindow.display(); //refresh the screen
        
    }
    if (gameOver)
    {
        _mainWindow.setView(defaultView);
        _gameState = Game::GameOver;
    }
    else if (toMainMenu)
    {
        _mainWindow.setView(defaultView);
        _gameState = Game::ShowingMenu;
    }
    else
    {
        _gameState = Game::Exiting;
    }
}

void Game::ShowGameOver()
{
    GameOverScreen gameOverScreen;
    gameOverScreen.Show(_mainWindow);
    _gameState = Game::ShowingMenu;
}

void Game::GameLoop()
{
    sf::Event currentEvent;
    while (_mainWindow.pollEvent(currentEvent))
    {
        switch (_gameState)
        {
            case Game::ShowingSplash:
            {
                ShowSplashScreen();
                break;
            }
                
            case Game::ShowingMenu:
            {
                ShowMenu();
                break;
            }
                
            case Game::Playing:
            {
                PlayGame();
                break;
            }
                
            case Game::GameOver:
            {
                ShowGameOver();
                break;
            }
        
            default:
                break;
        }
    }
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;