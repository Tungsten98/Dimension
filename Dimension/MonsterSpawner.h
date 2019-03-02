//
//  MonsterSpawner.h
//  Dimension
//
//  Created by 17xiangyangt on 1/21/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__MonsterSpawner__
#define __Dimension__MonsterSpawner__

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"
#include "image_manager.h"
#include "ClockManager.h"
#include "Monster.h"
#include "Player.h"
#include "Obstacle.h"

namespace sf
{
    class Texture;
    class Sprite;
    class SoundBuffer;
    class Sound;
    class Image;
}

class Monster;
class ClockManager;
class Obstacle;
class Potion;

class MonsterSpawner
{
private:
    std::vector<Monster> gameWave[8][10];
    std::vector<Obstacle> obstacles[8];
    sf::Sprite backgrounds[8];
    int waveTypeIterator;
    int wavePartIterator;
    image_manager img_mgr;
    ClockManager clk_mgr;
    void generateLevels();
    void generateBackground();

public:
    MonsterSpawner(Player& player);
    void copyToVec (std::vector<Monster>& monsterArray);
    void update();
    int getTypeIterator();
    int getPartIterator();
    sf::Sprite getBackground();
    std::vector<Obstacle> getObstacleArray();
    
private:
    Player* thePlayer;
    
    sf::Image creatures;
    sf::Image backgroundImages;
    sf::Image obstacleImages;
    
    sf::SoundBuffer changeD;
    sf::Sound changeSound;
    
    sf::Texture treeTexture;
    sf::Texture stoneTexture;
    sf::Texture mtnTreeTexture;
    sf::Texture snowTreeTexture;
    sf::Texture cactusTexture;
    sf::Texture netherStoneTexture;
    sf::Texture goldStoneTexture;
    
    sf::Texture forestTexture;
    sf::Sprite forestBackground;
    sf::Texture mountainTexture;
    sf::Sprite mountainBackground;
    sf::Texture snowTexture;
    sf::Sprite snowBackground;
    sf::Texture desertTexture;
    sf::Sprite desertBackground;
    sf::Texture netherTexture;
    sf::Sprite netherBackground;
    sf::Texture riftTexture;
    sf::Sprite riftBackground;
    
    sf::Texture DarkBush;
    sf::Texture GiantSpider;
    sf::Texture Imp;
    sf::Texture DarkEnt;
    sf::Texture PosMan;
    sf::Texture SkeletonBeast;
    sf::Texture SkeletonMan;
    
    sf::Texture Bush;
    sf::Texture CycloneMan;
    sf::Texture Ent;
    sf::Texture GiantBat;
    sf::Texture Minotaur;
    sf::Texture Ogre;
    sf::Texture StoneGolem;
    
    sf::Texture SnowBush;
    sf::Texture EvergreenEnt;
    sf::Texture SnowGolem;
    sf::Texture SnowGuardian;
    sf::Texture SnowMan;
    sf::Texture SnowTitan;
    sf::Texture SnowWarrior;
    
    sf::Texture CactusMan;
    sf::Texture Scorpion;
    sf::Texture BandedBeast;
    sf::Texture HalBandit;
    sf::Texture LizardMan;
    sf::Texture Mummy;
    sf::Texture PHalBandit;
    sf::Texture SwoBandit;
    sf::Texture PSwoBandit;
};

#endif /* defined(__Dimension__MonsterSpawner__) */
