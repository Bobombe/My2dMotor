#ifndef FIXEDSPRITE_H
#define FIXEDSPRITE_H

#include <SFML/Graphics.hpp>
#include "fixedobject.h"
#include "iostream"

class FixedSprite : virtual public FixedObject
{
    public:
        FixedSprite();
        FixedSprite(const std::string& imagePath);
        FixedSprite(const sf::Vector2f& pos, const std::string& imagePath = "");
        virtual ~FixedSprite();

        //SETTERS
        void setSprite(const std::string& imagePath);
        virtual void setPosition(const sf::Vector2f &pos);
        void setRotation(float degree);

        virtual bool isCollidablePoint(sf::Vector2f pointInGlobalCoordinate);

        //GETTERS
        virtual sf::Vector2f getPosition();
        //virtual sf::FloatRect getBox();
    protected:
        //sf::Sprite * m_sprite;
        sf::Image m_image;
    private:
};

#endif // FIXEDSPRITE_H
