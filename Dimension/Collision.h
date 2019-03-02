//
//  Collision.h
//  Dimension
//
//  Created by 17xiangyangt on 1/3/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__Collision__
#define __Dimension__Collision__

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Collision
{
    bool PixelPerfectTest (const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);
    /* Uses AlphaLimit to test for collisions between the two sf::Sprite objects
     * Supports scaling and rotation
     * AlphaLimit: The threshold at which a pixel becomes "solid"
     * e.g. If a pixel's AlphaLimit value is 127, a pixel with an AlphaLimit value of 128 will cause a collision, whereas a pixel with AlphaLimit 126 will not.
     */
    
    bool CreateTextureAndBitmask (sf::Texture &LoadInto, const std::string& fileName);
    /* replaces sf::Texture.loadFromFile(). Loads a texture from the file and creates a bitmask for it,
     * much faster than downloading an image from the graphics card, as loadFromFile would do, then creating
     * a bitmask for it.
     */
    
    bool CircleTest (const sf::Sprite& Object1, const sf::Sprite& Object2); //test for collisions within the circular boundaries of the sprite
    
    bool BoundingBoxTest (const sf::Sprite& Object1, const sf::Sprite& Object2); //test for collisions within the rectangular bounding box of the sprite
}

#endif /* defined(__Dimension__Collision__) */
