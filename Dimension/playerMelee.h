//
//  playerMelee.h
//  Dimension
//
//  Created by 17xiangyangt on 1/10/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__playerMelee__
#define __Dimension__playerMelee__

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

class playerMelee: public sf::Sprite
{
public:
    playerMelee(float x, float y, const sf::Texture* texture, std::string& direction, int& damage);
    ~playerMelee();
    void loadResources(float x, float y, const sf::Texture* texture, std::string& direction);
    void unloadResources();
    
    int getDamage();
    sf::Sprite getSprite();
    void setX(float x);
    void setY(float y);
    float getX();
    float getY();
    void Draw(sf::RenderWindow &window);
    
private:
    float x, y;
    const sf::Texture* meleeTexture;
    sf::Sprite meleeSprite;
    int m_Damage;
    
};

#endif /* defined(__Dimension__playerMelee__) */
