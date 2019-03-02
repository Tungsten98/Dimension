//
//  Player.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/2/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Player.h"

Player::Player()
{
    sf::Texture playerTexture;
    if (playerTexture.loadFromFile(resourcePath() + "Playerssheet.png"))
    {
        currentTexture = playerTexture;
    }
    
    sf::Texture mlTexture;
    if (mlTexture.loadFromFile(resourcePath() + "playerstrike.png"))
    {
        meleeTexture = mlTexture;
    }
    
    sf::Texture statBarTexture;
    if (statBarTexture.loadFromFile(resourcePath() + "statinterface.png"))
    {
        statTexture = statBarTexture;
    }
    rangedTexture = img_mgr.getTexture(resourcePath() + "playerspelln.png");
    
    pauseTexture = img_mgr.getTexture(resourcePath() + "pausebutton.png");
    quitTexture = img_mgr.getTexture(resourcePath() + "quitbutton.png");
    
    pauseSprite.setTexture(pauseTexture);
    quitSprite.setTexture(quitTexture);

    m_Sprite.sf::Sprite::setTexture(currentTexture, true);
    
    sf::IntRect tempRect (0, 0, 80, 204);
    repreRect = tempRect;
    m_Sprite.sf::Sprite::setTextureRect(repreRect);
    m_Sprite.sf::Sprite::setOrigin(repreRect.width/2, repreRect.height/2);
    
    m_xCoord = 1024/2;
    m_yCoord = 768*1.5;
    m_Sprite.sf::Sprite::setPosition(m_xCoord, m_yCoord);
    m_View.sf::View::setSize(1024, 768);
    m_View.sf::View::setCenter(m_Sprite.getPosition().x, m_Sprite.getPosition().y);
    
    m_StatBar.sf::Sprite::setTexture(statTexture);
    m_StatBar.sf::Sprite::setPosition(m_View.getCenter().x - m_View.getCenter().x, m_View.getCenter().y + 256);
    
    pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
    quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
    
    sf::Texture bTexture;
    bTexture = img_mgr.getTexture(resourcePath() + "healthbar.png");
    barTexture = bTexture;
    healthBar.setTexture(barTexture);
    healthBar.sf::Sprite::setPosition(m_View.getCenter().x - 349, m_View.getCenter().y + 278);
    healthBar.setColor(sf::Color(255, 0, 0));
    manaBar.setTexture(barTexture);
    manaBar.sf::Sprite::setPosition(m_View.getCenter().x - 349, m_View.getCenter().y + 336);
    manaBar.setColor(sf::Color(0, 0, 255));
    
    sf::Font font;
    if (font.loadFromFile(resourcePath() + "sansation.ttf"))
    {
        m_Font = font;
    }
    
    if (msBuffer.loadFromFile(resourcePath() + "SwordSwing.wav"))
    {
        meleeSound.setBuffer(msBuffer);
    }
    if (hesBuffer.loadFromFile(resourcePath() + "heal.wav"))
    {
        healSound.setBuffer(hesBuffer);
    }
    if (husBuffer.loadFromFile(resourcePath() + "Pain.wav"))
    {
        hurtSound.setBuffer(husBuffer);
    }
    if (lvlsBuffer.loadFromFile(resourcePath() + "LevelUp.wav"))
    {
        levelSound.setBuffer(lvlsBuffer);
    }
    
    m_direction = "down";
    isMelee = false;
    isRanged = false;
    m_bDead = false;
    
    m_Damage = 10;
    m_Health = 100;
    MAX_HEALTH = 100;
    m_Mana = 50;
    MAX_MANA = 50;
    manaRegenRate = 5;
    
    m_Experience = 0;
    m_ExpCap = 100;
    m_Level = 1;
    
    m_Score = 0;
    
    m_hText.setFont(m_Font);
    std::string healthString = std::to_string(m_Health);
    std::string maxHealthString = std::to_string(MAX_HEALTH);
    sf::String hString = healthString + " / " + maxHealthString;
    m_hText.setString(hString);
    m_hText.setCharacterSize(20);
    m_hText.setColor(sf::Color::White);
    m_hText.setPosition(m_View.getCenter().x - 137, m_View.getCenter().y + 273);
    
    m_mText.setFont(m_Font);
    std::string manaString = std::to_string(m_Mana);
    std::string maxManaString = std::to_string(MAX_MANA);
    sf::String mString = manaString + " / " + maxManaString;
    m_mText.setString(mString);
    m_mText.setCharacterSize(20);
    m_mText.setColor(sf::Color::White);
    m_mText.setPosition(m_View.getCenter().x - 137, m_View.getCenter().y + 331);
    
    m_lvlText.setFont(m_Font);
    std::string levelString = std::to_string(m_Level);
    std::string maxLevelString = std::to_string(m_LvlCap);
    sf::String lvlString = levelString + " / " + maxLevelString;
    m_lvlText.setString(lvlString);
    m_lvlText.setCharacterSize(14);
    m_lvlText.setColor(sf::Color(92, 0, 0));
    m_lvlText.setPosition(m_View.getCenter().x + 253, m_View.getCenter().y + 294);
    
    m_expText.setFont(m_Font);
    std::string experienceString = std::to_string(m_Experience);
    std::string maxExperienceString = std::to_string(m_ExpCap);
    sf::String expString = experienceString + " / " + maxExperienceString;
    m_expText.setString(expString);
    m_expText.setCharacterSize(14);
    m_expText.setColor(sf::Color(92, 0, 0));
    m_expText.setPosition(m_View.getCenter().x + 298, m_View.getCenter().y + 272);
    
    m_waveText.setFont(m_Font);
    m_waveText.setCharacterSize(14);
    m_waveText.setColor(sf::Color(92, 0, 0));
    m_waveText.setPosition(m_View.getCenter().x + 334, m_View.getCenter().y + 328);
    
    m_scoreText.setFont(m_Font);
    std::string scoreString = std::to_string(m_Score);
    sf::String sString = scoreString;
    m_scoreText.setString(sString);
    m_scoreText.setCharacterSize(14);
    m_scoreText.setColor(sf::Color(92, 0, 0));
    m_scoreText.setPosition(m_View.getCenter().x + 260, m_View.getCenter().y + 352);
}

