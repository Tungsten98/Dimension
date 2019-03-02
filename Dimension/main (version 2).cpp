#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ResourcePath.hpp"
#include "Player.h"
#include "image_manager.h"

int main()
{
    sf::RenderWindow window (sf::VideoMode (1024, 768), "Dimension");
    
    image_manager img_mgr;
    
    //load a texture to place into background
    
    sf::Sprite spBackground; //create a sprite shape to fill with texture
    spBackground.setTexture(img_mgr.getTexture(resourcePath() + "mountainbackground.png"), true);
   
    Player playerStats;
    sf::Sprite thePlayer;
    thePlayer.setTexture(img_mgr.getTexture(resourcePath() + "Player_man.png"));
    thePlayer.setOrigin(78/2, 203/2);
    thePlayer.setPosition(1024/2, 768*1.5);
    
    sf::View view1(sf::FloatRect(0, 0, 1024, 768));
    view1.setCenter(thePlayer.getPosition().x, thePlayer.getPosition().y);
    
    //run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        //check all events triggered within the window since the last iteration of loop
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                }
                break;
                    
                case sf::Event::KeyPressed: //check for keys pressed
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    {
                        playerStats.setSpriteMode(1);
                        if (thePlayer.getPosition().y <= 136)
                        {
                            thePlayer.move (0,0);
                        }
                        else
                        {
                            thePlayer.move(0, -16);
                            if (thePlayer.getPosition().y <= view1.getCenter().y)//move the camera
                            {
                                if (view1.getCenter().y > (768/2))
                                {
                                    view1.move(0, -16);
                                }
                                else
                                {
                                    view1.move(0, 0);
                                }
                            }
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    {
                        playerStats.setSpriteMode(0);
                        if (thePlayer.getPosition().y >= 1536 - 136)
                        {
                            thePlayer.move (0,0);
                        }
                        else
                        {
                            thePlayer.move(0, 16);
                            if (thePlayer.getPosition().y >= view1.getCenter().y)
                            {
                                if (view1.getCenter().y < (768*1.5))
                                {
                                    view1.move(0, 16);
                                }
                                else
                                {
                                    view1.move(0, 0);
                                }
                            }
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        if (thePlayer.getPosition().x <= 48)
                        {
                            thePlayer.move (0,0);
                        }
                        else
                        {
                            thePlayer.move(-16, 0);
                            if (thePlayer.getPosition().x <= view1.getCenter().x)
                            {
                                if (view1.getCenter().x > (1024/2))
                                {
                                    view1.move(-16, 0);
                                }
                                else
                                {
                                    view1.move(0, 0);
                                }
                            }
                        }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    {
                        if (thePlayer.getPosition().x >= 2048 - 48)
                        {
                            thePlayer.move (0,0);
                        }
                        else
                        {
                            thePlayer.move(16, 0);
                            if (thePlayer.getPosition().x >= view1.getCenter().x)
                            {
                                if (view1.getCenter().x < (1024*1.5))
                                {
                                    view1.move(16, 0);
                                }
                                else
                                {
                                    view1.move(0, 0);
                                }
                            }
                        }
                    }
                }
                    break;
                    
                default:
                    break;
            }
            
        }
        
        switch (playerStats.getSpriteMode()) //change the sprite according to m_SpriteMode in Player.cpp
        {
            case 0:
                thePlayer.setTexture(img_mgr.getTexture(resourcePath() + "Player_man.png"), true);
                break;
                
            case 1:
                thePlayer.setTexture(img_mgr.getTexture(resourcePath() + "Player_man_3.png"), true);
                break;
                
            default:
                break;
        }
        
        window.clear(); //clear the screen per refresh
        window.draw(spBackground); //draw the sprite
        window.draw(thePlayer);
        window.setView(view1);
        window.display(); //refresh the screen
    }
    
    return EXIT_SUCCESS;
}