#include "Decorator.h"

using namespace ui;

// (De)Constructor
Decorator::Decorator(Element* element)
    : Element(element->getPosn(), element->getSize()), p_element{element}
{
}

Decorator::~Decorator()
{
    if (p_ownsElement) delete p_element;
}



// Public Functions 
const sf::Vector2f& Decorator::getPosn() {  return p_element->getPosn(); }

const sf::Vector2f& Decorator::getSize() {  return p_element->getSize(); }

bool Decorator::getStatusTrait(StatusTrait st) {  return p_element->getStatusTrait(st); }



void Decorator::movePosn(const sf::Vector2f& movement)
{
    p_element->movePosn(movement);
    setPosn(p_element->getPosn());
}

void Decorator::scaleSize(const sf::Vector2f& scalars)
{
    p_element->scaleSize(scalars);
    setSize(p_element->getSize());
}

void Decorator::swapStatusTrait(StatusTrait st)
{
    p_element->swapStatusTrait(st);
}



void Decorator::setOwnership(bool ownsElement) { p_ownsElement = ownsElement; }



void Decorator::update(UpdateInfo& uInfo)
{
    if (p_ownsElement) p_element->update(uInfo);
}

void Decorator::render(sf::RenderWindow& window)
{
    if (p_ownsElement) p_element->render(window);
}

