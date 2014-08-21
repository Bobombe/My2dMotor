//*
#include "fixedobject.h"
#include "moteur2d.h"

FixedObject::FixedObject()
{
    m_indexOfDO = -1;
    Moteur2D::getInstance()->addFixedObject(this);
}

FixedObject::~FixedObject()
{
    Moteur2D::getInstance()->deleteFixedObject(this);
    if (m_drawableObject)
    {
        delete m_drawableObject;
    }

    if (m_indexOfDO>=0)
    {
        Moteur2D::getInstance()->deleteDrawable(m_indexOfDO);
    }
}
//*/