int Player::getHealth()
{
    return m_Health;
}

int Player::getMaxHealth()
{
    return MAX_HEALTH;
}

int Player::getMana()
{
    return m_Mana;
}

int Player::getMaxMana()
{
    return MAX_MANA;
}

int Player::getExp()
{
    return m_Experience;
}

int Player::getMaxExp()
{
    return m_ExpCap;
}

int Player::getLevel()
{
    return m_Level;
}

int Player::getMaxLevel()
{
    return m_LvlCap;
}

int Player::getScore()
{
    return m_Score;
}

void Player::setScore(int score)
{
    m_Score += score;
    
    std::string scoreString = std::to_string(m_Score);
    sf::String sString = scoreString;
    m_scoreText.setString(sString);
}

void Player::writeWave(MonsterSpawner& monsterSpawner)
{
    std::string waveType = std::to_string(monsterSpawner.getTypeIterator() + 1);
    std::string wavePart = std::to_string(monsterSpawner.getPartIterator() + 1);
    sf::String waveString = waveType + " - " + wavePart;
    m_waveText.setString(waveString);
}

void Player::waveCountDown(ClockManager& clockManager)
{
    std::string countDown = std::to_string(5 - clockManager.respawnTime());
    sf::String waveCountDown = "NEXT WAVE IN: " + countDown;
    m_waveText.setString(waveCountDown);
}

void Player::setTexture (const sf::Texture *texture)
{
    m_Sprite.sf::Sprite::setTexture(*texture, true);
}

void Player::setPosition(float x, float y)
{
    m_Sprite.sf::Sprite::setPosition(x, y);
}

const sf::Vector2f& Player::getPosition() const
{
    return m_Sprite.sf::Sprite::getPosition();
}

sf::Sprite Player::getPause()
{
    return pauseSprite;
}

void Player::meleeAttack(sf::RenderWindow &window)
{
    if(!isMelee)
    {
        isMelee = true;
        if (m_direction == "down")
        {
            mAttack.push_back (playerMelee(m_Sprite.getPosition().x, m_Sprite.getPosition().y + 104, &meleeTexture, m_direction, m_Damage));
        }
        else if (m_direction == "up")
        {
            mAttack.push_back (playerMelee(m_Sprite.getPosition().x, m_Sprite.getPosition().y - 104, &meleeTexture, m_direction, m_Damage));
        }
        meleeSound.play();
    }
}

