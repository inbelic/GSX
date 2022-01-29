#include "Element.h"

using namespace ui;

// (De)Constructor
Element::Element(sf::Vector2f posn, sf::Vector2f size)
    : m_posn{posn}, m_size{size}
{
    initStatus();
}

Element::~Element()
{
    for (auto child : m_children) delete child;
}



// Private Functions
void Element::initStatus()
{
    m_status[StatusTrait::Updating] = true;
    m_status[StatusTrait::Rendering] = true;
    m_status[StatusTrait::Hovering] = false;
    m_status[StatusTrait::Active] = false;
}


// Protected Functions
void Element::setPosn(sf::Vector2f posn) {  m_posn = posn; }

void Element::setSize(sf::Vector2f size) {  m_size = size; }



void Element::moveChildren(const sf::Vector2f& movement)
{
    for (auto child : m_children) child->movePosn(movement);
}

void Element::scaleChildren(const sf::Vector2f& scalars)
{
    for (auto child : m_children) child->scaleSize(scalars);
}

void Element::updateChildren(UpdateInfo& uInfo)
{
    for (auto child : m_children) child->update(uInfo);
}

void Element::renderChildren(sf::RenderWindow& window)
{
    for (auto child : m_children) child->render(window);
}



void Element::statusTrigger(StatusTrait) {}



// Public Functions

const sf::Vector2f& Element::getPosn() { return m_posn;}

const sf::Vector2f& Element::getSize() { return m_size; }

bool Element::getStatusTrait(StatusTrait st) { return m_status[st]; }



void Element::movePosn(const sf::Vector2f& movement) 
{ 
    setPosn(getPosn() + movement);
    moveChildren(movement);
}

void Element::scaleSize(const sf::Vector2f& scalars) 
{
    auto curSize = getSize();
    setSize(sf::Vector2f(scalars.x*curSize.x, scalars.y*curSize.y));
    scaleChildren(scalars);
}

void Element::swapStatusTrait(StatusTrait st)
{
    m_status[st] = !m_status[st];
    statusTrigger(st);
}



void Element::setID(std::string id) { m_id = id; }

std::string Element::getID() { return m_id; }

void Element::addChild(Element* child) { m_children.emplace_back(child); }



void Element::update(UpdateInfo& uInfo)
{
    if (getStatusTrait(StatusTrait::Updating)) updateChildren(uInfo);
}

void Element::render(sf::RenderWindow& window)
{
    if (getStatusTrait(StatusTrait::Rendering)) renderChildren(window);
}
