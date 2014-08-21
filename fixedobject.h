#ifndef FIXEDOBJECT_H
#define FIXEDOBJECT_H
#include "SFML/Graphics.hpp"


// Les objets dessinables (sprite, shape ...) implémentent leur position,
// cette classe n'est donc qu'une interface pour accéder aux positions
class FixedObject
{
    public:
        //*
        FixedObject();
        virtual ~FixedObject();

        virtual void setPosition(const sf::Vector2f &pos) = 0;
        virtual sf::Vector2f getPosition() = 0;
        virtual sf::FloatRect getBox()
        {
            m_bBox.left=getPosition().x;
            m_bBox.top=getPosition().y;
            return m_bBox;
        }

        bool operator !=(const FixedObject &b) const
        {
            return b.m_indexOfDO != m_indexOfDO;
        }

    protected:

        int m_indexOfDO;
        sf::FloatRect m_bBox;
        sf::Drawable *m_drawableObject;

    private:
};

#endif // FIXEDOBJECT_H
