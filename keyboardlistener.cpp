#include "ketboardlistener.h"

#include "moteur2d.h"
KeyboardListener::KeyboardListener()
{
    //ctor
    Moteur2D::getInstance()->addKeyboardListener(this);
}
