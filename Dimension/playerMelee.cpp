//
//  playerMelee.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/10/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "playerMelee.h"

playerMelee::playerMelee(float x, float y, const sf::Texture* texture, std::string& direction, int& damage)
{
    loadResources(x, y, texture, direction);
    m_Damage = damage;
}

playerMelee::~playerMelee(){};

void playerMelee::loadResources(float x, float y, const sf::Texture* texture, std::string& direction)
{
    this->x = x;
    this->y = y;
    
    meleeTexture = texture;
    meleeSprite.setTexture(*meleeTexture);
    
    if (direction == "down")
    {
        meleeSprite.setRotation(180.f);
    }
    meleeSprite.setOrigin(meleeTexture->getSize().x/2, meleeTexture->getSize().y/2);
    meleeSprite.setPosition(x, y);
}

int playerMelee::getDamage()
{
    return m_Damage;
}

void playerMelee::unloadResources(){}

sf::Sprite playerMelee::getSprite()
{
    return meleeSprite;
}

void playerMelee::setX(float x)
{
    this->x = x;
}

void playerMelee::setY(float y)
{
    this->y = y;
}

float playerMelee::getX()
{
    return x;
}

float playerMelee::getY()
{
    return y;
}

void playerMelee::Draw(sf::RenderWindow &window)
{
    window.draw(meleeSprite);
}