#ifndef _UI_ELEMENT_HEADER
#define _UI_ELEMENT_HEADER

#include "UpdateInfo.h"
#include <vector>
#include <string>

namespace ui
{
    enum class StatusTrait { Active, Hovering, Rendering, Updating };

    class Element
    {
    private:
        sf::Vector2f m_posn;
        sf::Vector2f m_size;

        std::map<StatusTrait,bool> m_status; // Use of map allows less setters/getters
        std::string m_id = "NA";

        std::vector<Element*> m_children;

        void initStatus();

    protected:
        void setPosn(sf::Vector2f);
        void setSize(sf::Vector2f);

        void moveChildren(const sf::Vector2f&);
        void scaleChildren(const sf::Vector2f&); 
        void updateChildren(UpdateInfo&);
        void renderChildren(sf::RenderWindow&);

        virtual void statusTrigger(StatusTrait);

    public:
        Element(sf::Vector2f, sf::Vector2f);
        virtual ~Element();

        virtual const sf::Vector2f& getPosn();
        virtual const sf::Vector2f& getSize();
        virtual bool getStatusTrait(StatusTrait);

        virtual void movePosn(const sf::Vector2f&); // All overrides must should call moveChildren
        virtual void scaleSize(const sf::Vector2f&); // All overrides must should call scaleChildren
        virtual void swapStatusTrait(StatusTrait);

        void setID(std::string);
        std::string getID();
        void addChild(Element*);

        virtual void update(UpdateInfo&); // All overrides should call updateChildren
        virtual void render(sf::RenderWindow&); // All overrides should call renderChildren
    };
}




#endif