void Player::rangedAttack(sf::RenderWindow &window)
{
    if (m_Mana >= 10)
    {
        isRanged = true;
        if (m_direction == "down")
        {
            rAttack.push_back (playerRanged(m_Sprite.getPosition().x, m_Sprite.getPosition().y + 104, &rangedTexture, m_direction, m_Damage));
        }
        else if (m_direction == "up")
        {
            rAttack.push_back (playerRanged(m_Sprite.getPosition().x, m_Sprite.getPosition().y - 104, &rangedTexture, m_direction, m_Damage));
        }
        m_Mana -= 10;
        manaBar.setTextureRect(sf::IntRect(manaBar.getPosition().x, manaBar.getPosition().y, (barTexture.getSize().x * m_Mana / MAX_MANA), barTexture.getSize().y));
        std::string manaString = std::to_string(m_Mana);
        std::string maxManaString = std::to_string(MAX_MANA);
        sf::String mString = manaString + " / " + maxManaString;
        m_mText.setString(mString);
        
        clk_mgr.resetManaHeal();
    }
}

void Player::incrementKill()
{
    killCount++;
}

void Player::healHealth()
{
    if (killCount == 10)
    {
        m_Health += MAX_HEALTH/5;
        if (m_Health > MAX_HEALTH)
        {
            m_Health = MAX_HEALTH;
        }
        m_Mana += MAX_MANA/5;
        if (m_Mana > MAX_MANA)
        {
            m_Mana = MAX_MANA;
        }
        
        sf::Clock clock;
        healSound.play();
        if (clock.getElapsedTime().asSeconds() == 1.0f)
        {
            healSound.stop();
        }
        
        healthBar.setTextureRect(sf::IntRect(healthBar.getPosition().x, healthBar.getPosition().y, (barTexture.getSize().x * m_Health / MAX_HEALTH), barTexture.getSize().y));
        std::string healthString = std::to_string(m_Health);
        std::string maxHealthString = std::to_string(MAX_HEALTH);
        sf::String hString = healthString + " / " + maxHealthString;
        m_hText.setString(hString);
        
        manaBar.setTextureRect(sf::IntRect(manaBar.getPosition().x, manaBar.getPosition().y, (barTexture.getSize().x * m_Mana / MAX_MANA), barTexture.getSize().y));
        std::string manaString = std::to_string(m_Mana);
        std::string maxManaString = std::to_string(MAX_MANA);
        sf::String mString = manaString + " / " + maxManaString;
        m_mText.setString(mString);
        
        killCount = 0;
    }
}

void Player::updateMana()
{
    if (clk_mgr.manaHealTime() >= 8.0 && m_Mana < MAX_MANA)
    {
        m_Mana += manaRegenRate;
        if (m_Mana > MAX_MANA)
        {
            m_Mana = MAX_MANA;
        }
        manaBar.setTextureRect(sf::IntRect(manaBar.getPosition().x, manaBar.getPosition().y, (barTexture.getSize().x * m_Mana / MAX_MANA), barTexture.getSize().y));
        std::string manaString = std::to_string(m_Mana);
        std::string maxManaString = std::to_string(MAX_MANA);
        sf::String mString = manaString + " / " + maxManaString;
        m_mText.setString(mString);
        clk_mgr.resetManaHeal();
    }
}

