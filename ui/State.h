#ifndef _UI_STATE_HEADER_
#define _UI_STATE_HEADER_

#include "Element.h"


namespace ui
{
    class Factory;

    class State
    {
    private:
        Element* m_topElement;
        // In sfml we must ensure that textures & fonts outlive their 
        // owners, so the state controls that
        std::vector<sf::Texture*> m_txtrs;
        std::vector<sf::Font*> m_fnts;

    public:
        State(); // All states should be constructed from a ui::Factory
        ~State();

        void update(UpdateInfo&);
        void render(sf::RenderWindow&);

        friend class ui::Factory;
    };
}


#endif