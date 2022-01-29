#include "Decorators.h"

using namespace ui;


//  #####################
//  HOVER
//  #####################

Hover::Hover(Element* element)
    : Decorator(element)
{
}

Hover::~Hover()
{
}

void Hover::update(UpdateInfo& uInfo)
{
    auto posn = getPosn();
    auto size = getSize();
    auto mPosn = uInfo.msPosn;
    
    if ((posn.x <= mPosn.x && posn.y <= mPosn.y) &&
        (posn.x + size.x >= mPosn.x && posn.y + size.y >= mPosn.y))
    {
        if (!p_element->getStatusTrait(StatusTrait::Hovering))
        {
            p_element->swapStatusTrait(StatusTrait::Hovering);
        }
    }
    else if (p_element->getStatusTrait(StatusTrait::Hovering))
    {
        p_element->swapStatusTrait(StatusTrait::Hovering);
    }

    if (p_ownsElement) p_element->update(uInfo);
}



// #####################
// Click
// #####################
Click::Click(Element* element, sf::Mouse::Button mb)
    : Decorator(element), m_mb{mb}
{
}

Click::~Click()
{
}

void Click::update(UpdateInfo& uInfo)
{
    if (m_clickedLast)
    {
        if (getStatusTrait(StatusTrait::Active)) swapStatusTrait(StatusTrait::Active);
        if(!sf::Mouse::isButtonPressed(m_mb)) m_clickedLast = false; 
    }
    else
    {
        if(sf::Mouse::isButtonPressed(m_mb) && getStatusTrait(StatusTrait::Hovering)) 
        {
            m_clickedLast = true;
            if (!getStatusTrait(StatusTrait::Active)) swapStatusTrait(StatusTrait::Active);
        }
    }

    if (p_ownsElement) p_element->update(uInfo);
}

//  #####################
//  Drag
//  #####################

Drag::Drag(Element* element, sf::Mouse::Button mb)
    : Decorator(element), m_mb{mb}
{
}

Drag::~Drag()
{
}

void Drag::update(UpdateInfo& uInfo)
{
    bool curPressed = sf::Mouse::isButtonPressed(m_mb);
    if (curPressed && getStatusTrait(StatusTrait::Hovering))
    {
        if (!uInfo.hasItem && !m_lastPressed) 
        {
            m_dragging = true;
            uInfo.hasItem = true;
        }
    } 
    else if (m_dragging)
    {
        m_dragging = false;
        uInfo.hasItem = false;
    }

    if (m_dragging)
    {
        auto difference = sf::Vector2f(uInfo.msPosn.x,uInfo.msPosn.y) - p_element->getPosn();
        auto size = p_element->getSize();
        difference.x -= size.x / 2;
        difference.y -= size.y / 2;
        p_element->movePosn(difference);
    }

    m_lastPressed = curPressed;
    
    if (p_ownsElement) p_element->update(uInfo);
}



// #######################
// Functionality
// #######################

Functionality::Functionality(Element* element)
    : Decorator(element)
{
}

Functionality::~Functionality()
{
}

void Functionality::giveUpdFunc(updfnc::fnct updfunc)
{
    m_updfunc = updfunc;
}

void Functionality::update(UpdateInfo& uInfo)
{
    if (p_element->getStatusTrait(StatusTrait::Active)) m_updfunc(uInfo);
    if (p_ownsElement) p_element->update(uInfo);
}



//  #####################
//  Dependant
//  #####################

Dependant::Dependant(Element* wrappedElement, Element* dependant, 
                    StatusTrait depTrait, StatusTrait sensTrait, 
                    bool relation, depfnc::init initFunc)
    : Decorator(wrappedElement), m_depTrait{depTrait}, m_sensTrait{sensTrait}, m_relation{relation}
{
    m_decDependant = initFunc(dependant);
}

Dependant::~Dependant()
{
    delete m_decDependant;
}

void Dependant::update(UpdateInfo& uInfo)
{
    m_decDependant->update(uInfo);

    bool d_trait = m_decDependant->getStatusTrait(m_depTrait);
    bool s_trait = p_element->getStatusTrait(m_sensTrait);
    if (m_relation && (d_trait != s_trait)) p_element->swapStatusTrait(m_sensTrait);
    if (!m_relation && (d_trait == s_trait)) p_element->swapStatusTrait(m_sensTrait);

    if (p_ownsElement) p_element->update(uInfo);
}



// ####################
// Dependant functions
// ####################
namespace ui::depfnc
{
    Element* initBase(Element* dependant)
    {
        Decorator* empty = new Decorator(dependant);
        empty->setOwnership(false);
        return empty;
    }

    Element* initHover(Element* dependant)
    {
        Hover* hover = new Hover(dependant);
        hover->setOwnership(false);
        return hover;
    }
}