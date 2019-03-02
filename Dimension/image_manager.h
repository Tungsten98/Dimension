//
//  image_manager.h
//  Dimension
//
//  Created by 17xiangyangt on 1/2/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __Dimension__image_manager__
#define __Dimension__image_manager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class image_manager
{
public:
    image_manager();
    ~image_manager(); // constructor and destructor
    
private:
    image_manager(const image_manager&);
    image_manager& operator = (const image_manager&); // private copy constructor and assignment operator prevents duplicates of image manager
    
public:
    const sf::Texture& getTexture (const std::string& filename); // Loads the desired texture
    void addResoruceDirectories (const std::string& directory);
    
private:
    std::map <std::string, sf::Texture> textures_; // maps image files with string keys
    std::vector<std::string> resourceDirectories;
};

#endif /* defined(__Dimension__image_manager__) */
