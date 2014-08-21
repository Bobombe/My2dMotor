#ifndef GRAVITY_H
#define GRAVITY_H

#include "animatedobject.h"
#include "updatable.h"
#include <vector>
#include "SFML/Graphics.hpp"

class Gravity : public Updatable
{
    public:
        enum GravityType
        {
            UNIFORM, // Direction et intensit� de la gravit� fixe. Parfait pour simuler la gravit� sur terre
            PONCTUAL_UNIFORM, // Intensit� fixe, la direction d�pend des positions de l'objet et du centre de gravit�
            PONCTUAL // g = G*m/d, dir comme PONCTUAL_UNIFORM
        };


        // Constructeur par d�faut construit une gravit� terrestre uniforme
        Gravity();
        virtual ~Gravity();
        // Methode pour la mise � jour
        void update(float seconds);

        // Supprime tous les objets de sa liste d'objets affect�s par sa gravit�
        void eraseObjects();
        // Regarde dans la liste d'objets anim�s du Moteur2D et les ajoute � sa liste d'objets affect�s par sa gravit�
        void addAllAnimatedObject();
        // Ajoute un objet � sa liste d'objets affect�s par sa gravit�
        void addAnimatedObject(AnimatedObject * ao)
        {
            m_objects.push_back(ao);
        }

        // SETTERS
        // Exemple gravit� Uniforme
        void setTerrestrianGravity();
        // Exemple gravit� Uniforme Ponctuelle
        void setTerrestrianPointGravity();
        // Exemple gravit� Ponctuelle pour une echelle au system solaire
        void setSolarSystemGravity();
        void setPixMetersScale(float value)
        {
            m_pixMetersScale = value;
        }
        void setGravityVector(const sf::Vector2f & gv)
        {
            m_gravityVector.x = gv.x;
            m_gravityVector.y = gv.y;
        }
        void setGravityType(GravityType gt)
        {
            m_gravityType = gt;
        }
        void setMass(float m)
        {
            m_mass = m;
        }
        void setTemporalScale(float temporalScale)
        {
            m_temporalScale = temporalScale;
        }
    protected:
        std::vector<AnimatedObject*> m_objects;

        // Echelle pixel/metres
        float m_pixMetersScale;

        // Carac de la gravit�
        // Type de gravit�
        GravityType m_gravityType;
        // Direction ou point de gravit�, d�pend du type de gravit�
        sf::Vector2f m_gravityVector;
        // Force gravitationnelle
        float m_forceGravitationnelle;
        // Masse de l'objet cr�ant la gravit�
        float m_mass;
        // Rapport temporel : temps simu sur temps r�el, ex : =86400 -> 1seconde vaut un jour
        float m_temporalScale;
    private:
};

#endif // GRAVITY_H
