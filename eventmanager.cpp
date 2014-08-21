#include "eventmanager.h"
#include "moteur2d.h"

EventManager::EventManager()
{
    //ctor
}

EventManager::~EventManager()
{
    //dtor
}

void EventManager::eventLoop(sf::RenderWindow &window)
{

    while (window.pollEvent(m_e))
    {
        // Click sur la croix -> Fermeture
        if(m_e.type == sf::Event::Closed)
            window.close();

        // Appuis sur touche -> Appel des listener de clavier
        else if (m_e.type == sf::Event::KeyPressed)
        {
            std::vector <KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
            for (unsigned int i = 0; i<kls.size(); i++)
            {
                kls.at(i)->keyPressed(m_e.key.code);
            }
        }
        // Relachement d'une touche -> Appel des listener de clavier
        else if (m_e.type == sf::Event::KeyReleased)
        {
            std::vector <KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
            for (unsigned int i = 0; i<kls.size(); i++)
            {
                kls.at(i)->keyReleased(m_e.key.code);
            }
        }

        // Appuis sur un bouton de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseButtonPressed)
        {
            std::vector <MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (unsigned int i = 0; i<mls.size(); i++)
            {
                mls.at(i)->buttonPressed(m_e.mouseButton);
            }
        }
        // Relachement d'un bouton de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseButtonReleased)
        {
            std::vector <MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (unsigned int i = 0; i<mls.size(); i++)
            {
                mls.at(i)->buttonReleased(m_e.mouseButton);
            }
        }
        // Mouvement de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseMoved)
        {
            std::vector <MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (unsigned int i = 0; i<mls.size(); i++)
            {
                mls.at(i)->mouseMoved(m_e.mouseMove);
            }
        }
        // Mouvement molette de la souris -> Appel des listener de souris
        else if (m_e.type == sf::Event::MouseWheelMoved)
        {
            std::vector <MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (unsigned int i = 0; i<mls.size(); i++)
            {
                mls.at(i)->mouseWheel(m_e.mouseWheel);
            }
        }
    }

}
