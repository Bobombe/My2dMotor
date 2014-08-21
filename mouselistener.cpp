#include "ketboardlistener.h"

#include "moteur2d.h"
MouseListener::MouseListener()
{
    //ctor
    Moteur2D::getInstance()->addMouseListener(this);
}
