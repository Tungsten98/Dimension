//
//  Collision.cpp
//  Dimension
//
//  Created by 17xiangyangt on 1/3/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Collision.h"
#include <map>

namespace Collision
{
    class BitMaskManager
    {
    private:
        std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
        
    public:
        ~BitMaskManager() //destructor clears the manager's memory
        {
            std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
            for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin();
                 iter != end; ++iter)
            {
                delete [] iter->second;
            }
        }
        
        sf::Uint8 GetPixel (const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y)
        {
            if (x>tex->getSize().x || y>tex->getSize().y)
            {
                return 0;
            }
            else
            {
                return mask [x+y*tex->getSize().x];
            }
        }
        
        sf::Uint8* GetMask (const sf::Texture* tex)
        {
            sf::Uint8* mask;
            std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
            if (pair == Bitmasks.end())
            {
                sf::Image img = tex->copyToImage();
                mask = CreateMask (tex, img);
            }
            else
            {
                mask = pair->second;
            }
            
            return mask;
        }
        
        sf::Uint8* CreateMask (const sf::Texture* tex, const sf::Image& img)
        {
            sf::Uint8* mask = new sf::Uint8 [tex->getSize().y*tex->getSize().x]; // request new space from the free store, equal to the area of the texture
            
            for (unsigned int y = 0; y < tex->getSize().y; y++)
            {
                for (unsigned int x = 0; x < tex->getSize().x; x++)
                {
                    mask[x+y*tex->getSize().x] = img.getPixel(x, y).a;
                }
            }
            
            Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex, mask));
            return mask;
        }
    };//declaration and implementation of private class
    
    BitMaskManager Bitmasks;
    
    bool PixelPerfectTest (const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit)
    {
        sf::FloatRect intersection;
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), intersection)) //if the two objects' boundaries intersect
        {
            sf::IntRect SubRect1 = Object1.getTextureRect();
            sf::IntRect SubRect2 = Object2.getTextureRect();
            
            sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
            sf::Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());
            
            //Loop through the pixels
            for (int i = intersection.left; i < intersection.left+intersection.width; i++)
            {
                for (int j = intersection.top; j < intersection.top+intersection.height; j++)
                {
                    sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
                    sf::Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);
                    
                    //make sure all sprites fall within the texture rectangle
                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < SubRect1.width && o1v.y < SubRect1.height &&
                        o2v.x < SubRect2.width && o2v.y < SubRect2.height)
                    {
                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x)+SubRect1.left, (int)(o1v.y)+SubRect1.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x)+SubRect2.left, (int)(o2v.y)+SubRect2.top) > AlphaLimit) //(int)(variable to cast) is a casting (explicit type changing) technique, for maximum code security, don't rely on casting
                            {
                                return true;
                            }
                    }
                }
            }
        }
        return false;
    }
    
    bool CreateTextureAndBitmask (sf::Texture &LoadInto, const std::string& fileName)
    {
        sf::Image img;
        if (!img.loadFromFile(fileName))
        {
            return false;
        }
        if (!LoadInto.loadFromImage(img))
        {
            return false;
        }
        
        Bitmasks.CreateMask(&LoadInto, img);
        return true;
    }
    
    //private functions used to find sprite's center and size (for CircleTest() function)
    sf::Vector2f GetSpriteCenter (const sf::Sprite& object)
    {
        sf::FloatRect AABB = object.getLocalBounds(); //get the object's local (ignores applied transformations) boundaries
        return sf::Vector2f (AABB.left + AABB.width/2.f, AABB.top + AABB.height/2.f);
    }
    
    sf::Vector2f GetSpriteSize (const sf::Sprite& object)
    {
        sf::IntRect OriginalSize = object.getTextureRect();
        sf::Vector2f scale = object.getScale();
        return sf::Vector2f (OriginalSize.width*scale.x, OriginalSize.height*scale.y);
    }
    
    bool CircleTest (const sf::Sprite& Object1, const sf::Sprite& Object2)
    {
        sf::Vector2f Obj1Size = GetSpriteSize(Object1);
        sf::Vector2f Obj2Size = GetSpriteSize(Object2);
        
        float Radius1 = (Obj1Size.x + Obj1Size.y)/4;
        float Radius2 = (Obj2Size.x + Obj2Size.y)/4; //Using d = 2r theory, by adding both diameters together, one must divide the result by 4 to get the radius for that circle
        
        sf::Vector2f Distance = GetSpriteCenter(Object1)-GetSpriteCenter(Object2);
        
        return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2)); // applying Pythagoras's theorem to calculate the difference between the two sprite's centers, and returns true if it is less than or equal to the length of the two radii combined
    }
    
    class OrientedBoundingBox // private class used in the Bounding box test
    {
    public:
        OrientedBoundingBox (const sf::Sprite& Object) // calculate the four points of the bounding box from a transformed (scaled, rotated, etc.) sprite object
        {
            sf::Transform trans = Object.getTransform();
            sf::IntRect local = Object.getTextureRect();
            //Establish an array of points
            Points[0] = trans.transformPoint(0.f, 0.f);
            Points[1] = trans.transformPoint(local.width, 0.f);
            Points[2] = trans.transformPoint(local.width, local.height);
            Points[3] = trans.transformPoint(0.f, local.height);
        }
        
        sf::Vector2f Points[4]; //initializing from after constructor also works
        
        void ProjectOntoAxis(const sf::Vector2f& Axis, float& min, float& max) // project all four points of the bounding box onto the given axis and return the dot products of the two outermost points
        {
            min = (Points[0].x*Axis.x + Points[0].y*Axis.y);
            max = min;
            for (int j = 1; j < 4; j++)
            {
                float Projection = (Points[j].x*Axis.x + Points[j].y*Axis.y);
                if (Projection < min)
                {
                    min = Projection;
                }
                if (Projection > max)
                {
                    max = Projection;
                }
            }
        }
    };
    
    bool BoundingBoxTest (const sf::Sprite& Object1, const sf::Sprite& Object2)
    {
        OrientedBoundingBox OBB1 (Object1);
        OrientedBoundingBox OBB2 (Object2);
        
        // create the four distinct axes that are perpendicular to the edges of the two rectangles
        sf::Vector2f Axes[4] =
        {
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[0].x,
                          OBB1.Points[1].y-OBB1.Points[0].y),
            
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[2].x,
                          OBB1.Points[1].y-OBB1.Points[2].y),
            
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[3].x,
                          OBB2.Points[0].y-OBB2.Points[3].y),
            
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[1].x,
                          OBB2.Points[0].y-OBB2.Points[1].y)
        };
        
        for (int i = 0; i < 4; i++) // for each axis:
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;
            
            //project the points of both bounding boxes onto the axis,
            OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
            OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);
            
            // and check whether the outermost projected points of both OBBs overlap.
            // If this is not the case, the Seperating Axis Theorem states that there can be no collision between the rectangles
            
            if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
            {
                return false;
            }
        }
        
        return true;
    }
}