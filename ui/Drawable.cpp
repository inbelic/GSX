#include "Drawable.h"

using namespace ui;

// ##############################
// Drawable
// ############################

// (De)Constructor
Shape::Shape(sf::Vector2f posn, sf::Vector2f size)
    : Element(posn,size)
{
}

Shape::~Shape()
{
}



// Protected Function Overrides
void Shape::statusTrigger(StatusTrait st)
{
    switch (st)
    {
    case StatusTrait::Hovering:
    {
        sf::Color temp = m_cs.getFillColor();
        m_cs.setFillColor(m_altColor);
        m_altColor = temp;
        break;
    } 
    default:
        break;
    }
}


// Public Function Overrides
void Shape::giveCS(sf::ConvexShape cs) { m_cs = cs; }

void Shape::giveAltColor(sf::Color altColor) { m_altColor = altColor; }



void Shape::movePosn(const sf::Vector2f& movement)
{
    setPosn(getPosn() + movement);
    moveChildren(movement);
    m_cs.move(movement);
}

void Shape::scaleSize(const sf::Vector2f& scalars)
{
    auto curSize = getSize();
    setSize(sf::Vector2f(scalars.x*curSize.x, scalars.y*curSize.y));
    scaleChildren(scalars);
    m_cs.scale(scalars);
}



void Shape::update(UpdateInfo& uInfo)
{
    if (getStatusTrait(StatusTrait::Updating)) updateChildren(uInfo);
}

void Shape::render(sf::RenderWindow& window)
{
    if (getStatusTrait(StatusTrait::Rendering))
    {
        window.draw(m_cs);
        renderChildren(window);
    }
}


// ##############################
// Text
// ############################


// (De)Constructor
Text::Text(sf::Vector2f posn, sf::Vector2f size)
    : Element(posn,size)
{
}

Text::~Text()
{
    if (m_txt != nullptr) delete m_txt;
}



// Protected Function Overrides
void Text::statusTrigger(StatusTrait st)
{
    switch (st)
    {
    case StatusTrait::Hovering:
    {
        sf::Color temp = m_txt->getFillColor();
        m_txt->setFillColor(m_altColor);
        m_altColor = temp;
        break;
    } 
    default:
        break;
    }
}


// Public Function Overrides
void Text::giveTxt(sf::Text* txt) { m_txt = txt; }

void Text::giveAltColor(sf::Color altColor) { m_altColor = altColor; }



void Text::movePosn(const sf::Vector2f& movement)
{
    setPosn(getPosn() + movement);
    moveChildren(movement);
    m_txt->move(movement);
}

void Text::scaleSize(const sf::Vector2f& scalars)
{
    auto curSize = getSize();
    setSize(sf::Vector2f(scalars.x*curSize.x, scalars.y*curSize.y));
    scaleChildren(scalars);
    m_txt->scale(scalars);
}



void Text::update(UpdateInfo& uInfo)
{
    if (getStatusTrait(StatusTrait::Updating)) updateChildren(uInfo);
}

void Text::render(sf::RenderWindow& window)
{
    if (getStatusTrait(StatusTrait::Rendering))
    {
        window.draw(*(m_txt));
        renderChildren(window);
    }
}