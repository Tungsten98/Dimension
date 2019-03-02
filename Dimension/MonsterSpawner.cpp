//
//  MonsterSpawner.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/21/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "MonsterSpawner.h"

MonsterSpawner::MonsterSpawner(Player& player)
{
    thePlayer = &player;
    waveTypeIterator = 0;
    wavePartIterator = 1;//-1;
    
    if (!creatures.loadFromFile(resourcePath() + "spritesheet.png"))
    {
        return;
    }
    if (!obstacleImages.loadFromFile(resourcePath() + "obstacles.png"))
    {
        return;
    }
    if (!backgroundImages.loadFromFile(resourcePath() + "backgrounds.png"))
    {
        return;
    }
    
    forestTexture.loadFromImage(backgroundImages, sf::IntRect(0, 0, 2048, 1536));
    mountainTexture.loadFromImage(backgroundImages, sf::IntRect(0, 0, 2048, 1536));
    snowTexture.loadFromImage(backgroundImages, sf::IntRect(2048, 0, 2048, 1536));
    desertTexture.loadFromImage(backgroundImages, sf::IntRect(0, 1536, 2048, 1536));
    
    stoneTexture.loadFromImage(obstacleImages, sf::IntRect(0, 0, 74, 73));
    treeTexture.loadFromImage(obstacleImages, sf::IntRect(74, 0, 123, 184));
    mtnTreeTexture.loadFromImage(obstacleImages, sf::IntRect(197, 0, 123, 184));
    snowTreeTexture.loadFromImage(obstacleImages, sf::IntRect(320, 0, 80, 200));
    cactusTexture.loadFromImage(obstacleImages, sf::IntRect(0, 200, 131, 201));
    
    DarkBush.loadFromImage(creatures, sf::IntRect(0, 0, 408, 161));
    GiantSpider.loadFromImage(creatures, sf::IntRect(409, 0, 332, 173));
    DarkEnt.loadFromImage(creatures, sf::IntRect(746, 0, 274, 198));
    Imp.loadFromImage(creatures, sf::IntRect(1000, 0, 134, 98));
    PosMan.loadFromImage(creatures, sf::IntRect(1134, 0, 124, 198));
    SkeletonBeast.loadFromImage(creatures, sf::IntRect(1258, 0, 202, 151));
    SkeletonMan.loadFromImage(creatures, sf::IntRect(1460, 0, 212, 199));
    
    Bush.loadFromImage(creatures, sf::IntRect(0, 199, 436, 102));
    CycloneMan.loadFromImage(creatures, sf::IntRect(436, 199, 284, 199));
    Ent.loadFromImage(creatures, sf::IntRect(720, 199, 286, 199));
    GiantBat.loadFromImage(creatures, sf::IntRect(1006, 199, 388, 150));
    Minotaur.loadFromImage(creatures, sf::IntRect(1394, 199, 162, 196));
    Ogre.loadFromImage(creatures, sf::IntRect(1556, 199, 152, 198));
    StoneGolem.loadFromImage(creatures, sf::IntRect(0, 301, 158, 197));
    
    SnowBush.loadFromImage(creatures, sf::IntRect(0, 498, 436, 102));
    EvergreenEnt.loadFromImage(creatures, sf::IntRect(498, 401, 250, 198));
    SnowMan.loadFromImage(creatures, sf::IntRect(686, 498, 400, 199));
    SnowWarrior.loadFromImage(creatures, sf::IntRect(1086, 498, 290, 199));
    SnowGolem.loadFromImage(creatures, sf::IntRect(1376, 498, 216, 245));
    SnowGuardian.loadFromImage(creatures, sf::IntRect(1592, 498, 220, 197));
    SnowTitan.loadFromImage(creatures, sf::IntRect(0, 576, 180, 245));
    
    
    CactusMan.loadFromImage(creatures, sf::IntRect(0, 821, 262, 201));
    Scorpion.loadFromImage(creatures, sf::IntRect(262, 821, 266, 199));
    LizardMan.loadFromImage(creatures, sf::IntRect(528, 821, 326, 249));
    BandedBeast.loadFromImage(creatures, sf::IntRect(854, 821, 334, 250));
    Mummy.loadFromImage(creatures, sf::IntRect(1188, 821, 154, 199));
    SwoBandit.loadFromImage(creatures, sf::IntRect(1342, 821, 230, 199));
    HalBandit.loadFromImage(creatures, sf::IntRect(1572, 821, 232, 199));
    PSwoBandit.loadFromImage(creatures, sf::IntRect(0, 1022, 230, 199));
    PHalBandit.loadFromImage(creatures, sf::IntRect(230, 1022, 232, 199));
    
    if (changeD.loadFromFile(resourcePath() + "End_Fx.wav"))
    {
        changeSound.setBuffer(changeD);
    }
    
    generateLevels();
    generateBackground();
}

void MonsterSpawner::generateBackground()
{
    forestBackground.setTexture(forestTexture);
    forestBackground.setColor(sf::Color(204, 204, 204));
    mountainBackground.setTexture(mountainTexture);
    snowBackground.setTexture(snowTexture);
    desertBackground.setTexture(desertTexture);
    netherBackground.setTexture(netherTexture);
    riftBackground.setTexture(riftTexture);
    riftBackground.setColor(sf::Color(255, 255, 180));
    
    backgrounds[0] = forestBackground;
    backgrounds[1] = mountainBackground;
    backgrounds[2] = forestBackground;
    backgrounds[3] = snowBackground;
    backgrounds[4] = forestBackground;
    backgrounds[5] = desertBackground;
    
    //forest part 1
    obstacles[0].push_back(Obstacle(&treeTexture, 606, 201));
    obstacles[0].push_back(Obstacle(&treeTexture, 1000, 603));
    obstacles[0].push_back(Obstacle(&treeTexture, 1536, 873));
    obstacles[0].push_back(Obstacle(&treeTexture, 260, 991));
    obstacles[0].push_back(Obstacle(&treeTexture, 1836, 530));
    obstacles[0].push_back(Obstacle(&stoneTexture, 719, 1293));
    obstacles[0].push_back(Obstacle(&stoneTexture, 1286, 705));
    obstacles[0].push_back(Obstacle(&stoneTexture, 1745, 1101));
    obstacles[0].push_back(Obstacle(&stoneTexture, 920, 990));
    obstacles[0].push_back(Obstacle(&stoneTexture, 302, 172));
    
    //mountain dimension
    obstacles[1].push_back(Obstacle(&mtnTreeTexture, 200, 150));
    obstacles[1].push_back(Obstacle(&mtnTreeTexture, 500, 400));
    obstacles[1].push_back(Obstacle(&mtnTreeTexture, 800, 650));
    obstacles[1].push_back(Obstacle(&mtnTreeTexture, 1150, 462));
    obstacles[1].push_back(Obstacle(&mtnTreeTexture, 1900, 1000));
    obstacles[1].push_back(Obstacle(&stoneTexture, 174, 1293));
    obstacles[1].push_back(Obstacle(&stoneTexture, 1386, 968));
    obstacles[1].push_back(Obstacle(&stoneTexture, 508, 1623));
    obstacles[1].push_back(Obstacle(&stoneTexture, 900, 176));
    obstacles[1].push_back(Obstacle(&stoneTexture, 1736, 217));
    
    //forest part 2
    obstacles[2].push_back(Obstacle(&treeTexture, 606, 201));
    obstacles[2].push_back(Obstacle(&treeTexture, 1000, 603));
    obstacles[2].push_back(Obstacle(&treeTexture, 1536, 873));
    obstacles[2].push_back(Obstacle(&treeTexture, 260, 991));
    obstacles[2].push_back(Obstacle(&treeTexture, 1836, 530));
    obstacles[2].push_back(Obstacle(&stoneTexture, 719, 1293));
    obstacles[2].push_back(Obstacle(&stoneTexture, 1286, 705));
    obstacles[2].push_back(Obstacle(&stoneTexture, 1745, 1101));
    obstacles[2].push_back(Obstacle(&stoneTexture, 920, 990));
    obstacles[2].push_back(Obstacle(&stoneTexture, 302, 172));
    
    //snow dimension
    obstacles[3].push_back(Obstacle(&stoneTexture, 200, 150));
    obstacles[3].push_back(Obstacle(&stoneTexture, 500, 400));
    obstacles[3].push_back(Obstacle(&stoneTexture, 800, 650));
    obstacles[3].push_back(Obstacle(&stoneTexture, 1150, 462));
    obstacles[3].push_back(Obstacle(&stoneTexture, 1900, 1000));
    obstacles[3].push_back(Obstacle(&snowTreeTexture, 174, 1293));
    obstacles[3].push_back(Obstacle(&snowTreeTexture, 1386, 968));
    obstacles[3].push_back(Obstacle(&snowTreeTexture, 508, 1623));
    obstacles[3].push_back(Obstacle(&snowTreeTexture, 900, 176));
    obstacles[3].push_back(Obstacle(&snowTreeTexture, 1736, 217));
    
    //forest part 3
    obstacles[4].push_back(Obstacle(&treeTexture, 606, 201));
    obstacles[4].push_back(Obstacle(&treeTexture, 1000, 603));
    obstacles[4].push_back(Obstacle(&treeTexture, 1536, 873));
    obstacles[4].push_back(Obstacle(&treeTexture, 260, 991));
    obstacles[4].push_back(Obstacle(&treeTexture, 1836, 530));
    obstacles[4].push_back(Obstacle(&stoneTexture, 719, 1293));
    obstacles[4].push_back(Obstacle(&stoneTexture, 1286, 705));
    obstacles[4].push_back(Obstacle(&stoneTexture, 1745, 1101));
    obstacles[4].push_back(Obstacle(&stoneTexture, 920, 990));
    obstacles[4].push_back(Obstacle(&stoneTexture, 302, 172));
    
    //desert dimension
    obstacles[5].push_back(Obstacle(&cactusTexture, 200, 150));
    obstacles[5].push_back(Obstacle(&cactusTexture, 500, 400));
    obstacles[5].push_back(Obstacle(&cactusTexture, 800, 650));
    obstacles[5].push_back(Obstacle(&cactusTexture, 1150, 462));
    obstacles[5].push_back(Obstacle(&cactusTexture, 1900, 1000));
    obstacles[5].push_back(Obstacle(&stoneTexture, 174, 1293));
    obstacles[5].push_back(Obstacle(&stoneTexture, 1386, 968));
    obstacles[5].push_back(Obstacle(&stoneTexture, 508, 1623));
    obstacles[5].push_back(Obstacle(&stoneTexture, 900, 176));
    obstacles[5].push_back(Obstacle(&stoneTexture, 1736, 217));
}

