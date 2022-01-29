#ifndef _UI_DECORATOR_HEADER_
#define _UI_DECORATOR_HEADER_

#include "Element.h"

namespace ui::fnc
{
    typedef bool (*Active)(ui::Element*);
    typedef void (*Update)(ui::Element*);
}

namespace ui
{
    class Decorator
        : public Element
    {
    protected:
        Element* p_element;
        bool p_ownsElement = true; // Defaults to true, but dependant classes don't want to own

    public:
        Decorator(Element*);
        virtual ~Decorator();

        virtual const sf::Vector2f& getPosn() override;
        virtual const sf::Vector2f& getSize() override;
        virtual bool getStatusTrait(StatusTrait) override;

        virtual void movePosn(const sf::Vector2f&) override; // All overrides must should call moveChildren
        virtual void scaleSize(const sf::Vector2f&) override; // All overrides must should call scaleChildren
        virtual void swapStatusTrait(StatusTrait) override;

        void setOwnership(bool);

        virtual void update(UpdateInfo&) override; // All overrides must should call updateChildren
        virtual void render(sf::RenderWindow&) override; // All overrides should call renderChildren
    };

}

#endif