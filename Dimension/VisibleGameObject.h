//
//  VisibleGameObject.h
//  Dimension
//
//  Created by 17xiangyangt on 2/1/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__VisibleGameObject__
#define __Dimension__VisibleGameObject__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace sf
{
    class Texture;
    class Sprite;
}

class VisibleGameObject
{
private:
    sf::Texture* m_Texture;
    sf::Sprite m_Sprite;
    
public:
    VisibleGameObject();
    virtual ~VisibleGameObject();
    
    virtual void Draw(sf::RenderWindow& window);
    virtual sf::Sprite getSprite();
};

#endif /* defined(__Dimension__VisibleGameObject__) */
