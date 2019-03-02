//
//  playerRanged.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/31/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "playerRanged.h"

playerRanged::playerRanged(float x, float y, const sf::Texture* texture, std::string& direction, int& damage)
{
    this->direction = direction;
    loadResources(x, y, texture, this->direction);
    m_Damage = damage;
}

playerRanged::~playerRanged(){};

void playerRanged::loadResources(float x, float y, const sf::Texture* texture, std::string& direction)
{
    this->x = x;
    this->y = y;
    
    rangedTexture = texture;
    rangedSprite.setTexture(*rangedTexture);
    
    if (direction == "down")
    {
        rangedSprite.setRotation(180.f);
    }
    rangedSprite.setOrigin(rangedTexture->getSize().x/2, rangedTexture->getSize().y/2);
    rangedSprite.setPosition(x, y);
}

void playerRanged::move()
{
    if (direction == "up")
    {
        this->y -= 2;
        rangedSprite.setPosition(x, y);
    }
    else
    {
        this->y += 2;
        rangedSprite.setPosition(x, y);
    }
}

int playerRanged::getDamage()
{
    return m_Damage;
}

void playerRanged::unloadResources(){}

sf::Sprite playerRanged::getSprite()
{
    return rangedSprite;
}

void playerRanged::setX(float x)
{
    this->x = x;
}

void playerRanged::setY(float y)
{
    this->y = y;
}

float playerRanged::getX()
{
    return x;
}

float playerRanged::getY()
{
    return y;
}

std::string playerRanged::getDirection()
{
    return this->direction;
}

void playerRanged::Draw(sf::RenderWindow &window)
{
    window.draw(rangedSprite);
}