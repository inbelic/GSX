#include "State.h"

using namespace ui;

State::State()
{
}

State::~State()
{
    if (m_topElement != nullptr) delete m_topElement;
    for (auto fnt : m_fnts) delete fnt;
    for (auto txtr : m_txtrs) delete txtr;
}

void State::update(UpdateInfo& uInfo)
{
    if (m_topElement != nullptr) m_topElement->update(uInfo);
}

void State::render(sf::RenderWindow& window)
{
    if (m_topElement != nullptr) m_topElement->render(window);
}