//
//  ClockManager.h
//  Dimension
//
//  Created by 17xiangyangt on 1/23/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__ClockManager__
#define __Dimension__ClockManager__

#include <iostream>
#include <SFML/Graphics.hpp>

namespace sf
{
    class Clock;
    class Time;
}

class ClockManager: public sf::Clock
{
private:
    sf::Clock meleeClock;
    sf::Clock meleeCoolDown;
    sf::Clock rangedCoolDown;
    sf::Clock manaHealClock;
    sf::Clock gameOverClock;
    sf::Clock invulClock;
    sf::Clock respawnClock;
    
public:
    ClockManager();
    ~ClockManager();
    
    float meleeTime();
    float mCoolDownTime();
    float rCoolDownTime();
    float gameOverTime();
    float invulTime();
    float manaHealTime();
    int respawnTime();
    
    void resetMeleeTime();
    void resetMeleeCoolDown();
    void resetRangedCoolDown();
    void resetGameOver();
    void resetInvul();
    void resetRespawn();
    void resetManaHeal();
};

#endif /* defined(__Dimension__ClockManager__) */
