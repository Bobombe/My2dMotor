#include "moteur2d.h"
#include <stdexcept>
#include <iostream>

#include "eventmanager.h"

Moteur2D * Moteur2D::m_instance = 0;

Moteur2D * Moteur2D::getInstance()
{
    if (m_instance == 0)
    {
        m_instance = new Moteur2D();
        //m_instance->init();
    }
    return m_instance;
}

Moteur2D::Moteur2D()
{
    //ctor
    m_drawablesIndex = 0;
}

Moteur2D::~Moteur2D()
{
    //dtor
    if(m_instance)
        delete m_instance;

    // Tous les drawables sont g�r�s par le moteur et donc il faut les d�truire"
    for (unsigned int i = 0; i < m_drawables.size(); i++)
    {
        delete m_drawables.at(i);
    }
    delete m_window;
    // TO DO : D�truire le contenu des vectors
}

void Moteur2D::init(int width, int height)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), "Youpi", sf::Style::Default, settings);

    sf::View v = m_window->getDefaultView();
    m_view.setSize(v.getSize());
    m_view.setCenter(v.getCenter());
    updateView();
}
/*
void Moteur2D::setWindowSize(int width, int height)
{
    m_window->setSize(sf::Vector2u(width, height));

    sf::View v = m_window->getDefaultView();
    m_view.setSize(v.getSize());
    m_view.setCenter(v.getCenter());
    updateView();
}
//*/
void Moteur2D::run()
{

    EventManager em;
    m_t = m_clock.getElapsedTime();
    sf::Time t2;


    while(m_window->isOpen())
    {
        // On efface la fen�tre d�s le d�but pour permettre aux Updatables de d�ssiner
        m_window->clear();// efface la fen�tre

        t2 = m_clock.getElapsedTime();
        float s = (t2-m_t).asSeconds() ;

        // First called by eventmanager
        em.eventLoop(*m_window);

        //Then make the Updates needed before updating positions of objects (external forcies like gravity)
        for (unsigned int i =0; i<m_preUpdates.size(); i++)
        {
            m_preUpdates.at(i)->update(s);
        }

        //then update animated object according to interactions with other objects (collisions)
        for (unsigned int i =0; i<m_animatedObjects.size(); i++)
        {
            m_animatedObjects.at(i)->update(s);
        }

        //Then make the Updates needed after updating positions of objects (I don't know what yet)
        for (unsigned int i =0; i<m_postUpdates.size(); i++)
        {
            m_postUpdates.at(i)->update(s);
        }

        //And to finish draw all
        // Dessine tous les objets dessinables

        for (unsigned int i =0; i<m_preDraw.size(); i++)
        {
            m_window->draw(*m_preDraw.at(i));
        }
        for (unsigned int i =0; i<m_concreteBackgrounds.size(); i++)
        {
            sf::Sprite* sprite= m_concreteBackgrounds.at(i)->getSprite();
            if (sprite)
                m_window->draw(*sprite);
        }

        for (std::map<int,sf::Drawable*>::iterator it=m_drawables.begin(); it!=m_drawables.end(); ++it)
        {
            m_window->draw(*(it->second));
        }

        for (unsigned int i =0; i<m_postDraw.size(); i++)
        {
            m_window->draw(*m_postDraw.at(i));
        }

        m_window->display();// Affiche

        //MaJ temps
        m_t = t2;

    }
}

void Moteur2D::updateView()
{
    m_window->setView(m_view);
}


// Permet l'acc�s aux textures, si la texture est inexistante cette methode la cr�era.
sf::Texture* Moteur2D::getTexture(const std::string& imagePath)
{
    try
    {
        return &m_textures.at(imagePath);
    }
    catch (const std::out_of_range& oor)
    {
        // Texture in�xistante, je la charge
        sf::Texture t;
        t.loadFromFile(imagePath);
        m_textures.insert(std::pair<std::string, sf::Texture>(imagePath, t));
    }
    try
    {
        return &m_textures.at(imagePath);
    }
    catch (const std::out_of_range& oor)
    {
        // problem !
        std::cout << "Probl�me d'ajout de Texture" << std::endl;
        return 0;
    }
}

/*
void Moteur2D::addUpdatable(Updatable* u)
{
    m_updates.push_back(u);
}//*/

void Moteur2D::addKeyboardListener(KeyboardListener* kl)
{
    m_keyboardListeners.push_back(kl);
}

void Moteur2D::addMouseListener(MouseListener* ml)
{
    m_mouseListeners.push_back(ml);
}

int Moteur2D::addDrawable(sf::Drawable *d)
{
    m_drawablesIndex++;
    m_drawables[m_drawablesIndex] = d;
    return m_drawablesIndex;
}

void Moteur2D::deleteDrawable(int index)
{
    m_drawables.erase(index);
}

void Moteur2D::deleteFixedObject(FixedObject*f)
{
    for (unsigned int i = 0; i < m_fixedObjects.size(); i++)
    {
        if (f==m_fixedObjects.at(i))
        {
            m_fixedObjects.erase(m_fixedObjects.begin()+i);
        }
    }
}

void Moteur2D::deleteAnimatedObject(AnimatedObject*a)
{
    for (unsigned int i = 0; i < m_animatedObjects.size(); i++)
    {
        if (a==m_animatedObjects.at(i))
        {
            m_animatedObjects.erase(m_animatedObjects.begin()+i);
        }
    }
}

/*
FixedSprite * Moteur2D::addCollidable(const sf::Vector2f& pos, const std::string& imagePath)
{
    FixedSprite *fs = new FixedSprite(pos, imagePath);
    addCollidable(fs);
    return fs;
}
//*/
/*
Gravity * Moteur2D::setEarthGravity()
{
    Gravity * ret;
    if (m_gravities.size()>0)
    {
        ret = m_gravities.at(0);
        // On vide toutes les classes Gravity
        for (unsigned int i = 0; i<m_gravities.size(); i++)
        {
            m_gravities.at(i)->eraseObjects();
        }
        ret->setTerrestrianGravity();
    }
    else
    {
        ret = new Gravity();
        addGravity(ret);
    }

    // On affecte tous les sprites anim�s � la gravit� terrestre
    for (unsigned int i =0; i<m_colliders.size(); i++)
    {
        ret->addAnimatedObject(m_colliders.at(i));
    }
    return ret;
}
//*/


