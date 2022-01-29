#ifndef _UI_DRAWABLE_HEADER_
#define _UI_DRAWABLE_HEADER_

#include "Element.h"

namespace ui
{
    class Shape
        : public Element 
    {
    protected:
        sf::ConvexShape m_cs;
        sf::Color m_altColor;

        virtual void statusTrigger(StatusTrait) override;

    public:
        Shape(sf::Vector2f, sf::Vector2f);
        virtual ~Shape();

        void giveCS(sf::ConvexShape);
        void giveAltColor(sf::Color);

        virtual void movePosn(const sf::Vector2f&) override;
        virtual void scaleSize(const sf::Vector2f&) override;

        virtual void update(UpdateInfo&) override;
        virtual void render(sf::RenderWindow&) override;
    };

    class Text
        : public Element
    {
    protected:
        sf::Text* m_txt;
        sf::Color m_altColor;
        std::string m_str;

        virtual void statusTrigger(StatusTrait) override;

    public:
        Text(sf::Vector2f, sf::Vector2f);
        virtual ~Text();

        void giveTxt(sf::Text*);
        void giveAltColor(sf::Color);

        virtual void movePosn(const sf::Vector2f&) override;
        virtual void scaleSize(const sf::Vector2f&) override;

        virtual void update(UpdateInfo&) override;
        virtual void render(sf::RenderWindow&) override;
    };
}


#endif