//
//  Monster.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/7/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Monster.h"

Monster::Monster(const sf::Texture* texture, float x, float y, Player& player, int dValue, int stHealth, int rewardXP)
{
    m_Texture = texture;
    m_Sprite.sf::Sprite::setTexture(*m_Texture, true);
    
    /*if (painBuffer.loadFromFile(resourcePath() + "MummyZombie.wav"))
    {
        pain.setBuffer(painBuffer);
    }*/
    
    sf::IntRect tempRect (0, 0, m_Texture->getSize().x/2, m_Texture->getSize().y);
    repreRect = tempRect;
    m_Sprite.setTextureRect(repreRect);
    m_Sprite.sf::Sprite::setOrigin(repreRect.width/2, repreRect.height/2);
    m_Sprite.sf::Sprite::setPosition(x, y);
    m_respawnX = x;
    m_respawnY = y;
    
    m_Player = &player;
    
    m_Health = stHealth;
    MAX_HEALTH = stHealth;
    m_Damage = dValue;
    giveXP = rewardXP;
}

int Monster::getDamage()
{
    return m_Damage;
}

int Monster::getExperience()
{
    return giveXP;
}

void Monster::move(std::vector<Obstacle> obstacles)
{
    // Initialize a timer
    sf::Clock clock;
        
    // Get elapsed time at the beginning of a frame
    // Multiply this by target framerate to get a value of around one
    float delta = clock.restart().asSeconds() * 60;
        
    // Move all objects based on elapsed time
    sf::Vector2f direction = (m_Player->getPosition() - m_Sprite.getPosition());
    int speed = 32;
    
    if (Collision::BoundingBoxTest(m_Sprite, m_Player->getSprite()))
    {
        m_Sprite.move (0, 0);
    }
    else
    {
        int obCount = 0;
        for (int i = 0; i < obstacles.size(); ++i)
        {
            if (!(Collision::BoundingBoxTest(m_Sprite, obstacles[i].getSprite())))
            {
                obCount++;
            }
            else
            {
                if (m_Sprite.getPosition().y > obstacles[i].getSprite().getPosition().y)
                {
                    m_Sprite.move(0, 2);
                }
                else if (m_Sprite.getPosition().y < obstacles[i].getSprite().getPosition().y)
                {
                    m_Sprite.move(0, -2);
                }
                break;
            }
        }
        if (obCount == obstacles.size())
        {
            m_Sprite.move(delta * speed * direction);
        }
    }
    
    updateCoords();
    if (m_yCoord > m_prevyCoord)
    {
        sf::IntRect tempRect (0, 0, m_Texture->getSize().x/2, m_Texture->getSize().y);
        repreRect = tempRect;
        m_Sprite.setTextureRect(repreRect);
        m_Sprite.sf::Sprite::setOrigin(repreRect.width/2, repreRect.height/2);
    }
    else if (m_yCoord < m_prevyCoord)
    {
        sf::IntRect tempRect (m_Texture->getSize().x/2, 0, m_Texture->getSize().x/2, m_Texture->getSize().y);
        repreRect = tempRect;
        m_Sprite.setTextureRect(repreRect);
        m_Sprite.sf::Sprite::setOrigin(repreRect.width/2, repreRect.height/2);
    }
}

void Monster::updateCoords()
{
    m_xCoord = m_Sprite.sf::Sprite::getPosition().x;
    
    float temp = m_yCoord;
    m_yCoord = m_Sprite.sf::Sprite::getPosition().y;
    m_prevyCoord = temp;
}

void Monster::mAttacked(std::vector <playerMelee> targetVector, std::string& direction)
{
    if (clk_mgr.invulTime() >= 0.5)
    {
        for (int i = 0; i < targetVector.size(); ++i)
        {
            if (Collision::BoundingBoxTest(targetVector[i].getSprite(), m_Sprite))
            {
                if (direction == "up" && m_Sprite.sf::Sprite::getPosition().y >= 136)
                {
                    m_Sprite.move(0, -64);
                }
                else if (direction == "down" && m_Sprite.sf::Sprite::getPosition().y <= 1400)
                {
                    m_Sprite.move(0, 64);
                }
                
                m_Health -= targetVector[i].getDamage();
                m_Sprite.setColor(sf::Color(255, 255, 255, 128));
                colorClock.restart();
                clk_mgr.resetInvul();
            }
        }
        pain.play();
    }
    
    if (colorClock.getElapsedTime().asSeconds() >= 0.5)
    {
        m_Sprite.setColor(sf::Color(255, 255, 255, 255));
    }
    
    if (m_Health <= 0)
    {
        m_Player->gainExperience(giveXP);
        m_Player->setScore(giveXP);
        m_bDead = true;
        this->~Monster();
    }
}

void Monster::rAttacked(std::vector <playerRanged> targetVector, std::string& direction)
{
    if (clk_mgr.invulTime() >= 0.5)
    {
        for (int i = 0; i < targetVector.size(); ++i)
        {
            if (Collision::BoundingBoxTest(targetVector[i].getSprite(), m_Sprite))
            {
                if (direction == "up" && m_Sprite.sf::Sprite::getPosition().y >= 136)
                {
                    m_Sprite.move(0, -64);
                }
                else if (direction == "down" && m_Sprite.sf::Sprite::getPosition().y <= 1400)
                {
                    m_Sprite.move(0, 64);
                }
                
                m_Health -= targetVector[i].getDamage();
                m_Sprite.setColor(sf::Color(255, 255, 255, 128));
                colorClock.restart();
                clk_mgr.resetInvul();
            }
        }
        pain.play();
    }
    if (colorClock.getElapsedTime().asSeconds() >= 0.5)
    {
        m_Sprite.setColor(sf::Color(255, 255, 255, 255));
    }
    
    if (m_Health <= 0)
    {
        m_Player->gainExperience(giveXP);
        m_Player->setScore(giveXP);
        m_bDead = true;
        
        /*srand(time(NULL));
         int randXcoord, randYcoord;
         
         randXcoord = rand() % 2048 + 1;
         randYcoord = rand() % 1536 + 1;
         
         m_xCoord = randXcoord;
         m_yCoord = randYcoord;
         
         m_Sprite.sf::Sprite::setPosition(m_xCoord, m_yCoord);
         m_Health = MAX_HEALTH;*/ //we will need this later for sandbox mode
    }
}

bool Monster::isDead()
{
    return m_bDead;
}

void Monster::Draw(sf::RenderWindow &window)
{
    window.draw(m_Sprite);
}

sf::Sprite Monster::getSprite()
{
    return m_Sprite;
}

void Monster::setTexture (const sf::Texture *texture)
{
    m_Sprite.sf::Sprite::setTexture(*texture, true);
}

void Monster::setOrigin (const sf::Texture *texture)
{
    m_Sprite.sf::Sprite::setOrigin(texture->getSize().x/2, texture->getSize().y/2);
}

void Monster::setPosition (float x, float y)
{
    m_Sprite.sf::Sprite::setPosition(x, y);
}

const sf::Vector2f& Monster::getPosition() const
{
    return m_Sprite.sf::Sprite::getPosition();
}