void Player::attacked(Monster& monster)
{
    if (Collision::BoundingBoxTest(m_Sprite, monster.getSprite()))
    {
        if (clk_mgr.invulTime() >= 0.5)
        {
            m_Health -= monster.getDamage();//calculate the percentage of the health bar to draw
            healthBar.setTextureRect(sf::IntRect(healthBar.getPosition().x, healthBar.getPosition().y, (barTexture.getSize().x * m_Health / MAX_HEALTH), barTexture.getSize().y));
            std::string healthString = std::to_string(m_Health);
            std::string maxHealthString = std::to_string(MAX_HEALTH);
            sf::String hString = healthString + " / " + maxHealthString;
            m_hText.setString(hString);
            
            hurtSound.play();
            
            if (monster.getPosition().y < m_Sprite.getPosition().y
                && m_Sprite.getPosition().y <= 1400)
            {
                m_Sprite.sf::Sprite::move(0, 32);
                m_yCoord += 32;
                if (m_Sprite.sf::Sprite::getPosition().y >= m_View.getCenter().y)
                {
                    if (m_View.sf::View::getCenter().y < (768*1.5) + 128)
                    {
                        m_View.sf::View::move(0, 32);
                        m_StatBar.sf::Sprite::move(0, 32);
                        healthBar.sf::Sprite::move(0, 32);
                        m_hText.move(0, 32);
                        manaBar.sf::Sprite::move(0, 32);
                        m_mText.move(0, 32);
                        m_expText.move(0, 32);
                        m_lvlText.move(0, 32);
                        m_waveText.move(0, 32);
                        m_scoreText.move(0, 32);
                    }
                    else
                    {
                        m_View.sf::View::move(0, 0);
                    }
                    pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
                    quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
                }
                
            }
            if (monster.getPosition().y > m_Sprite.getPosition().y
                && m_Sprite.getPosition().y >= 132)
            {
                m_Sprite.sf::Sprite::move(0, -32);
                m_yCoord -= 32;
                if (m_Sprite.sf::Sprite::getPosition().y <= m_View.getCenter().y)//move the camera
                {
                    if (m_View.sf::View::getCenter().y > (768/2))
                    {
                        m_View.sf::View::move(0, -32);
                        m_StatBar.sf::Sprite::move(0, -32);
                        healthBar.sf::Sprite::move(0, -32);
                        m_hText.move(0, -32);
                        manaBar.sf::Sprite::move(0, -32);
                        m_mText.move(0, -32);
                        m_expText.move(0, -32);
                        m_lvlText.move(0, -32);
                        m_waveText.move(0, -32);
                        m_scoreText.move(0, -32);
                    }
                    else
                    {
                        m_View.sf::View::move(0, 0);
                    }
                    pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
                    quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
                }
            }
            if (monster.getPosition().x < m_Sprite.getPosition().x
                && m_Sprite.getPosition().x <= 1968)
            {
                m_Sprite.sf::Sprite::move(32, 0);
                m_xCoord += 32;
                if (m_Sprite.sf::Sprite::getPosition().x <= m_View.getCenter().x)
                {
                    if (m_View.sf::View::getCenter().x > (1024/2))
                    {
                        m_View.sf::View::move(32, 0);
                        m_StatBar.sf::Sprite::move(32, 0);
                        healthBar.sf::Sprite::move(32, 0);
                        m_hText.move(32, 0);
                        manaBar.sf::Sprite::move(32, 0);
                        m_mText.move(32, 0);
                        m_expText.move(32, 0);
                        m_lvlText.move(32, 0);
                        m_waveText.move(32, 0);
                        m_scoreText.move(32, 0);
                    }
                    else
                    {
                        m_View.sf::View::move(0, 0);
                    }
                    pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
                    quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
                }
            }
            if (monster.getPosition().x > m_Sprite.getPosition().x
                && m_Sprite.getPosition().x >= 64)
            {
                m_Sprite.sf::Sprite::move(-32, 0);
                m_xCoord -= 32;
                if (m_Sprite.sf::Sprite::getPosition().x >= m_View.getCenter().x)
                {
                    if (m_View.sf::View::getCenter().x < (1024*1.5))
                    {
                        m_View.sf::View::move(-32, 0);
                        m_StatBar.sf::Sprite::move(-32, 0);
                        healthBar.sf::Sprite::move(-32, 0);
                        m_hText.move(-32, 0);
                        manaBar.sf::Sprite::move(-32, 0);
                        m_mText.move(-32, 0);
                        m_expText.move(-32, 0);
                        m_lvlText.move(-32, 0);
                        m_waveText.move(-32, 0);
                        m_scoreText.move(-32, 0);
                    }
                    else
                    {
                        m_View.sf::View::move(0, 0);
                    }
                    pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
                    quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
                }
            }
            
            clk_mgr.resetInvul();
        }
        
        
        m_Sprite.setColor(sf::Color(255, 255, 255, 128));
        colorClock.restart();
    }
    
    if (colorClock.getElapsedTime().asSeconds() >= 0.5)
    {
        m_Sprite.setColor(sf::Color(255, 255, 255, 255));
    }
    
    if (m_Health <= 0)
    {
        healthBar.setTextureRect(sf::IntRect(healthBar.getPosition().x, healthBar.getPosition().y, 0, 0));
        if (m_Health < 0)
        {
            m_Health = 0;
        }
        sf::Clock deadClock;
        
        if (deadClock.getElapsedTime().asMicroseconds() == 1)
            m_bDead = true;
    }
}

bool Player::isDead()
{
    return m_bDead;
}

