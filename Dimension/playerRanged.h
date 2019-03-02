
//
//  playerRanged.h
//  Dimension
//
//  Created by 17xiangyangt on 1/31/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__playerRanged__
#define __Dimension__playerRanged__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Monster.h"
#include "Collision.h"
#include <string>

namespace sf
{
    class Texture;
    class Sprite;
}

class Player;
class Monster;

class playerRanged: public sf::Sprite
{
public:
    playerRanged(float x, float y, const sf::Texture* texture, std::string& direction, int& damage);
    ~playerRanged();
    void loadResources(float x, float y, const sf::Texture* texture, std::string& direction);
    void unloadResources();
    
    int getDamage();
    sf::Sprite getSprite();
    void setX(float x);
    void setY(float y);
    float getX();
    float getY();
    void Draw(sf::RenderWindow &window);
    void move();
    std::string getDirection();
    
private:
    float x, y;
    const sf::Texture* rangedTexture;
    std::string direction;
    sf::Sprite rangedSprite;
    int m_Damage;
    
};

#endif /* defined(__Dimension__playerRanged__) */
