//
//  MainMenu.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/19/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    //load main menu image from file
    sf::Texture menuTexture;
    if (menuTexture.loadFromFile(resourcePath() + "mainmenu.png"))
    {
        menuSprite.setTexture(menuTexture);
    }
    
    sf::Texture exitTexture, playTexture, highScoreTexture;
    if (exitTexture.loadFromFile(resourcePath() + "exitbutton.png"))
    {
        exitSprite.setTexture(exitTexture);
    }
    if (playTexture.loadFromFile(resourcePath() + "playbutton.png"))
    {
        playSprite.setTexture(playTexture);
    }

    //setup clickable regions
    MenuItem playButton;
    playButton.menuRect.top = 400;
    playButton.menuRect.height = 175;
    playButton.menuRect.left = 125;
    playButton.menuRect.width = 350;
    playSprite.setTextureRect(sf::IntRect(0, 0, 350, 175));
    playSprite.setPosition(125, 400);
    playButton.action = Play;
    
    MenuItem exitButton;
    exitButton.menuRect.top = 400;
    exitButton.menuRect.height = 175;
    exitButton.menuRect.left = 575;
    exitButton.menuRect.width = 350;
    exitSprite.setTextureRect(sf::IntRect(0, 0, 350, 175));
    exitSprite.setPosition(575, 400);
    exitButton.action = Exit;
    
    _menuItems.push_back(playButton);
    _menuItems.push_back(exitButton);
    
    window.draw(menuSprite);
    window.draw(playSprite);
    window.draw(exitSprite);
    window.display();
    
    return getMenuResponse(window);
}

MainMenu::MenuResult MainMenu::handleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;
    
    for (it = _menuItems.begin(); it != _menuItems.end(); ++it)
    {
        sf::IntRect menuItemRect = (*it).menuRect;
        if ((menuItemRect.top + menuItemRect.height) > y && menuItemRect.top < y
            && (menuItemRect.left + menuItemRect.width) > x && menuItemRect.left < x)
        {
            return (*it).action;
        }
    }
    
    return Nothing;
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;
    
    while (true)
    {
        while(window.pollEvent(menuEvent))
        {
            if (menuEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
            if (menuEvent.type == sf::Event::MouseButtonPressed)
            {
                return handleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }
        }
    }
}