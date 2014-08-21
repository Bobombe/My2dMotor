#include "fixedsprite.h"
#include "moteur2d.h"

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
}

sf::Vector2f FixedSprite::getPosition()
{
    sSprite
    return s.getPosition();
}





