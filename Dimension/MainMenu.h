//
//  MainMenu.h
//  Dimension
//
//  Created by 17xiangyangt on 1/19/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__MainMenu__
#define __Dimension__MainMenu__

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "ResourcePath.hpp"

class MainMenu
{
public:
    enum MenuResult {Nothing, Exit, Play};
    
    struct MenuItem
    {
        sf::IntRect menuRect;
        MenuResult action;
    };
    
    MenuResult Show (sf::RenderWindow& window);
    
private:
    MenuResult getMenuResponse (sf::RenderWindow& window);
    MenuResult handleClick (int x, int y);
    std::list <MenuItem> _menuItems;
    
    sf::Sprite menuSprite, playSprite, exitSprite;
};

#endif /* defined(__Dimension__MainMenu__) */
