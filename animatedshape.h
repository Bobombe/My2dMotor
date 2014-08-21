#ifndef ANIMATEDSHAPE_H
#define ANIMATEDSHAPE_H

#include "fixedshape.h"
#include "animatedobject.h"

class AnimatedShape : public FixedShape, public  AnimatedObject
{
    public:
        // Constructeur par d�faut cr�e un cercle (forme diff�rente pouvant etre pr�cis�e)
        AnimatedShape(ShapeType shapeType = CIRCLE, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f vit = sf::Vector2f(0, 0));
        // Constructeur cr�ant un cercle de rayon radius
        AnimatedShape(float radius, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f vit = sf::Vector2f(0, 0));
        // Constructeur cr�ant un rectangle de taille size
        AnimatedShape(sf::Vector2f size, sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f vit = sf::Vector2f(0, 0));
        virtual ~AnimatedShape();
    protected:
    private:
};

#endif // ANIMATEDSHAPE_H
