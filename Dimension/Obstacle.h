//
//  Obstacle.h
//  Dimension
//
//  Created by 17xiangyangt on 2/1/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__Obstacle__
#define __Dimension__Obstacle__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "VisibleGameObject.h"

namespace sf
{
    class Texture;
    class Sprite;
}

class Obstacle: public VisibleGameObject
{
private:
    sf::Texture* m_Texture;
    sf::Sprite m_Sprite;
    
public:
    Obstacle(sf::Texture* texture, float x, float y);
    ~Obstacle();
    
    void Draw(sf::RenderWindow& window);
    sf::Sprite getSprite();
};

#endif /* defined(__Dimension__Obstacle__) */
