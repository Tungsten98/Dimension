//
//  Game.h
//  Dimension
//
//  Created by 17xiangyangt on 1/19/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__Game__
#define __Dimension__Game__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameOverScreen.h"
#include "image_manager.h"
#include "Player.h"
#include "Monster.h"
#include "MonsterSpawner.h"
#include "Collision.h"
#include "ClockManager.h"

class Game
{
public:
    static void Start();
    
private:
    static bool IsExiting();
    static void GameLoop();
    
    enum GameState
    {
        Uninitialized,
        ShowingSplash,
        Paused,
        ShowingMenu,
        Playing,
        GameOver,
        Exiting
    };
    
    static void ShowSplashScreen();
    static void ShowMenu();
    static void PlayGame();
    static void ShowGameOver();
    
    static GameState _gameState;
    static sf::RenderWindow _mainWindow;
    
    static Player thePlayer;
};

#endif /* defined(__Dimension__Game__) */
