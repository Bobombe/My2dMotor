#include "fixedsprite.h"
#include "moteur2d.h"
#include <typeinfo>

#define sSprite sf::Sprite& s = dynamic_cast<sf::Sprite&>(*m_drawableObject);

FixedSprite::FixedSprite()
{
    //ctor
}

FixedSprite::FixedSprite(const std::string& imagePath)
{
    //ctor
    if (imagePath != "")
        setSprite(imagePath);
    setPosition(sf::Vector2f(0, 0));
}

FixedSprite::FixedSprite(const sf::Vector2f& pos, const std::string& imagePath)
{
    //ctor
    if (imagePath != "")
        setSprite(imagePath);
    setPosition(pos);
}

FixedSprite::~FixedSprite()
{
    //dtor
}

void FixedSprite::setSprite(const std::string& imagePath)
{
    //m_drawableObject = Moteur2D::getInstance()->addSprite(imagePath);

    sf::Sprite *sprite = new sf::Sprite;
    sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
    m_bBox = sprite->getGlobalBounds();
    m_drawableObject = sprite;
    m_indexOfDO = Moteur2D::getInstance()->addDrawable(m_drawableObject);

    m_image = sprite->getTexture()->copyToImage();

}
/*
sf::FloatRect FixedSprite::getBox()
{
    if (m_drawableObject)
    {
        sSprite
        sf::FloatRect ret = s.getGlobalBounds();

        return ret;
    }

    return sf::FloatRect(0, 0, 0, 0);
}
//*/
void FixedSprite::setPosition(const sf::Vector2f &pos)
{
    sSprite
    s.setPosition(pos);
    m_bBox = s.getGlobalBounds();
}


void FixedSprite::setRotation(float degree)
{
    try
    {
        sf::Sprite& c = dynamic_cast<sf::Sprite&>(*m_drawableObject);
        c.setRotation(degree);
        m_bBox = c.getGlobalBounds();
    }
    catch (const std::bad_cast& e)
    {
        std::cerr << e.what() << std::endl;
    }
}


sf::Vector2f FixedSprite::getPosition()
{
    sSprite
    return s.getPosition();
}

bool FixedSprite::isCollidablePoint(sf::Vector2f pointInGlobalCoordinate)
{

    try
    {
        sf::Sprite& sprite = dynamic_cast<sf::Sprite&>(*m_drawableObject);

        pointInGlobalCoordinate=sprite.getTransform().getInverse().transformPoint(pointInGlobalCoordinate);
        if(pointInGlobalCoordinate.x>0 && pointInGlobalCoordinate.y>0&&
           pointInGlobalCoordinate.x<m_image.getSize().x && pointInGlobalCoordinate.y<m_image.getSize().y)
        {
            return (m_image.getPixel(pointInGlobalCoordinate.x, pointInGlobalCoordinate.y).a)>128;
        }
        return false;
    }
    catch (const std::bad_cast& e)
    {
        //std::cerr << e.what() << std::endl;
        return false;
    }

}




