//
//  ClockManager.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/23/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "ClockManager.h"

ClockManager::ClockManager(){}

ClockManager::~ClockManager(){}

float ClockManager::meleeTime()
{
    return meleeClock.getElapsedTime().asSeconds();
}

float ClockManager::mCoolDownTime()
{
    return meleeCoolDown.getElapsedTime().asSeconds();
}

float ClockManager::rCoolDownTime()
{
    return rangedCoolDown.getElapsedTime().asSeconds();
}

float ClockManager::manaHealTime()
{
    return manaHealClock.getElapsedTime().asSeconds();
}

float ClockManager::gameOverTime()
{
    return gameOverClock.getElapsedTime().asSeconds();
}

float ClockManager::invulTime()
{
    return invulClock.getElapsedTime().asSeconds();
}

int ClockManager::respawnTime()
{
    return respawnClock.getElapsedTime().asSeconds();
}

void ClockManager::resetMeleeTime()
{
    meleeClock.restart();
}

void ClockManager::resetMeleeCoolDown()
{
    meleeCoolDown.restart();
}

void ClockManager::resetRangedCoolDown()
{
    rangedCoolDown.restart();
}

void ClockManager::resetManaHeal()
{
    manaHealClock.restart();
}

void ClockManager::resetGameOver()
{
    gameOverClock.restart();
}

void ClockManager::resetInvul()
{
    invulClock.restart();
}

void ClockManager::resetRespawn()
{
    respawnClock.restart();
}