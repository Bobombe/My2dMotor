#ifndef MOTEUR2D_H
#define MOTEUR2D_H

#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include "updatable.h"
#include "animatedobject.h"
#include "fixedobject.h"
#include "mouselistener.h"
#include "ketboardlistener.h"
#include "gravity.h"
#include "view.h"
#include "concretebackground.h"

class Moteur2D
{
    public:
        static Moteur2D* getInstance();
        void run();

        //Gravity * setEarthGravity();

        void updateView();

        // ADDERS
        int addDrawable(sf::Drawable *d);

        void addPreDrawable(sf::Drawable* d)
        {
            m_preDraw.push_back(d);
        }

        void addPostDrawable(sf::Drawable* d)
        {
            m_postDraw.push_back(d);
        }

        void addConcreteBackground(ConcreteBackground* cb)
        {
            m_concreteBackgrounds.push_back(cb);
        }

        void addFixedObject(FixedObject* fo)
        {
            m_fixedObjects.push_back(fo);
        }
        //FixedSprite * addCollidable(const sf::Vector2f& pos, const std::string& imagePath);

        void addAnimatedObject(AnimatedObject* ao)
        {
            m_animatedObjects.push_back(ao);
        }

        void addKeyboardListener(KeyboardListener* kl);
        void addMouseListener(MouseListener* ml);

        void addPreUpdate(Updatable *u)
        {
            m_preUpdates.push_back(u);
        }

        void addPostUpdate(Updatable *u)
        {
            m_postUpdates.push_back(u);
        }

        //Suppression
        void deleteDrawable(int index);
        void deleteFixedObject(FixedObject*f);
        void deleteAnimatedObject(AnimatedObject*a);

        //GETTERS
        View * getView()
        {
            return &m_view;
        }
        sf::RenderWindow & getWindow()
        {
            return *m_window;
        }

        sf::Texture* getTexture(const std::string& imagePath);
        const std::vector <KeyboardListener*>& getKeyboardListeners()
        {
            return m_keyboardListeners;
        }
        const std::vector <MouseListener*>& getMouseListeners()
        {
            return m_mouseListeners;
        }
        const std::vector <FixedObject*>& getFixedObjects()
        {
            return m_fixedObjects;
        }
        const std::vector <AnimatedObject*>& getAnimatedObjects()
        {
            return m_animatedObjects;
        }
        const std::vector <ConcreteBackground*>& getConcreteBackgrounds()
        {
            return m_concreteBackgrounds;
        }
        sf::Time getTime()
        {
            return m_clock.getElapsedTime();
        }

        // SETTERS
        //void setWindowSize(int width, int height);
        void init(int width=800, int height=600);

    protected:
        Moteur2D();
        virtual ~Moteur2D();

        static Moteur2D * m_instance;

        sf::RenderWindow *m_window;
        View m_view;

        std::map<std::string, sf::Texture> m_textures;
        //std::vector <Updatable*> m_updates;


        // First called by eventmanager
        std::vector <KeyboardListener*> m_keyboardListeners;
        std::vector <MouseListener*> m_mouseListeners;

        //Then make the Updates needed before updating positions of objects (external forcies like gravity)
        std::vector <Updatable*> m_preUpdates;

        //then update animated object according to interactions with other objects (collisions)
        std::vector <AnimatedObject*> m_animatedObjects;
        std::vector <FixedObject*> m_fixedObjects;

        //Then make the Updates needed after updating positions of objects (I don't know what yet)
        std::vector <Updatable*> m_postUpdates;

        //-------- And to finish draw all --------\\

        // TO DO : Pour m_preDraw et m_postDraw : passer en map pouvant avoir plusieurs index �gaux repr�sentant la profondeur
        // Dessinables avant perso et autres
        std::vector <sf::Drawable*> m_preDraw;

        // Background tengible
        std::vector <ConcreteBackground*> m_concreteBackgrounds;

        // Dessins au niveau du perso
        std::map <int, sf::Drawable*> m_drawables;
        int m_drawablesIndex;

        // Dessinables apr�s perso et autres
        std::vector <sf::Drawable*> m_postDraw;

        sf::Clock m_clock;
        sf::Time m_t;

    private:
};

#endif // MOTEUR2D_H