void MonsterSpawner::generateLevels()
{
    //forest part, part 1
    gameWave[0][0].push_back(Monster(&DarkBush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][0].push_back(Monster(&DarkBush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][0].push_back(Monster(&DarkBush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[0][0].push_back(Monster(&DarkBush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[0][0].push_back(Monster(&DarkBush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    
    gameWave[0][1].push_back(Monster(&DarkBush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][1].push_back(Monster(&DarkBush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][1].push_back(Monster(&DarkBush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[0][1].push_back(Monster(&DarkBush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[0][1].push_back(Monster(&DarkBush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[0][1].push_back(Monster(&GiantSpider, 1024+364, 768-263, *thePlayer, 10, 40, 20));
    gameWave[0][1].push_back(Monster(&GiantSpider, 1024-353, 768+454, *thePlayer, 10, 40, 20));
    gameWave[0][1].push_back(Monster(&GiantSpider, 1024-830, 768-576, *thePlayer, 10, 40, 20));
    gameWave[0][1].push_back(Monster(&GiantSpider, 1024-95, 768+166, *thePlayer, 10, 40, 20));
    gameWave[0][1].push_back(Monster(&GiantSpider, 1024+585, 768+452, *thePlayer, 10, 40, 20));
    
    gameWave[0][2].push_back(Monster(&DarkBush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][2].push_back(Monster(&DarkBush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][2].push_back(Monster(&DarkBush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[0][2].push_back(Monster(&DarkBush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[0][2].push_back(Monster(&DarkBush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[0][2].push_back(Monster(&Imp, 1024+364, 768-263, *thePlayer, 5, 25, 10));
    gameWave[0][2].push_back(Monster(&Imp, 1024-353, 768+454, *thePlayer, 5, 25, 10));
    gameWave[0][2].push_back(Monster(&Imp, 1024-830, 768-576, *thePlayer, 5, 25, 10));
    gameWave[0][2].push_back(Monster(&Imp, 1024-95, 768+166, *thePlayer, 5, 25, 10));
    gameWave[0][2].push_back(Monster(&Imp, 1024+585, 768+452, *thePlayer, 5, 25, 10));
    gameWave[0][2].push_back(Monster(&DarkEnt, 1024+261, 768+563, *thePlayer, 20, 80, 40));
    gameWave[0][2].push_back(Monster(&DarkEnt, 1024-125, 768+252, *thePlayer, 20, 80, 40));
    gameWave[0][2].push_back(Monster(&DarkEnt, 1024-354, 768+192, *thePlayer, 20, 80, 40));
    gameWave[0][2].push_back(Monster(&DarkEnt, 1024+586, 768-466, *thePlayer, 20, 80, 40));
    gameWave[0][2].push_back(Monster(&DarkEnt, 1024+702, 768-163, *thePlayer, 20, 80, 40));
    
    gameWave[0][3].push_back(Monster(&DarkBush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][3].push_back(Monster(&DarkBush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[0][3].push_back(Monster(&DarkBush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[0][3].push_back(Monster(&DarkBush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[0][3].push_back(Monster(&DarkBush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[0][3].push_back(Monster(&Imp, 1024+364, 768-263, *thePlayer, 5, 25, 10));
    gameWave[0][3].push_back(Monster(&Imp, 1024-353, 768+454, *thePlayer, 5, 25, 10));
    gameWave[0][3].push_back(Monster(&Imp, 1024-830, 768-576, *thePlayer, 5, 25, 10));
    gameWave[0][3].push_back(Monster(&Imp, 1024-95, 768+166, *thePlayer, 5, 25, 10));
    gameWave[0][3].push_back(Monster(&Imp, 1024+585, 768+452, *thePlayer, 5, 25, 10));
    gameWave[0][3].push_back(Monster(&DarkEnt, 1024+261, 768+563, *thePlayer, 20, 80, 40));
    gameWave[0][3].push_back(Monster(&DarkEnt, 1024-125, 768+252, *thePlayer, 20, 80, 40));
    gameWave[0][3].push_back(Monster(&DarkEnt, 1024-354, 768+192, *thePlayer, 20, 80, 40));
    gameWave[0][3].push_back(Monster(&DarkEnt, 1024+586, 768-466, *thePlayer, 20, 80, 40));
    gameWave[0][3].push_back(Monster(&DarkEnt, 1024+702, 768-163, *thePlayer, 20, 80, 40));
    
    //mountain dimension
    gameWave[1][0].push_back(Monster(&Bush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024+364, 768-263, *thePlayer, 5, 25, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024-353, 768+454, *thePlayer, 5, 25, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024-830, 768-576, *thePlayer, 5, 25, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024-95, 768+166, *thePlayer, 5, 25, 10));
    gameWave[1][0].push_back(Monster(&Bush, 1024+585, 768+452, *thePlayer, 5, 25, 10));
    
    gameWave[1][1].push_back(Monster(&Bush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][1].push_back(Monster(&Bush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][1].push_back(Monster(&Bush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[1][1].push_back(Monster(&Bush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[1][1].push_back(Monster(&Bush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[1][1].push_back(Monster(&Ent, 1024+364, 768-263, *thePlayer, 10, 40, 20));
    gameWave[1][1].push_back(Monster(&Ent, 1024-353, 768+454, *thePlayer, 10, 40, 20));
    gameWave[1][1].push_back(Monster(&Ent, 1024-830, 768-576, *thePlayer, 10, 40, 20));
    gameWave[1][1].push_back(Monster(&Ent, 1024-95, 768+166, *thePlayer, 10, 40, 20));
    gameWave[1][1].push_back(Monster(&Ent, 1024+585, 768+452, *thePlayer, 10, 40, 20));
    
    gameWave[1][2].push_back(Monster(&Bush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][2].push_back(Monster(&Bush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][2].push_back(Monster(&Bush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[1][2].push_back(Monster(&Bush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[1][2].push_back(Monster(&Bush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[1][2].push_back(Monster(&Ent, 1024+364, 768-263, *thePlayer, 10, 40, 20));
    gameWave[1][2].push_back(Monster(&Ent, 1024-353, 768+454, *thePlayer, 10, 40, 20));
    gameWave[1][2].push_back(Monster(&Ent, 1024-830, 768-576, *thePlayer, 10, 40, 20));
    gameWave[1][2].push_back(Monster(&Ent, 1024-95, 768+166, *thePlayer, 10, 40, 20));
    gameWave[1][2].push_back(Monster(&Ent, 1024+585, 768+452, *thePlayer, 10, 40, 20));
    gameWave[1][2].push_back(Monster(&CycloneMan, 1623, 548, *thePlayer, 15, 50, 30));
    gameWave[1][2].push_back(Monster(&CycloneMan, 165, 348, *thePlayer, 15, 50, 30));
    gameWave[1][2].push_back(Monster(&CycloneMan, 1725, 1256, *thePlayer, 15, 50, 30));
    gameWave[1][2].push_back(Monster(&CycloneMan, 674, 725, *thePlayer, 15, 50, 30));
    gameWave[1][2].push_back(Monster(&CycloneMan, 283, 1029, *thePlayer, 15, 50, 30));
    
    gameWave[1][3].push_back(Monster(&Bush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][3].push_back(Monster(&Bush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[1][3].push_back(Monster(&Bush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[1][3].push_back(Monster(&Bush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[1][3].push_back(Monster(&Bush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[1][3].push_back(Monster(&Ent, 1024+364, 768-263, *thePlayer, 10, 40, 20));
    gameWave[1][3].push_back(Monster(&Ent, 1024-353, 768+454, *thePlayer, 10, 40, 20));
    gameWave[1][3].push_back(Monster(&Ent, 1024-830, 768-576, *thePlayer, 10, 40, 20));
    gameWave[1][3].push_back(Monster(&Ent, 1024-95, 768+166, *thePlayer, 10, 40, 20));
    gameWave[1][3].push_back(Monster(&Ent, 1024+585, 768+452, *thePlayer, 10, 40, 20));
    gameWave[1][3].push_back(Monster(&CycloneMan, 1623, 548, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 165, 348, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 1725, 1256, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 674, 725, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 283, 1029, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 473, 329, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 857, 596, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 1029, 397, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 238, 721, *thePlayer, 15, 50, 30));
    gameWave[1][3].push_back(Monster(&CycloneMan, 380, 1726, *thePlayer, 15, 50, 30));
    
    gameWave[1][4].push_back(Monster(&GiantBat, 1024/2, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][4].push_back(Monster(&GiantBat, 1024*1.5, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][4].push_back(Monster(&GiantBat, 1024*1.5, 768*1.5, *thePlayer, 15, 55, 30));
    gameWave[1][4].push_back(Monster(&GiantBat, 1024*1.75, 768/1.75, *thePlayer, 15, 55, 30));
    gameWave[1][4].push_back(Monster(&GiantBat, 1024/1.75, 768*1.75, *thePlayer, 15, 55, 30));
    gameWave[1][4].push_back(Monster(&Ent, 1024+364, 768-263, *thePlayer, 10, 40, 20));
    gameWave[1][4].push_back(Monster(&Ent, 1024-353, 768+454, *thePlayer, 10, 40, 20));
    gameWave[1][4].push_back(Monster(&Ent, 1024-830, 768-576, *thePlayer, 10, 40, 20));
    gameWave[1][4].push_back(Monster(&Ent, 1024-95, 768+166, *thePlayer, 10, 40, 20));
    gameWave[1][4].push_back(Monster(&Ent, 1024+585, 768+452, *thePlayer, 10, 40, 20));
    gameWave[1][4].push_back(Monster(&CycloneMan, 1623, 548, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 165, 348, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 1725, 1256, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 674, 725, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 283, 1029, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 473, 329, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 857, 596, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 1029, 397, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 238, 721, *thePlayer, 15, 50, 30));
    gameWave[1][4].push_back(Monster(&CycloneMan, 380, 1726, *thePlayer, 15, 50, 30));
    
    gameWave[1][5].push_back(Monster(&GiantBat, 1024/2, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][5].push_back(Monster(&GiantBat, 1024*1.5, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][5].push_back(Monster(&GiantBat, 1024*1.5, 768*1.5, *thePlayer, 15, 55, 30));
    gameWave[1][5].push_back(Monster(&GiantBat, 1024*1.75, 768/1.75, *thePlayer, 15, 55, 30));
    gameWave[1][5].push_back(Monster(&GiantBat, 1024/1.75, 768*1.75, *thePlayer, 15, 55, 30));
    gameWave[1][5].push_back(Monster(&Minotaur, 1024+364, 768-263, *thePlayer, 20, 60, 35));
    gameWave[1][5].push_back(Monster(&Minotaur, 1024-353, 768+454, *thePlayer, 20, 60, 35));
    gameWave[1][5].push_back(Monster(&Minotaur, 1024-830, 768-576, *thePlayer, 20, 60, 35));
    gameWave[1][5].push_back(Monster(&Minotaur, 1024-95, 768+166, *thePlayer, 20, 60, 35));
    gameWave[1][5].push_back(Monster(&Minotaur, 1024+585, 768+452, *thePlayer, 20, 60, 35));
    gameWave[1][5].push_back(Monster(&CycloneMan, 1623, 548, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 165, 348, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 1725, 1256, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 674, 725, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 283, 1029, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 473, 329, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 857, 596, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 1029, 397, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 238, 721, *thePlayer, 15, 50, 30));
    gameWave[1][5].push_back(Monster(&CycloneMan, 380, 1726, *thePlayer, 15, 50, 30));
    
    gameWave[1][6].push_back(Monster(&GiantBat, 1024/2, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][6].push_back(Monster(&GiantBat, 1024*1.5, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][6].push_back(Monster(&GiantBat, 1024*1.5, 768*1.5, *thePlayer, 15, 55, 30));
    gameWave[1][6].push_back(Monster(&GiantBat, 1024*1.75, 768/1.75, *thePlayer, 15, 55, 30));
    gameWave[1][6].push_back(Monster(&GiantBat, 1024/1.75, 768*1.75, *thePlayer, 15, 55, 30));
    gameWave[1][6].push_back(Monster(&Minotaur, 1024+364, 768-263, *thePlayer, 20, 60, 35));
    gameWave[1][6].push_back(Monster(&Minotaur, 1024-353, 768+454, *thePlayer, 20, 60, 35));
    gameWave[1][6].push_back(Monster(&Minotaur, 1024-830, 768-576, *thePlayer, 20, 60, 35));
    gameWave[1][6].push_back(Monster(&Minotaur, 1024-95, 768+166, *thePlayer, 20, 60, 35));
    gameWave[1][6].push_back(Monster(&Minotaur, 1024+585, 768+452, *thePlayer, 20, 60, 35));
    gameWave[1][6].push_back(Monster(&CycloneMan, 1623, 548, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 165, 348, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 1725, 1256, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 674, 725, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 283, 1029, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 473, 329, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 857, 596, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 1029, 397, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 238, 721, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&CycloneMan, 380, 1726, *thePlayer, 15, 50, 30));
    gameWave[1][6].push_back(Monster(&StoneGolem, 919, 475, *thePlayer, 20, 80, 30));
    gameWave[1][6].push_back(Monster(&StoneGolem, 172, 439, *thePlayer, 20, 80, 30));
    gameWave[1][6].push_back(Monster(&StoneGolem, 487, 102, *thePlayer, 20, 80, 30));
    gameWave[1][6].push_back(Monster(&StoneGolem, 587, 857, *thePlayer, 20, 80, 30));
    gameWave[1][6].push_back(Monster(&StoneGolem, 1625, 1053, *thePlayer, 20, 80, 30));
    
    gameWave[1][7].push_back(Monster(&GiantBat, 1024/2, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][7].push_back(Monster(&GiantBat, 1024*1.5, 768/2, *thePlayer, 15, 55, 30));
    gameWave[1][7].push_back(Monster(&GiantBat, 1024*1.5, 768*1.5, *thePlayer, 15, 55, 30));
    gameWave[1][7].push_back(Monster(&GiantBat, 1024*1.75, 768/1.75, *thePlayer, 15, 55, 30));
    gameWave[1][7].push_back(Monster(&GiantBat, 1024/1.75, 768*1.75, *thePlayer, 15, 55, 30));
    gameWave[1][7].push_back(Monster(&Minotaur, 1024+364, 768-263, *thePlayer, 20, 60, 35));
    gameWave[1][7].push_back(Monster(&Minotaur, 1024-353, 768+454, *thePlayer, 20, 60, 35));
    gameWave[1][7].push_back(Monster(&Minotaur, 1024-830, 768-576, *thePlayer, 20, 60, 35));
    gameWave[1][7].push_back(Monster(&Minotaur, 1024-95, 768+166, *thePlayer, 20, 60, 35));
    gameWave[1][7].push_back(Monster(&Minotaur, 1024+585, 768+452, *thePlayer, 20, 60, 35));
    gameWave[1][7].push_back(Monster(&Ogre, 1623, 548, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 165, 348, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 1725, 1256, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 674, 725, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 283, 1029, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 473, 329, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 857, 596, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 238, 721, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 380, 1726, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&Ogre, 1029, 397, *thePlayer, 35, 90, 45));
    gameWave[1][7].push_back(Monster(&StoneGolem, 919, 475, *thePlayer, 20, 80, 30));
    gameWave[1][7].push_back(Monster(&StoneGolem, 172, 439, *thePlayer, 20, 80, 30));
    gameWave[1][7].push_back(Monster(&StoneGolem, 487, 102, *thePlayer, 20, 80, 30));
    gameWave[1][7].push_back(Monster(&StoneGolem, 587, 857, *thePlayer, 20, 80, 30));
    gameWave[1][7].push_back(Monster(&StoneGolem, 1625, 1053, *thePlayer, 20, 80, 30));
    
    gameWave[1][8].push_back(Monster(&Ogre, 1024/2, 768/2, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024*1.5, 768/2, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024*1.5, 768*1.5, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024*1.75, 768/1.75, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024/1.75, 768*1.75, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024+364, 768-263, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024-353, 768+454, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024-830, 768-576, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024-95, 768+166, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1024+585, 768+452, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1623, 548, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 165, 348, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 1725, 1256, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 674, 725, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&Ogre, 283, 1029, *thePlayer, 35, 90, 45));
    gameWave[1][8].push_back(Monster(&StoneGolem, 473, 329, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 857, 596, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 238, 721, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 380, 1726, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 1029, 397, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 919, 475, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 172, 439, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 487, 102, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 587, 857, *thePlayer, 20, 80, 30));
    gameWave[1][8].push_back(Monster(&StoneGolem, 1625, 1053, *thePlayer, 20, 80, 30));
    
    gameWave[1][9].push_back(Monster(&Ogre, 1024/2, 768/2, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024*1.5, 768/2, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024*1.5, 768*1.5, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024*1.75, 768/1.75, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024/1.75, 768*1.75, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024+364, 768-263, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024-353, 768+454, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024-830, 768-576, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024-95, 768+166, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1024+585, 768+452, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1623, 548, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 165, 348, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1725, 1256, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 674, 725, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 283, 1029, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 473, 329, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 857, 596, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 238, 721, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 380, 1726, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1029, 397, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 919, 475, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 172, 439, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 487, 102, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 587, 857, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 408, 1218, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 981, 158, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 195, 177, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1192, 495, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 508, 1276, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 485, 213, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 324, 421, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 283, 943, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 592, 1238, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1239, 836, *thePlayer, 35, 90, 45));
    gameWave[1][9].push_back(Monster(&Ogre, 1769, 239, *thePlayer, 35, 90, 45));
    
    //forest part 2
    gameWave[2][0].push_back(Monster(&DarkBush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[2][0].push_back(Monster(&DarkBush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[2][0].push_back(Monster(&DarkBush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[2][0].push_back(Monster(&DarkBush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[2][0].push_back(Monster(&DarkBush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[2][0].push_back(Monster(&GiantSpider, 1024+364, 768-263, *thePlayer, 10, 40, 20));
    gameWave[2][0].push_back(Monster(&GiantSpider, 1024-353, 768+454, *thePlayer, 10, 40, 20));
    gameWave[2][0].push_back(Monster(&GiantSpider, 1024-830, 768-576, *thePlayer, 10, 40, 20));
    gameWave[2][0].push_back(Monster(&GiantSpider, 1024-95, 768+166, *thePlayer, 10, 40, 20));
    gameWave[2][0].push_back(Monster(&GiantSpider, 1024+585, 768+452, *thePlayer, 10, 40, 20));
    
    gameWave[2][1].push_back(Monster(&DarkBush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[2][1].push_back(Monster(&DarkBush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[2][1].push_back(Monster(&DarkBush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[2][1].push_back(Monster(&DarkBush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[2][1].push_back(Monster(&DarkBush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[2][1].push_back(Monster(&Imp, 1024+364, 768-263, *thePlayer, 5, 25, 10));
    gameWave[2][1].push_back(Monster(&Imp, 1024-353, 768+454, *thePlayer, 5, 25, 10));
    gameWave[2][1].push_back(Monster(&Imp, 1024-830, 768-576, *thePlayer, 5, 25, 10));
    gameWave[2][1].push_back(Monster(&Imp, 1024-95, 768+166, *thePlayer, 5, 25, 10));
    gameWave[2][1].push_back(Monster(&Imp, 1024+585, 768+452, *thePlayer, 5, 25, 10));
    gameWave[2][1].push_back(Monster(&DarkEnt, 1024+261, 768+563, *thePlayer, 20, 80, 40));
    gameWave[2][1].push_back(Monster(&DarkEnt, 1024-125, 768+252, *thePlayer, 20, 80, 40));
    gameWave[2][1].push_back(Monster(&DarkEnt, 1024-354, 768+192, *thePlayer, 20, 80, 40));
    gameWave[2][1].push_back(Monster(&DarkEnt, 1024+586, 768-466, *thePlayer, 20, 80, 40));
    gameWave[2][1].push_back(Monster(&DarkEnt, 1024+702, 768-163, *thePlayer, 20, 80, 40));
    
    gameWave[2][2].push_back(Monster(&DarkBush, 1024/2, 768/2, *thePlayer, 5, 20, 10));
    gameWave[2][2].push_back(Monster(&DarkBush, 1024*1.5, 768/2, *thePlayer, 5, 20, 10));
    gameWave[2][2].push_back(Monster(&DarkBush, 1024*1.5, 768*1.5, *thePlayer, 5, 20, 10));
    gameWave[2][2].push_back(Monster(&DarkBush, 1024*1.75, 768/1.75, *thePlayer, 5, 20, 10));
    gameWave[2][2].push_back(Monster(&DarkBush, 1024/1.75, 768*1.75, *thePlayer, 5, 20, 10));
    gameWave[2][2].push_back(Monster(&Imp, 1024+364, 768-263, *thePlayer, 5, 25, 10));
    gameWave[2][2].push_back(Monster(&Imp, 1024-353, 768+454, *thePlayer, 5, 25, 10));
    gameWave[2][2].push_back(Monster(&Imp, 1024-830, 768-576, *thePlayer, 5, 25, 10));
    gameWave[2][2].push_back(Monster(&Imp, 1024-95, 768+166, *thePlayer, 5, 25, 10));
    gameWave[2][2].push_back(Monster(&Imp, 1024+585, 768+452, *thePlayer, 5, 25, 10));
    gameWave[2][2].push_back(Monster(&DarkEnt, 1024+261, 768+563, *thePlayer, 20, 80, 40));
    gameWave[2][2].push_back(Monster(&DarkEnt, 1024-125, 768+252, *thePlayer, 20, 80, 40));
    gameWave[2][2].push_back(Monster(&DarkEnt, 1024-354, 768+192, *thePlayer, 20, 80, 40));
    gameWave[2][2].push_back(Monster(&DarkEnt, 1024+586, 768-466, *thePlayer, 20, 80, 40));
    gameWave[2][2].push_back(Monster(&DarkEnt, 1024+702, 768-163, *thePlayer, 20, 80, 40));
    
    gameWave[2][3].push_back(Monster(&PosMan, 1024/2, 768/2, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024*1.5, 768/2, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024*1.5, 768*1.5, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024*1.75, 768/1.75, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024/1.75, 768*1.75, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024+364, 768-263, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024-353, 768+454, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024-830, 768-576, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024-95, 768+166, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1024+585, 768+452, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1623, 548, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 165, 348, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1725, 1256, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 674, 725, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 283, 1029, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 473, 329, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 857, 596, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 1029, 397, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 238, 721, *thePlayer, 25, 100, 50));
    gameWave[2][3].push_back(Monster(&PosMan, 380, 1726, *thePlayer, 25, 100, 50));
    
    gameWave[2][4].push_back(Monster(&PosMan, 1024/2, 768/2, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024*1.5, 768/2, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024*1.5, 768*1.5, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024*1.75, 768/1.75, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024/1.75, 768*1.75, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024+364, 768-263, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024-353, 768+454, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024-830, 768-576, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024-95, 768+166, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1024+585, 768+452, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1623, 548, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 165, 348, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1725, 1256, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 674, 725, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 283, 1029, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 473, 329, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 857, 596, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 1029, 397, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 238, 721, *thePlayer, 25, 100, 50));
    gameWave[2][4].push_back(Monster(&PosMan, 380, 1726, *thePlayer, 25, 100, 50));
    
    gameWave[2][5].push_back(Monster(&PosMan, 1024/2, 768/2, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024*1.5, 768/2, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024*1.5, 768*1.5, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024*1.75, 768/1.75, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024/1.75, 768*1.75, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024+364, 768-263, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024-353, 768+454, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024-830, 768-576, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024-95, 768+166, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1024+585, 768+452, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1623, 548, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 165, 348, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1725, 1256, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 674, 725, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 283, 1029, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 473, 329, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 857, 596, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 1029, 397, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 238, 721, *thePlayer, 25, 100, 50));
    gameWave[2][5].push_back(Monster(&PosMan, 380, 1726, *thePlayer, 25, 100, 50));
    
    //snow dimension
    gameWave[3][0].push_back(Monster(&SnowBush, 1024/2, 768/2, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024*1.5, 768/2, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024*1.5, 768*1.5, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024*1.75, 768/1.75, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024/1.75, 768*1.75, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024+364, 768-263, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024-353, 768+454, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024-830, 768-576, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024-95, 768+166, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&SnowBush, 1024+585, 768+452, *thePlayer, 15, 30, 15));
    gameWave[3][0].push_back(Monster(&EvergreenEnt, 1024+261, 768+563, *thePlayer, 25, 70, 40));
    gameWave[3][0].push_back(Monster(&EvergreenEnt, 1024-125, 768+252, *thePlayer, 25, 70, 40));
    gameWave[3][0].push_back(Monster(&EvergreenEnt, 1024-354, 768+192, *thePlayer, 25, 70, 40));
    gameWave[3][0].push_back(Monster(&EvergreenEnt, 1024+586, 768-466, *thePlayer, 25, 70, 40));
    gameWave[3][0].push_back(Monster(&EvergreenEnt, 1024+702, 768-163, *thePlayer, 25, 70, 40));
    
    gameWave[3][1].push_back(Monster(&SnowBush, 1024/2, 768/2, *thePlayer, 15, 30, 15));
    gameWave[3][1].push_back(Monster(&SnowBush, 1024*1.5, 768/2, *thePlayer, 15, 30, 15));
    gameWave[3][1].push_back(Monster(&SnowBush, 1024*1.5, 768*1.5, *thePlayer, 15, 30, 15));
    gameWave[3][1].push_back(Monster(&SnowBush, 1024*1.75, 768/1.75, *thePlayer, 15, 30, 15));
    gameWave[3][1].push_back(Monster(&SnowBush, 1024/1.75, 768*1.75, *thePlayer, 15, 30, 15));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 1024+261, 768+563, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 1024-125, 768+252, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 1024-354, 768+192, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 1024+586, 768-466, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 1024+702, 768-163, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 165, 348, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 1725, 1256, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 674, 725, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 283, 1029, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&EvergreenEnt, 473, 329, *thePlayer, 25, 70, 40));
    gameWave[3][1].push_back(Monster(&SnowMan, 857, 596, *thePlayer, 30, 100, 50));
    gameWave[3][1].push_back(Monster(&SnowMan, 1029, 397, *thePlayer, 30, 100, 50));
    gameWave[3][1].push_back(Monster(&SnowMan, 238, 721, *thePlayer, 30, 100, 50));
    gameWave[3][1].push_back(Monster(&SnowMan, 380, 1726, *thePlayer, 30, 100, 50));
    gameWave[3][1].push_back(Monster(&SnowMan, 1623, 548, *thePlayer, 30, 100, 50));
    
    gameWave[3][2].push_back(Monster(&SnowMan, 1024/2, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024*1.5, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024*1.5, 768*1.5, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024*1.75, 768/1.75, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024/1.75, 768*1.75, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024+261, 768+563, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024-125, 768+252, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024-354, 768+192, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024+586, 768-466, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1024+702, 768-163, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 165, 348, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 1725, 1256, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 674, 725, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 283, 1029, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&SnowMan, 473, 329, *thePlayer, 30, 100, 50));
    gameWave[3][2].push_back(Monster(&EvergreenEnt, 857, 596, *thePlayer, 25, 70, 40));
    gameWave[3][2].push_back(Monster(&EvergreenEnt, 1029, 397, *thePlayer, 25, 70, 40));
    gameWave[3][2].push_back(Monster(&EvergreenEnt, 238, 721, *thePlayer, 25, 70, 40));
    gameWave[3][2].push_back(Monster(&EvergreenEnt, 380, 1726, *thePlayer, 25, 70, 40));
    gameWave[3][2].push_back(Monster(&EvergreenEnt, 1623, 548, *thePlayer, 25, 70, 40));
    
    gameWave[3][3].push_back(Monster(&SnowMan, 1024/2, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024*1.5, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024*1.5, 768*1.5, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024*1.75, 768/1.75, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024/1.75, 768*1.75, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024+261, 768+563, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024-125, 768+252, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024-354, 768+192, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024+586, 768-466, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1024+702, 768-163, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 165, 348, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 1725, 1256, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 674, 725, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 283, 1029, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowMan, 473, 329, *thePlayer, 30, 100, 50));
    gameWave[3][3].push_back(Monster(&SnowWarrior, 857, 596, *thePlayer, 35, 120, 50));
    gameWave[3][3].push_back(Monster(&SnowWarrior, 1029, 397, *thePlayer, 35, 120, 50));
    gameWave[3][3].push_back(Monster(&SnowWarrior, 238, 721, *thePlayer, 35, 120, 50));
    gameWave[3][3].push_back(Monster(&SnowWarrior, 380, 1726, *thePlayer, 35, 120, 50));
    gameWave[3][3].push_back(Monster(&SnowWarrior, 1623, 548, *thePlayer, 35, 120, 50));
    
    gameWave[3][4].push_back(Monster(&SnowMan, 1024/2, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024*1.5, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024*1.5, 768*1.5, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024*1.75, 768/1.75, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024/1.75, 768*1.75, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024+261, 768+563, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024-125, 768+252, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024-354, 768+192, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024+586, 768-466, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1024+702, 768-163, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 165, 348, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 1725, 1256, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 674, 725, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 283, 1029, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowMan, 473, 329, *thePlayer, 30, 100, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 857, 596, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 1029, 397, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 238, 721, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 380, 1726, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 1623, 548, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 981, 158, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 195, 177, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 1192, 495, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 508, 1276, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 485, 213, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 324, 421, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 283, 943, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 592, 1238, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 1239, 836, *thePlayer, 35, 120, 50));
    gameWave[3][4].push_back(Monster(&SnowWarrior, 1769, 239, *thePlayer, 35, 120, 50));
    
    gameWave[3][5].push_back(Monster(&SnowMan, 1024/2, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024*1.5, 768/2, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024*1.5, 768*1.5, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024*1.75, 768/1.75, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024/1.75, 768*1.75, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024+261, 768+563, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024-125, 768+252, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024-354, 768+192, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024+586, 768-466, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1024+702, 768-163, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 165, 348, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 1725, 1256, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 674, 725, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 283, 1029, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowMan, 473, 329, *thePlayer, 30, 100, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 857, 596, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 1029, 397, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 238, 721, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 380, 1726, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 1623, 548, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 981, 158, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 195, 177, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 1192, 495, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 508, 1276, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowWarrior, 485, 213, *thePlayer, 35, 120, 50));
    gameWave[3][5].push_back(Monster(&SnowGolem, 324, 421, *thePlayer, 40, 150, 60));
    gameWave[3][5].push_back(Monster(&SnowGolem, 283, 943, *thePlayer, 40, 150, 60));
    gameWave[3][5].push_back(Monster(&SnowGolem, 592, 1238, *thePlayer, 40, 150, 60));
    gameWave[3][5].push_back(Monster(&SnowGolem, 1239, 836, *thePlayer, 40, 150, 60));
    gameWave[3][5].push_back(Monster(&SnowGolem, 1769, 239, *thePlayer, 40, 150, 60));
    
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024/2, 768/2, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024*1.5, 768/2, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024*1.5, 768*1.5, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024*1.75, 768/1.75, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024/1.75, 768*1.75, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024+261, 768+563, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024-125, 768+252, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024-354, 768+192, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024+586, 768-466, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1024+702, 768-163, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 165, 348, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1725, 1256, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 674, 725, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 283, 1029, *thePlayer, 30, 100, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 473, 329, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 857, 596, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1029, 397, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 238, 721, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 380, 1726, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1623, 548, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 981, 158, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 195, 177, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 1192, 495, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 508, 1276, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowWarrior, 485, 213, *thePlayer, 35, 120, 50));
    gameWave[3][6].push_back(Monster(&SnowGolem, 324, 421, *thePlayer, 40, 150, 60));
    gameWave[3][6].push_back(Monster(&SnowGolem, 283, 943, *thePlayer, 40, 150, 60));
    gameWave[3][6].push_back(Monster(&SnowGolem, 592, 1238, *thePlayer, 40, 150, 60));
    gameWave[3][6].push_back(Monster(&SnowGolem, 1239, 836, *thePlayer, 40, 150, 60));
    gameWave[3][6].push_back(Monster(&SnowGolem, 1769, 239, *thePlayer, 40, 150, 60));
    
    gameWave[3][7].push_back(Monster(&SnowGuardian, 1024/2, 768/2, *thePlayer, 35, 170, 55));
    gameWave[3][7].push_back(Monster(&SnowGuardian, 1024*1.5, 768/2, *thePlayer, 35, 170, 55));
    gameWave[3][7].push_back(Monster(&SnowGuardian, 1024*1.5, 768*1.5, *thePlayer, 35, 170, 55));
    gameWave[3][7].push_back(Monster(&SnowGuardian, 1024*1.75, 768/1.75, *thePlayer, 35, 170, 55));
    gameWave[3][7].push_back(Monster(&SnowGuardian, 1024/1.75, 768*1.75, *thePlayer, 35, 120, 55));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1024+261, 768+563, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1024-125, 768+252, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1024-354, 768+192, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1024+586, 768-466, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1024+702, 768-163, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 165, 348, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1725, 1256, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 674, 725, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 283, 1029, *thePlayer, 30, 100, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 473, 329, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 857, 596, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1029, 397, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 238, 721, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 380, 1726, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowWarrior, 1623, 548, *thePlayer, 35, 120, 50));
    gameWave[3][7].push_back(Monster(&SnowGolem, 981, 158, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 195, 177, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 1192, 495, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 508, 1276, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 485, 213, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 324, 421, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 283, 943, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 592, 1238, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 1239, 836, *thePlayer, 40, 150, 60));
    gameWave[3][7].push_back(Monster(&SnowGolem, 1769, 239, *thePlayer, 40, 150, 60));
    
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024/2, 768/2, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024*1.5, 768/2, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024*1.5, 768*1.5, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024*1.75, 768/1.75, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024/1.75, 768*1.75, *thePlayer, 35, 120, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024+261, 768+563, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024-125, 768+252, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024-354, 768+192, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024+586, 768-466, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowGuardian, 1024+702, 768-163, *thePlayer, 35, 170, 55));
    gameWave[3][8].push_back(Monster(&SnowTitan, 165, 348, *thePlayer, 40, 200, 70));
    gameWave[3][8].push_back(Monster(&SnowTitan, 1725, 1256, *thePlayer, 40, 200, 70));
    gameWave[3][8].push_back(Monster(&SnowTitan, 674, 725, *thePlayer, 40, 200, 70));
    gameWave[3][8].push_back(Monster(&SnowTitan, 283, 1029, *thePlayer, 40, 200, 70));
    gameWave[3][8].push_back(Monster(&SnowTitan, 473, 329, *thePlayer, 40, 200, 70));
    gameWave[3][8].push_back(Monster(&SnowWarrior, 857, 596, *thePlayer, 35, 120, 50));
    gameWave[3][8].push_back(Monster(&SnowWarrior, 1029, 397, *thePlayer, 35, 120, 50));
    gameWave[3][8].push_back(Monster(&SnowWarrior, 238, 721, *thePlayer, 35, 120, 50));
    gameWave[3][8].push_back(Monster(&SnowWarrior, 380, 1726, *thePlayer, 35, 120, 50));
    gameWave[3][8].push_back(Monster(&SnowWarrior, 1623, 548, *thePlayer, 35, 120, 50));
    gameWave[3][8].push_back(Monster(&SnowGolem, 981, 158, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 195, 177, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 1192, 495, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 508, 1276, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 485, 213, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 324, 421, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 283, 943, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 592, 1238, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 1239, 836, *thePlayer, 40, 150, 60));
    gameWave[3][8].push_back(Monster(&SnowGolem, 1769, 239, *thePlayer, 40, 150, 60));
    
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024/2, 768/2, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024*1.5, 768/2, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024*1.5, 768*1.5, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024*1.75, 768/1.75, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024/1.75, 768*1.75, *thePlayer, 35, 120, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024+261, 768+563, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024-125, 768+252, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024-354, 768+192, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024+586, 768-466, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1024+702, 768-163, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 857, 596, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1029, 397, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 238, 721, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 380, 1726, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGuardian, 1623, 548, *thePlayer, 35, 170, 55));
    gameWave[3][9].push_back(Monster(&SnowGolem, 324, 421, *thePlayer, 40, 150, 60));
    gameWave[3][9].push_back(Monster(&SnowGolem, 283, 943, *thePlayer, 40, 150, 60));
    gameWave[3][9].push_back(Monster(&SnowGolem, 592, 1238, *thePlayer, 40, 150, 60));
    gameWave[3][9].push_back(Monster(&SnowGolem, 1239, 836, *thePlayer, 40, 150, 60));
    gameWave[3][9].push_back(Monster(&SnowGolem, 1769, 239, *thePlayer, 40, 150, 60));
    gameWave[3][9].push_back(Monster(&SnowTitan, 165, 348, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 1725, 1256, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 674, 725, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 283, 1029, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 473, 329, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 981, 158, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 195, 177, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 1192, 495, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 508, 1276, *thePlayer, 40, 200, 70));
    gameWave[3][9].push_back(Monster(&SnowTitan, 485, 213, *thePlayer, 40, 200, 70));
    
    //forest part 3
    gameWave[4][0].push_back(Monster(&PosMan, 1024/2, 768/2, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024*1.5, 768/2, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024*1.5, 768*1.5, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024*1.75, 768/1.75, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024/1.75, 768*1.75, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024+364, 768-263, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024-353, 768+454, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024-830, 768-576, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024-95, 768+166, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1024+585, 768+452, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1623, 548, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 165, 348, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1725, 1256, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 674, 725, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 283, 1029, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 473, 329, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 857, 596, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 1029, 397, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 238, 721, *thePlayer, 25, 100, 50));
    gameWave[4][0].push_back(Monster(&PosMan, 380, 1726, *thePlayer, 25, 100, 50));
    
    gameWave[4][1].push_back(Monster(&PosMan, 1024/2, 768/2, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024*1.5, 768/2, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024*1.5, 768*1.5, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024*1.75, 768/1.75, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024/1.75, 768*1.75, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024+364, 768-263, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024-353, 768+454, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024-830, 768-576, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024-95, 768+166, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1024+585, 768+452, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1623, 548, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 165, 348, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1725, 1256, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 674, 725, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 283, 1029, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 473, 329, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 857, 596, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 1029, 397, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 238, 721, *thePlayer, 25, 100, 50));
    gameWave[4][1].push_back(Monster(&PosMan, 380, 1726, *thePlayer, 25, 100, 50));
    
    gameWave[4][2].push_back(Monster(&PosMan, 1024/2, 768/2, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024*1.5, 768/2, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024*1.5, 768*1.5, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024*1.75, 768/1.75, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024/1.75, 768*1.75, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024+364, 768-263, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024-353, 768+454, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024-830, 768-576, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024-95, 768+166, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1024+585, 768+452, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1623, 548, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 165, 348, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1725, 1256, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 674, 725, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 283, 1029, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 473, 329, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 857, 596, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 1029, 397, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 238, 721, *thePlayer, 25, 100, 50));
    gameWave[4][2].push_back(Monster(&PosMan, 380, 1726, *thePlayer, 25, 100, 50));
    
    gameWave[4][3].push_back(Monster(&SkeletonBeast, 1024/2, 768/2, *thePlayer, 30, 100, 55));
    gameWave[4][3].push_back(Monster(&SkeletonBeast, 1024*1.5, 768/2, *thePlayer, 30, 100, 55));
    gameWave[4][3].push_back(Monster(&SkeletonBeast, 1024*1.5, 768*1.5, *thePlayer, 30, 100, 55));
    gameWave[4][3].push_back(Monster(&SkeletonBeast, 1024*1.75, 768/1.75, *thePlayer, 30, 100, 55));
    gameWave[4][3].push_back(Monster(&SkeletonBeast, 1024/1.75, 768*1.75, *thePlayer, 30, 100, 55));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024+364, 768-263, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024-353, 768+454, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024-830, 768-576, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024-95, 768+166, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024+585, 768+452, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024+261, 768+563, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024-125, 768+252, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024-354, 768+192, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024+586, 768-466, *thePlayer, 35, 125, 60));
    gameWave[4][3].push_back(Monster(&SkeletonMan, 1024+702, 768-163, *thePlayer, 35, 125, 60));
    
    gameWave[4][4].push_back(Monster(&SkeletonBeast, 1024/2, 768/2, *thePlayer, 30, 100, 55));
    gameWave[4][4].push_back(Monster(&SkeletonBeast, 1024*1.5, 768/2, *thePlayer, 30, 100, 55));
    gameWave[4][4].push_back(Monster(&SkeletonBeast, 1024*1.5, 768*1.5, *thePlayer, 30, 100, 55));
    gameWave[4][4].push_back(Monster(&SkeletonBeast, 1024*1.75, 768/1.75, *thePlayer, 30, 100, 55));
    gameWave[4][4].push_back(Monster(&SkeletonBeast, 1024/1.75, 768*1.75, *thePlayer, 30, 100, 55));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024+364, 768-263, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024-353, 768+454, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024-830, 768-576, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024-95, 768+166, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024+585, 768+452, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024+261, 768+563, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024-125, 768+252, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024-354, 768+192, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024+586, 768-466, *thePlayer, 35, 125, 60));
    gameWave[4][4].push_back(Monster(&SkeletonMan, 1024+702, 768-163, *thePlayer, 35, 125, 60));
    
    //desert dimension
    gameWave[5][0].push_back(Monster(&CactusMan, 1024/2, 768/2, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024*1.5, 768/2, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024*1.5, 768*1.5, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024*1.75, 768/1.75, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024/1.75, 768*1.75, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024+364, 768-263, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024-353, 768+454, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024-830, 768-576, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024-95, 768+166, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024+585, 768+452, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024+261, 768+563, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024-125, 768+252, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024-354, 768+192, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024+586, 768-466, *thePlayer, 25, 40, 30));
    gameWave[5][0].push_back(Monster(&CactusMan, 1024+702, 768-163, *thePlayer, 25, 40, 30));
    
    gameWave[5][1].push_back(Monster(&CactusMan, 1024/2, 768/2, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024*1.5, 768/2, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024*1.5, 768*1.5, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024*1.75, 768/1.75, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024/1.75, 768*1.75, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024+364, 768-263, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024-353, 768+454, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024-830, 768-576, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024-95, 768+166, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&CactusMan, 1024+585, 768+452, *thePlayer, 25, 40, 30));
    gameWave[5][1].push_back(Monster(&Scorpion, 1024+261, 768+563, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 1024-125, 768+252, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 1024-354, 768+192, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 1024+586, 768-466, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 1024+702, 768-163, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 473, 329, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 857, 596, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 1029, 397, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 238, 721, *thePlayer, 35, 75, 45));
    gameWave[5][1].push_back(Monster(&Scorpion, 380, 1726, *thePlayer, 35, 75, 45));
    
    gameWave[5][2].push_back(Monster(&CactusMan, 1024/2, 768/2, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024*1.5, 768/2, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024*1.5, 768*1.5, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024*1.75, 768/1.75, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024/1.75, 768*1.75, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024+364, 768-263, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024-353, 768+454, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024-830, 768-576, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024-95, 768+166, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&CactusMan, 1024+585, 768+452, *thePlayer, 25, 40, 30));
    gameWave[5][2].push_back(Monster(&Scorpion, 1024+261, 768+563, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 1024-125, 768+252, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 1024-354, 768+192, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 1024+586, 768-466, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 1024+702, 768-163, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 473, 329, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 857, 596, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 1029, 397, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 238, 721, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&Scorpion, 380, 1726, *thePlayer, 35, 75, 45));
    gameWave[5][2].push_back(Monster(&LizardMan, 981, 158, *thePlayer, 45, 90, 55));
    gameWave[5][2].push_back(Monster(&LizardMan, 195, 177, *thePlayer, 45, 90, 55));
    gameWave[5][2].push_back(Monster(&LizardMan, 1192, 495, *thePlayer, 45, 90, 55));
    gameWave[5][2].push_back(Monster(&LizardMan, 508, 1276, *thePlayer, 45, 90, 55));
    gameWave[5][2].push_back(Monster(&LizardMan, 485, 213, *thePlayer, 45, 90, 55));
    
    gameWave[5][3].push_back(Monster(&Scorpion, 1024+261, 768+563, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 1024-125, 768+252, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 1024-354, 768+192, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 1024+586, 768-466, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 1024+702, 768-163, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 473, 329, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 857, 596, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 1029, 397, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 238, 721, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&Scorpion, 380, 1726, *thePlayer, 35, 75, 45));
    gameWave[5][3].push_back(Monster(&LizardMan, 981, 158, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 195, 177, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 1192, 495, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 508, 1276, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 485, 213, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 1024/2, 768/2, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 1024*1.5, 768/2, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 1024*1.5, 768*1.5, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 1024*1.75, 768/1.75, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&LizardMan, 1024/1.75, 768*1.75, *thePlayer, 45, 90, 55));
    gameWave[5][3].push_back(Monster(&BandedBeast, 1024+364, 768-263, *thePlayer, 45, 175, 80));
    gameWave[5][3].push_back(Monster(&BandedBeast, 1024-353, 768+454, *thePlayer, 45, 175, 80));
    gameWave[5][3].push_back(Monster(&BandedBeast, 1024-830, 768-576, *thePlayer, 45, 175, 80));
    gameWave[5][3].push_back(Monster(&BandedBeast, 1024-95, 768+166, *thePlayer, 45, 175, 80));
    gameWave[5][3].push_back(Monster(&BandedBeast, 1024+585, 768+452, *thePlayer, 45, 175, 80));
    
    gameWave[5][4].push_back(Monster(&Scorpion, 1024+261, 768+563, *thePlayer, 35, 75, 45));
    gameWave[5][4].push_back(Monster(&Scorpion, 1024-125, 768+252, *thePlayer, 35, 75, 45));
    gameWave[5][4].push_back(Monster(&Scorpion, 1024-354, 768+192, *thePlayer, 35, 75, 45));
    gameWave[5][4].push_back(Monster(&Scorpion, 1024+586, 768-466, *thePlayer, 35, 75, 45));
    gameWave[5][4].push_back(Monster(&Scorpion, 1024+702, 768-163, *thePlayer, 35, 75, 45));
    gameWave[5][4].push_back(Monster(&LizardMan, 473, 329, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 857, 596, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 1029, 397, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 238, 721, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 380, 1726, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 981, 158, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 195, 177, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 1192, 495, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 508, 1276, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 485, 213, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 1024/2, 768/2, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 1024*1.5, 768/2, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 1024*1.5, 768*1.5, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 1024*1.75, 768/1.75, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&LizardMan, 1024/1.75, 768*1.75, *thePlayer, 45, 90, 55));
    gameWave[5][4].push_back(Monster(&BandedBeast, 1024+364, 768-263, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 1024-353, 768+454, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 1024-830, 768-576, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 1024-95, 768+166, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 1024+585, 768+452, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 473, 519, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 827, 596, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 1129, 597, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 478, 731, *thePlayer, 45, 175, 80));
    gameWave[5][4].push_back(Monster(&BandedBeast, 318, 791, *thePlayer, 45, 175, 80));
    
    gameWave[5][5].push_back(Monster(&SwoBandit, 1024+261, 768+563, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 1024-125, 768+252, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 1024-354, 768+192, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 1024+586, 768-466, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 1024+702, 768-163, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 473, 329, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 857, 596, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 1029, 397, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 238, 721, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 380, 1726, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 981, 158, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 195, 177, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 1192, 495, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 508, 1276, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&SwoBandit, 485, 213, *thePlayer, 45, 110, 55));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024/2, 768/2, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024*1.5, 768/2, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024*1.5, 768*1.5, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024*1.75, 768/1.75, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024/1.75, 768*1.75, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024+364, 768-263, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024-353, 768+454, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024-830, 768-576, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024-95, 768+166, *thePlayer, 50, 110, 60));
    gameWave[5][5].push_back(Monster(&HalBandit, 1024+585, 768+452, *thePlayer, 50, 110, 60));
    
    gameWave[5][6].push_back(Monster(&BandedBeast, 473, 519, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 827, 596, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 1129, 597, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 478, 731, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 318, 791, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 1024+261, 768+563, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 1024-125, 768+252, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 1024-354, 768+192, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 1024+586, 768-466, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&BandedBeast, 1024+702, 768-163, *thePlayer, 45, 175, 80));
    gameWave[5][6].push_back(Monster(&SwoBandit, 473, 329, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 857, 596, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 1029, 397, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 238, 721, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 380, 1726, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 981, 158, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 195, 177, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 1192, 495, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 508, 1276, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&SwoBandit, 485, 213, *thePlayer, 45, 110, 55));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024/2, 768/2, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024*1.5, 768/2, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024*1.5, 768*1.5, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024*1.75, 768/1.75, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024/1.75, 768*1.75, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024+364, 768-263, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024-353, 768+454, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024-830, 768-576, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024-95, 768+166, *thePlayer, 50, 110, 60));
    gameWave[5][6].push_back(Monster(&HalBandit, 1024+585, 768+452, *thePlayer, 50, 110, 60));
    
    gameWave[5][7].push_back(Monster(&Mummy, 473, 329, *thePlayer, 50, 175, 85));
    gameWave[5][7].push_back(Monster(&Mummy, 857, 596, *thePlayer, 50, 175, 85));
    gameWave[5][7].push_back(Monster(&Mummy, 1029, 397, *thePlayer, 50, 175, 85));
    gameWave[5][7].push_back(Monster(&Mummy, 238, 721, *thePlayer, 50, 175, 85));
    gameWave[5][7].push_back(Monster(&Mummy, 380, 1726, *thePlayer, 50, 175, 85));
    gameWave[5][7].push_back(Monster(&HalBandit, 981, 158, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 195, 177, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1192, 495, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 508, 1276, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 485, 213, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024/2, 768/2, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024*1.5, 768/2, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024*1.5, 768*1.5, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024*1.75, 768/1.75, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024/1.75, 768*1.75, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024+364, 768-263, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024-353, 768+454, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024-830, 768-576, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024-95, 768+166, *thePlayer, 50, 110, 60));
    gameWave[5][7].push_back(Monster(&HalBandit, 1024+585, 768+452, *thePlayer, 50, 110, 60));
    
    gameWave[5][8].push_back(Monster(&PSwoBandit, 473, 329, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 857, 596, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 1029, 397, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 238, 721, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 380, 1726, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 981, 158, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 195, 177, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 1192, 495, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 508, 1276, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&PSwoBandit, 485, 213, *thePlayer, 50, 250, 95));
    gameWave[5][8].push_back(Monster(&Mummy, 473, 519, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 827, 596, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1129, 597, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 478, 731, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 318, 791, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024+261, 768+563, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024-125, 768+252, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024-354, 768+192, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024+586, 768-466, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024+702, 768-163, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024/2, 768/2, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024*1.5, 768/2, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024*1.5, 768*1.5, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024*1.75, 768/1.75, *thePlayer, 50, 175, 85));
    gameWave[5][8].push_back(Monster(&Mummy, 1024/1.75, 768*1.75, *thePlayer, 50, 175, 85));
    
    gameWave[5][9].push_back(Monster(&PSwoBandit, 473, 329, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 857, 596, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1029, 397, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 238, 721, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 380, 1726, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 981, 158, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 195, 177, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1192, 495, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 508, 1276, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 485, 213, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 473, 519, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 827, 596, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1129, 597, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 478, 731, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 318, 791, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1024+261, 768+563, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1024-125, 768+252, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1024-354, 768+192, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1024+586, 768-466, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PSwoBandit, 1024+702, 768-163, *thePlayer, 50, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024/2, 768/2, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024*1.5, 768/2, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024*1.5, 768*1.5, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024*1.75, 768/1.75, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024/1.75, 768*1.75, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024+261, 768+563, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024-125, 768+252, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024-354, 768+192, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024+586, 768-466, *thePlayer, 55, 250, 95));
    gameWave[5][9].push_back(Monster(&PHalBandit, 1024+702, 768-163, *thePlayer, 55, 250, 95));
}

sf::Sprite MonsterSpawner::getBackground()
{
    return backgrounds[waveTypeIterator];
}

void MonsterSpawner::copyToVec (std::vector<Monster>& monsterArray)
{
    monsterArray = gameWave[waveTypeIterator][wavePartIterator];
}

std::vector<Obstacle> MonsterSpawner::getObstacleArray()
{
    return obstacles[waveTypeIterator];
}

void MonsterSpawner::update()
{
    wavePartIterator++;
    if (wavePartIterator > 3 && waveTypeIterator == 0)
    {
        wavePartIterator = 0;
        waveTypeIterator++;
        changeSound.play();
    }
    else if (wavePartIterator > 9 && waveTypeIterator == 1)
    {
        wavePartIterator = 0;
        waveTypeIterator++;
        changeSound.play();
    }
    else if (wavePartIterator > 5 && waveTypeIterator == 2)
    {
        wavePartIterator = 0;
        waveTypeIterator++;
        changeSound.play();
    }
    else if (wavePartIterator > 9 && waveTypeIterator == 3)
    {
        wavePartIterator = 0;
        waveTypeIterator++;
        changeSound.play();
    }
    else if (wavePartIterator > 4 && waveTypeIterator == 4)
    {
        wavePartIterator  = 0;
        waveTypeIterator++;
        changeSound.play();
    }
    else if (wavePartIterator > 9 && waveTypeIterator == 5)
    {
        wavePartIterator = 9;
        waveTypeIterator = 5;
    }
}

int MonsterSpawner::getTypeIterator()
{
    return waveTypeIterator;
}

int MonsterSpawner::getPartIterator()
{
    return wavePartIterator;
}