void Player::gainExperience (int& exp)
{
    m_Experience += exp;
    
    std::string experienceString = std::to_string(m_Experience);
    std::string maxExperienceString = std::to_string(m_ExpCap);
    sf::String expString = experienceString + " / " + maxExperienceString;
    m_expText.setString(expString);
    
    if (m_Experience >= m_ExpCap && m_Level <= m_LvlCap)
    {
        m_Experience = 0;
        m_ExpCap *= 2;
        m_Level += 1;
        MAX_HEALTH += 40;
        MAX_MANA += 10;
        m_Health = MAX_HEALTH;
        m_Mana = MAX_MANA;
        manaRegenRate += 1;
        m_Damage += 5;
        
        levelSound.play();
        healthBar.setTextureRect(sf::IntRect(healthBar.getPosition().x, healthBar.getPosition().y, barTexture.getSize().x, barTexture.getSize().y));
        std::string healthString = std::to_string(m_Health);
        std::string maxHealthString = std::to_string(MAX_HEALTH);
        sf::String hString = healthString + " / " + maxHealthString;
        m_hText.setString(hString);
        
        manaBar.setTextureRect(sf::IntRect(manaBar.getPosition().x, manaBar.getPosition().y, barTexture.getSize().x, barTexture.getSize().y));
        std::string manaString = std::to_string(m_Mana);
        std::string maxManaString = std::to_string(MAX_MANA);
        sf::String mString = manaString + " / " + maxManaString;
        m_mText.setString(mString);
        
        std::string levelString = std::to_string(m_Level);
        std::string maxLevelString = std::to_string(m_LvlCap);
        sf::String lvlString = levelString + " / " + maxLevelString;
        m_lvlText.setString(lvlString);
        
        std::string experienceString = std::to_string(m_Experience);
        std::string maxExperienceString = std::to_string(m_ExpCap);
        sf::String expString = experienceString + " / " + maxExperienceString;
        m_expText.setString(expString);
    }
}

std::vector<playerMelee> Player::getMAttackVec()
{
    return mAttack;
}

void Player::clearAttack()
{
    if (isMelee)
    {
        for (int i = 0; i < mAttack.size(); ++i)
        {
            mAttack.erase(mAttack.begin() + i);
        }
        isMelee = false;
    }
}

void Player::moveUp()
{
    sf::IntRect tempRect (80, 0, 74, 204);
    repreRect = tempRect;
    m_Sprite.sf::Sprite::setTextureRect(tempRect);
    m_Sprite.sf::Sprite::setOrigin(repreRect.width/2, repreRect.height/2);
    m_direction = "up";
    
    if (m_Sprite.sf::Sprite::getPosition().y <= 136)
    {
        m_Sprite.sf::Sprite::move(0, 0);
    }
    else if (isMelee)
    {
        m_Sprite.sf::Sprite::move(0, 0);
    }
    else
    {
        m_Sprite.sf::Sprite::move(0, -16);
        m_yCoord -= 16;
        if (m_Sprite.sf::Sprite::getPosition().y <= m_View.getCenter().y)//move the camera
        {
            if (m_View.sf::View::getCenter().y > (768/2))
            {
                m_View.sf::View::move(0, -16);
                m_StatBar.sf::Sprite::move(0, -16);
                healthBar.sf::Sprite::move(0, -16);
                m_hText.move(0, -16);
                manaBar.sf::Sprite::move(0, -16);
                m_mText.move(0, -16);
                m_expText.move(0, -16);
                m_lvlText.move(0, -16);
                m_waveText.move(0, -16);
                m_scoreText.move(0, -16);
            }
            else
            {
                m_View.sf::View::move(0, 0);
            }
            pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
            quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
        }
    }

}

void Player::moveDown()
{
    sf::IntRect tempRect (0, 0, 80, 204);
    repreRect = tempRect;
    m_Sprite.sf::Sprite::setTextureRect(tempRect);
    m_Sprite.sf::Sprite::setOrigin(repreRect.width/2, repreRect.height/2);
    
    m_direction = "down";
    
    if (m_Sprite.sf::Sprite::getPosition().y >= 1536 - 136)
    {
        m_Sprite.sf::Sprite::move (0,0);
    }
    else if (isMelee)
    {
        m_Sprite.sf::Sprite::move(0, 0);
    }
    else
    {
        m_Sprite.sf::Sprite::move(0, 16);
        m_yCoord += 16;
        if (m_Sprite.sf::Sprite::getPosition().y >= m_View.getCenter().y)
        {
            if (m_View.sf::View::getCenter().y < (768*1.5) + 128)
            {
                m_View.sf::View::move(0, 16);
                m_StatBar.sf::Sprite::move(0, 16);
                healthBar.sf::Sprite::move(0, 16);
                m_hText.move(0, 16);
                manaBar.sf::Sprite::move(0, 16);
                m_mText.move(0, 16);
                m_expText.move(0, 16);
                m_lvlText.move(0, 16);
                m_waveText.move(0, 16);
                m_scoreText.move(0, 16);
            }
            else
            {
                m_View.sf::View::move(0, 0);
            }
            pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
            quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
        }
    }

}

