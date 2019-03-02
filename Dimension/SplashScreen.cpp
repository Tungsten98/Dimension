//
//  SplashScreen.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/19/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "splash.png"))
    {
        return;
    }
    
    sf::Sprite sprite(texture);
    
    renderWindow.draw(sprite);
    renderWindow.display();
    
    sf::Event event;
    while (true)
    {
        while (renderWindow.waitEvent(event))
        {
            if (event.type == sf::Event::EventType::KeyPressed
                || event.type == sf::Event::EventType::MouseButtonPressed
                || event.type == sf::Event::EventType::Closed)
            {
                return;
            }
        }
    }
}