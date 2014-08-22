#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <SFML/Graphics.hpp>
#include "updatable.h"
#include "fixedobject.h"

// La vitesse n'est pas inclu dans les drawable contrairement à la position,
// donc on l'implémente ici.
// Cette classe reste abstraite en incluant fixed object
class AnimatedObject : public Updatable, virtual public FixedObject
{
    public:
        AnimatedObject(sf::Vector2f vit = sf::Vector2f(0, 0));
        virtual ~AnimatedObject();


        // GETTERS
        virtual const sf::Vector2f& getVitesse()
        {
            return m_vit;
        }

        // SETTERS
        virtual void setVitesse(const sf::Vector2f& v)
        {
            m_vit.x= v.x;
            m_vit.y = v.y;
        }

        virtual void update(float seconds);
    protected:

        virtual void checkCollision(float seconds);
        virtual bool collideWith(const sf::FloatRect &other, const sf::Vector2f & newPos);
        virtual bool collideWith(FixedObject * fo);

        sf::Vector2f m_vit;
    private:
};

#endif // ANIMATEDOBJECT_H
