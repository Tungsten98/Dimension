//  Obstacle.cpp
//  Dimension
//
//  Created by 17xiangyangt on 2/1/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture* texture, float x, float y)
{
    m_Texture = texture;
    m_Sprite.setTexture(*m_Texture, true);
    m_Sprite.setOrigin(m_Texture->getSize().x/2, m_Texture->getSize().y/2);
    m_Sprite.setPosition(x, y);
}

Obstacle::~Obstacle(){}

void Obstacle::Draw(sf::RenderWindow& window)
{
    window.draw(m_Sprite);
}

sf::Sprite Obstacle::getSprite()
{
    return m_Sprite;
}