#ifndef _UI_FACTORY_HEADER_
#define _UI_FACTORY_HEADER_

#include "Decorators.h"
#include "Drawable.h"
#include "State.h"

namespace ui
{
    class Factory
    {
    protected:
        void setElement(State*,Element*);
        void giveTxtr(State*,sf::Texture*);
        void giveFnt(State*,sf::Font*);

    public:
        Factory();
        virtual ~Factory();

        virtual State* initState(sf::Vector2u) = 0;
    };

    namespace fact
    {
        class MenuMain
            : public Factory 
        {
        public:
            MenuMain();
            ~MenuMain();

            State* initState(sf::Vector2u) override;
        };
    
        class Settings
            : public Factory
        {
        public:
            Settings();
            ~Settings();

            State* initState(sf::Vector2u) override;
        };

        class Game
            : public Factory
        {
        public:
            Game();
            ~Game();

            State* initState(sf::Vector2u) override;
        };
    }
}

#endif