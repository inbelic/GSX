#ifndef _UI_DECORATORS_HEADER
#define _UI_DECORATORS_HEADER

#include "Decorator.h"

namespace ui::depfnc
{
    typedef Element* (*init)(Element*);

    Element* initBase(Element*);
    Element* initHover(Element*);
}

// When wrapping an Element with decorators we do so in the order
// such that for a Decorator, A, listed above Decorator, B, B is 
// child of A. Decorators will call their update function first
// and then its owned element. This is so that the base element
// will update on the frame and not the next
namespace ui
{
    class Hover
        : public Decorator 
    {
    public:
        Hover(Element*);
        virtual ~Hover();

        virtual void update(UpdateInfo&) override;
    };

    class Click
        : public Decorator
    {
    private:
        bool m_clickedLast = false;
        sf::Mouse::Button m_mb;

    public:
        Click(Element*,sf::Mouse::Button);
        virtual ~Click();

        virtual void update(UpdateInfo&) override;
    };

    class Drag
        : public Decorator
    {
    private:
        bool m_dragging = false;
        bool m_lastPressed = false;
        sf::Mouse::Button m_mb;

    public:
        Drag(Element*,sf::Mouse::Button);
        virtual ~Drag();

        virtual void update(UpdateInfo&) override;
    };

    class Functionality
        : public Decorator
    {
    private:
        updfnc::fnct m_updfunc = updfnc::initNull;

    public:
        Functionality(Element*);
        virtual ~Functionality(); 

        void giveUpdFunc(updfnc::fnct);

        void update(UpdateInfo&) override;
    };

    class Dependant 
        : public Decorator
    {
    private:
        Element* m_decDependant; // dependant might be wrapped 
        // sub-decorators will be owned but the dependant is not
        StatusTrait m_depTrait; // dependant trait
        StatusTrait m_sensTrait; // sensitive trait
        bool m_relation; // relations between the traits (if true then we want sens == dep, if false then sens =/= dep)


    public:
        Dependant(Element*,Element*,
                StatusTrait,StatusTrait, 
                bool, depfnc::init);
        virtual ~Dependant();

        virtual void update(UpdateInfo&) override;
    };
}



#endif