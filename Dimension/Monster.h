//
//  Monster.h
//  Dimension
//
//  Created by 17xiangyangt on 1/7/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__Monster__
#define __Dimension__Monster__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "playerMelee.h"
#include "playerRanged.h"
#include "ClockManager.h"
#include "Obstacle.h"
#include <vector>
#include <string>
#include <time.h>

namespace sf
{
    class Sprite;
    class Texture;
    class Clock;
    class SoundBuffer;
    class Sound;
}

class Player;
class playerMelee;
class playerRanged;
class ClockManager;
class Obstacle;

class Monster: public sf::Sprite
{
private:
    int m_Health;
    int MAX_HEALTH;
    int m_Damage;
    int giveXP;
    bool m_bDead;
    
public:
    Monster(const sf::Texture* texture, float x, float y, Player& player, int dValue, int stHealth, int rewardXP);
    
    void move(std::vector <Obstacle> obstacles);
    sf::Sprite getSprite();
    
    void setTexture (const sf::Texture *texture);
    void setOrigin (const sf::Texture *texture);
    void setPosition (float x, float y);
    const sf::Vector2f& getPosition() const;
    void mAttacked(std::vector <playerMelee> targetVector, std::string& direction);
    void rAttacked(std::vector <playerRanged> targetVector, std::string& direction);
    void Draw(sf::RenderWindow &window);
    int getDamage();
    int getExperience();
    bool isDead();
    
private:
    ~Monster();
    sf::Sprite m_Sprite;
    sf::SoundBuffer painBuffer;
    sf::Sound pain;
    const sf::Texture* m_Texture;
    Player* m_Player;
    sf::Clock colorClock;
    ClockManager clk_mgr;
    float m_xCoord;
    float m_yCoord;
    float m_prevyCoord;
    float m_respawnX;
    float m_respawnY;
    sf::IntRect repreRect;
    
    void updateCoords();
    
};

#endif /* defined(__Dimension__Monster__) */

//