void Player::moveLeft()
{
    if (m_Sprite.sf::Sprite::getPosition().x <= 48)
    {
        m_Sprite.sf::Sprite::move (0,0);
    }
    else if (isMelee)
    {
        m_Sprite.sf::Sprite::move(0, 0);
    }
    else
    {
        m_Sprite.sf::Sprite::move(-16, 0);
        m_xCoord -= -16;
        if (m_Sprite.sf::Sprite::getPosition().x <= m_View.getCenter().x)
        {
            if (m_View.sf::View::getCenter().x > (1024/2))
            {
                m_View.sf::View::move(-16, 0);
                m_StatBar.sf::Sprite::move(-16, 0);
                healthBar.sf::Sprite::move(-16, 0);
                m_hText.move(-16, 0);
                manaBar.sf::Sprite::move(-16, 0);
                m_mText.move(-16, 0);
                m_expText.move(-16, 0);
                m_lvlText.move(-16, 0);
                m_waveText.move(-16, 0);
                m_scoreText.move(-16, 0);
            }
            else
            {
                m_View.sf::View::move(0, 0);
            }
            pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
            quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
        }
    }
}

void Player::moveRight()
{
    if (m_Sprite.sf::Sprite::getPosition().x >= 2048 - 48)
    {
        m_Sprite.sf::Sprite::move (0,0);
    }
    else if (isMelee)
    {
        m_Sprite.sf::Sprite::move(0, 0);
    }
    else
    {
        m_Sprite.sf::Sprite::move(16, 0);
        m_xCoord += 16;
        if (m_Sprite.sf::Sprite::getPosition().x >= m_View.getCenter().x)
        {
            if (m_View.sf::View::getCenter().x < (1024*1.5))
            {
                m_View.sf::View::move(16, 0);
                m_StatBar.sf::Sprite::move(16, 0);
                healthBar.sf::Sprite::move(16, 0);
                m_hText.move(16, 0);
                manaBar.sf::Sprite::move(16, 0);
                m_mText.move(16, 0);
                m_expText.move(16, 0);
                m_lvlText.move(16, 0);
                m_waveText.move(16, 0);
                m_scoreText.move(16, 0);
            }
            else
            {
                m_View.sf::View::move(0, 0);
            }
            pauseSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 273);
            quitSprite.setPosition(m_View.getCenter().x + 464, m_View.getCenter().y + 321);
        }
    }

}

sf::Sprite Player::getSprite()
{
    return m_Sprite;
}

sf::Sprite Player::getStatBar()
{
    return m_StatBar;
}

sf::View Player::getView()
{
    return m_View;
}

sf::Text Player::getText()
{
    return m_hText;
}

std::string& Player::getDirection()
{
    return m_direction;
}

std::vector<playerRanged> Player::getRAttackVec()
{
    return rAttack;
}

void Player::Draw(sf::RenderWindow &window)
{
    if (isMelee)
    {
        for (int i = 0; i < mAttack.size(); ++i)
        {
            mAttack[i].Draw(window);
        }
    }
    if (isRanged)
    {
        for (int i = 0; i < rAttack.size(); ++i)
        {
            rAttack[i].move();
            rAttack[i].Draw(window);
        }
        if (rAttack.empty())
        {
            isRanged = false;
        }
    }
    
    window.draw(m_StatBar);
    window.draw(healthBar);
    window.draw(manaBar);
    window.draw(m_hText);
    window.draw(m_mText);
    window.draw(m_lvlText);
    window.draw(m_expText);
    window.draw(m_waveText);
    window.draw(m_scoreText);
    window.draw(m_Sprite);
    window.draw(pauseSprite);
    window.draw(quitSprite);
}

