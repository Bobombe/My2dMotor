#include "animatedobject.h"
#include "moteur2d.h"
#include <iostream>

AnimatedObject::AnimatedObject(sf::Vector2f vit)
{
    //ctor
    m_vit = vit;
    Moteur2D::getInstance()->addAnimatedObject(this);
}

AnimatedObject::~AnimatedObject()
{
    //dtor
    Moteur2D::getInstance()->deleteAnimatedObject(this);
}
//*
void AnimatedObject::update(float seconds)
{
    if (true)//m_isCollidable)
    {
        //setPosition(checkCollision(seconds));
        checkCollision(seconds);
    }
    else
    {
        setPosition(getPosition()+m_vit*seconds);
    }
}


//sf::Vector2f
void AnimatedObject::checkCollision(float seconds)
{

    // Calcule la nouvelle position sans collision
    sf::Vector2f newPos = this->getPosition()+m_vit*seconds;

    // Pour chaque objets
    // Collisions avec les objets fixes
    std::vector <FixedObject*> fos = Moteur2D::getInstance()->getFixedObjects();
    for (unsigned int i = 0; i<fos.size(); i++)
    {
        FixedObject* fo = fos.at(i);
        if ((*fo)!=(*this) /*&& fo->isCollidable()*/ && collideWith(fo->getBox(), newPos))
        {
            // On traite la collision
            m_vit.x=0;
            m_vit.y=0;
            return ;
        }

    }
    // Collisions avec les objets mouvants.
    std::vector <AnimatedObject*> aos = Moteur2D::getInstance()->getAnimatedObjects();
    for (unsigned int i = 0; i<aos.size(); i++)
    {
        AnimatedObject* ao = aos.at(i);
        if ((*ao)!=(*this) && /*ao->isCollidable() &&*/ collideWith(ao->getBox(), newPos))
        {
            // On traite la collision
            m_vit.x=0;
            m_vit.y=0;
            return;
        }
    }
    // Collisions avec les arrière plans concrets.
    std::vector <ConcreteBackground*> cbs = Moteur2D::getInstance()->getConcreteBackgrounds();
    for (unsigned int i = 0; i<cbs.size(); i++)
    {
        ConcreteBackground* cb = cbs.at(i);
        if (cb->collidedBy(this, newPos))
        {
            // On traite la collision
            m_vit.x=0;
            m_vit.y=0;
            return;
        }
    }
    setPosition( newPos);
}

bool AnimatedObject::collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos)
{
    sf::FloatRect r = getBox();
    sf::Vector2f p = getPosition();

    float left1 = newPos.x-p.x+r.left;
    float top1 = newPos.y-p.y+r.top;
    float right1 = left1+r.width;
    float bottom1 = top1+r.height;

    float bottom2 = other.top+other.height;
    float right2 = other.left+other.width;


    return ! (
    (bottom1 < other.top) ||
    (top1 > bottom2) ||
    (left1 > right2) ||
    (right1 < other.left) );

}

//*/










