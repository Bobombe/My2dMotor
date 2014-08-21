#include "concretebackground.h"
#include "moteur2d.h"

ConcreteBackground::ConcreteBackground(const std::string& imagePath)
{
    //ctor
    m_sprite = 0;
    if (imagePath!="")
    {
        m_sprite = new sf::Sprite;
        m_sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
        m_image = m_sprite->getTexture()->copyToImage();
    }
    Moteur2D::getInstance()->addConcreteBackground(this);
}

ConcreteBackground::~ConcreteBackground()
{
    //dtor
    if (m_sprite)
        delete m_sprite;
}

bool ConcreteBackground::collidedBy(AnimatedObject * ao, const sf::Vector2f & newObjectPos)
{
    if (!m_sprite)
        return false;

    sf::Vector2f posUL = newObjectPos-m_sprite->getPosition();
    sf::Vector2f posDR = posUL;
    posDR.x+=ao->getBox().width;
    posDR.y+=ao->getBox().height;

    // Si hors du background
    if (posDR.x<0 || posDR.y <0 || posUL.x>m_sprite->getGlobalBounds().width || posUL.y>m_sprite->getGlobalBounds().height)
    {
        return false;
    }
    //Si Point Haut/gauche trop en haut/gauche
    if (posUL.x<0)
    {
        posUL.x=0;
    }
    if (posUL.y<0)
    {
        posUL.y=0;
    }

    //Si Point Bas/droite trop en Bas/droite
    if (posDR.x>m_sprite->getGlobalBounds().width)
    {
        posDR.x=m_sprite->getGlobalBounds().width;
    }
    if (posDR.y>m_sprite->getGlobalBounds().height)
    {
        posDR.y=m_sprite->getGlobalBounds().height;
    }

    for (int i = posUL.x; i <posDR.x; i++)
    {
        for (int j = posUL.y; j <posDR.y; j++)
        {
            if (m_image.getPixel(i, j).a>128)
                return true;//collision
        }
    }
    return false;

}

void ConcreteBackground::setImage(const std::string& imagePath)
{
    if (!m_sprite)
        m_sprite = new sf::Sprite;
    m_sprite->setTexture(*Moteur2D::getInstance()->getTexture(imagePath));
    m_image = m_sprite->getTexture()->copyToImage();
}



