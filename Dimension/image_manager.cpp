//
//  image_manager.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/2/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "image_manager.h"
#include <iterator>

image_manager::image_manager() : textures_(), resourceDirectories(){};

image_manager::~image_manager() // destructor, clear all contents to avoid memory leak
{
    textures_.clear();
    resourceDirectories.clear();
}

const sf::Texture& image_manager::getTexture(const std::string& filename)
{
    //check whether the image already exists
    for (std::map <std::string, sf::Texture>::const_iterator iter = textures_.begin();
         iter != textures_.end();
         ++iter)
    {
        if (filename == iter->first)
        {
            return iter->second;
        }
    }
    
    //if the texture does not exist in the map yet, create one to use
    sf::Texture texture;
    
    if (texture.loadFromFile(filename))
    {
        textures_[filename] = texture;
        return textures_[filename];
    }
    
    //The texture has yet to be found, search in other registered directories
    for (std::vector<std::string>::iterator iter = resourceDirectories.begin();
        iter != resourceDirectories.end();
        ++iter)
    {
        if (texture.loadFromFile((*iter) + filename))
        {
            textures_[filename] = texture;
            return textures_[filename];
        }
    }
    
    //Else, print a blank image (return breaks out of function)
    textures_[filename] = texture;
    return textures_[filename];
}

void image_manager::addResoruceDirectories(const std::string& directory)
{
    //check whether the path already exists
    for (std::vector<std::string>::iterator iter = resourceDirectories.begin();
         iter != resourceDirectories.end();
         ++iter)
    {
        if (directory == (*iter)) // if the parameter string matches the string literal stored in 'iter'
        {
            return;
        }
        
        //insert the directory
        resourceDirectories.push_back(directory);
    }
}