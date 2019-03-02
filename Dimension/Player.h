//
//  Player.h
//  Dimension
//
//  Created by 17xiangyangt on 1/2/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__Player__
#define __Dimension__Player__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "image_manager.h"
#include "ResourcePath.hpp"
#include "Monster.h"
#include "Collision.h"
#include <string>
#include "playerMelee.h"
#include "playerRanged.h"
#include <vector>
#include "ClockManager.h"
#include "MonsterSpawner.h"
#include "Obstacle.h"

namespace sf
{
    class Texture;
    class Sprite;
    class View;
    class Clock;
    class Font;
    class Text;
    class Sound;
    class SoundBuffer;
}

class Monster;
class playerMelee;
class playerRanged;
class ClockManager;
class MonsterSpawner;
class Obstacle;

class Player : public sf::Sprite
{
private:
    int m_Health;
    int MAX_HEALTH;
    int m_Mana;
    int MAX_MANA;
    int manaRegenRate;
    int m_Damage;
    int m_Experience;
    int m_Score;
    int m_ExpCap;
    const int m_LvlCap = 50;
    int m_Level;
    int killCount;
    
    float m_xCoord;
    float m_yCoord;
    
    bool m_bDead;
    
    image_manager img_mgr;
    ClockManager clk_mgr;
    
    sf::Texture meleeTexture;
    sf::Texture rangedTexture;
    sf::Texture currentTexture;
    sf::Texture statTexture;
    sf::Texture barTexture;
    sf::Texture pauseTexture;
    sf::Texture quitTexture;
    
    sf::Sprite m_Sprite;
    sf::Sprite m_StatBar;
    sf::Sprite healthBar;
    sf::Sprite manaBar;
    sf::Sprite pauseSprite;
    sf::Sprite quitSprite;
    sf::View m_View;
    sf::Font m_Font;
    sf::Text m_hText;
    sf::Text m_mText;
    sf::Text m_lvlText;
    sf::Text m_expText;
    sf::Text m_waveText;
    sf::Text m_scoreText;
    
    std::string m_direction;
    sf::Clock colorClock;
    sf::IntRect repreRect;
    sf::IntRect pauseRect;
    
    sf::SoundBuffer msBuffer;
    sf::SoundBuffer hesBuffer;
    sf::SoundBuffer husBuffer;
    sf::SoundBuffer lvlsBuffer;
    
    sf::Sound meleeSound;
    sf::Sound healSound;
    sf::Sound hurtSound;
    sf::Sound levelSound;

public:
    Player();
    
    //overwritten methods
    void setTexture (const sf::Texture *texture);
    void setPosition (float x, float y);
    const sf::Vector2f& getPosition() const;
    
    void meleeAttack(sf::RenderWindow &window);
    void rangedAttack(sf::RenderWindow &window);
    void clearAttack();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void Draw(sf::RenderWindow &window);
    void attacked(Monster& monster);
    void updateMana();
    int getHealth();
    int getMaxHealth();
    int getMana();
    int getMaxMana();
    int getExp();
    int getMaxExp();
    int getLevel();
    int getMaxLevel();
    int getScore();
    void healHealth();
    void incrementKill();
    void setScore (int score);
    bool isDead();

    sf::Sprite getSprite();
    sf::Sprite getStatBar();
    sf::View getView();
    sf::Text getText();
    sf::Sprite getPause();
    std::string& getDirection();
    std::vector<playerMelee> getMAttackVec();
    std::vector<playerRanged> getRAttackVec();
    
    void gainExperience (int& exp);
    void writeWave(MonsterSpawner& monsterSpawner);
    void waveCountDown(ClockManager& ClockManager);
    
private:
    Player (const Player&); //private copy constructor
    Player operator = (const Player&);
    bool isMelee;
    bool isRanged;
    std::vector<playerMelee> mAttack;
    std::vector<playerRanged> rAttack;

};

#endif /* defined(__Dimension__Player__) */
