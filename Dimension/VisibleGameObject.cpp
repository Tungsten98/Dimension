//
//  VisibleGameObject.cpp
//  Dimension
//
//  Created by 17xiangyangt on 2/1/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject(){}

VisibleGameObject::~VisibleGameObject(){}

void VisibleGameObject::Draw(sf::RenderWindow& window)
{
    window.draw(m_Sprite);
}

sf::Sprite VisibleGameObject::getSprite()
{
    return m_Sprite;
}