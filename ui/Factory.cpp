#include "Factory.h"
using namespace ui;

Factory::Factory()
{
}

Factory::~Factory()
{
}

void Factory::setElement(State* state, Element* element)
{
    state->m_topElement = element;
}

void Factory::giveTxtr(State* state, sf::Texture* txtr)
{
    state->m_txtrs.emplace_back(txtr);
}

void Factory::giveFnt(State* state, sf::Font* fnt)
{
    state->m_fnts.emplace_back(fnt);
}


using namespace fact;

MenuMain::MenuMain()
    : Factory()
{
}

MenuMain::~MenuMain()
{
}

State* MenuMain::initState(sf::Vector2u winSize)
{
    State* n_state = new State();
    Element* container = new Element(sf::Vector2f(0.f,0.f),sf::Vector2f(winSize.x,winSize.y));

    float xSize = (float) winSize.x / 3;
    float ySize = (float) winSize.y / 5;
    auto size = sf::Vector2f(xSize,ySize);
    float offset = ySize / 3;
    sf::Font* fnt = new sf::Font();
    fnt->loadFromFile("data/UbuntuMono-R.ttf");
    giveFnt(n_state,fnt);
    
    for (int i = 0; i < 3; i++)
    {   
        auto posn = sf::Vector2f(xSize, ySize);
        sf::ConvexShape bg = sf::ConvexShape(4);
        bg.setPoint(0,sf::Vector2f(xSize,offset + i*(ySize + 10.f)));
        bg.setPoint(1,sf::Vector2f(2*xSize,offset + i*(ySize + 10.f)));
        bg.setPoint(2,sf::Vector2f(2*xSize,offset + ySize + i*(ySize + 10.f)));
        bg.setPoint(3,sf::Vector2f(xSize,offset + ySize + i*(ySize + 10.f)));
        bg.setFillColor(sf::Color(100,30,22));

        ui::Shape* shp1 = new ui::Shape(sf::Vector2f(xSize,offset + i*(ySize + 10.f)),
            sf::Vector2f(xSize,ySize));
        shp1->giveCS(bg);
        shp1->giveAltColor(sf::Color(115,45,37));
        
        ui::Text* n_txt = new ui::Text(shp1->getPosn(),shp1->getSize());
        sf::Text* txt = new sf::Text();
        txt->setFillColor(sf::Color::White);
        txt->setFont(*fnt);
        txt->setPosition(shp1->getPosn() + sf::Vector2f(10.f,10.f));
        txt->setCharacterSize(100);
        n_txt->giveAltColor(sf::Color::Black);

        ui::Functionality* funct = new ui::Functionality(shp1);
        switch (i)
        {
        case 0:
            funct->giveUpdFunc(updfnc::toMenuMainState);
            txt->setString("Main Menu");
            break;
        
        case 1:
            funct->giveUpdFunc(updfnc::toSettingsState);
            txt->setString("Settings");
            break;
        
        case 2:
            funct->giveUpdFunc(updfnc::toGameState);
            txt->setString("Player");
            break;
        }
        n_txt->giveTxt(txt);
        ui::Hover* txtHover = new ui::Hover(n_txt);
        shp1->addChild(txtHover);

        ui::Click* click = new ui::Click(funct,sf::Mouse::Button::Left);
        ui::Hover* hover = new ui::Hover(click);
 
        container->addChild(hover);
    }

    setElement(n_state,container);
    return n_state;
}




Settings::Settings()
    : Factory()
{
}

Settings::~Settings()
{
}

State* Settings::initState(sf::Vector2u winSize)
{
    State* n_state = new State();
    Element* container = new Element(sf::Vector2f(0.f,0.f),sf::Vector2f(winSize.x,winSize.y));

    float xSize = (float) winSize.x / 3;
    float ySize = (float) winSize.y / 5;
    auto size = sf::Vector2f(xSize,ySize);
    float offset = ySize / 3;
    for (int i = 0; i < 1; i++)
    {   
        auto posn = sf::Vector2f(xSize, ySize);
        sf::ConvexShape bg = sf::ConvexShape(4);
        bg.setPoint(0,sf::Vector2f(xSize,offset + i*(ySize + 10.f)));
        bg.setPoint(1,sf::Vector2f(2*xSize,offset + i*(ySize + 10.f)));
        bg.setPoint(2,sf::Vector2f(2*xSize,offset + ySize + i*(ySize + 10.f)));
        bg.setPoint(3,sf::Vector2f(xSize,offset + ySize + i*(ySize + 10.f)));
        bg.setFillColor(sf::Color(100,30,22));

        ui::Shape* shp1 = new ui::Shape(sf::Vector2f(xSize,offset + i*(ySize + 10.f)),
            sf::Vector2f(xSize,ySize));
        shp1->giveCS(bg);
        shp1->giveAltColor(sf::Color(115,45,37));

        ui::Functionality* funct = new ui::Functionality(shp1);
        switch (i)
        {
        case 0:
            funct->giveUpdFunc(updfnc::toMenuMainState);
            break;
        }

        ui::Click* click = new ui::Click(funct,sf::Mouse::Button::Left);
        ui::Hover* hover = new ui::Hover(click);
 
        container->addChild(hover);
    }

    setElement(n_state,container);
    return n_state;
}




Game::Game()
    : Factory()
{
}

Game::~Game()
{
}

State* Game::initState(sf::Vector2u winSize)
{
    State* n_state = new State();
    Element* container = new Element(sf::Vector2f(0.f,0.f),sf::Vector2f(winSize.x,winSize.y));

    float xSize = (float) winSize.x / 3;
    float ySize = (float) winSize.y / 5;
    auto size = sf::Vector2f(xSize,ySize);
    float offset = ySize / 3;
    for (int i = 0; i < 2; i++)
    {   
        auto posn = sf::Vector2f(xSize, ySize);
        sf::ConvexShape bg = sf::ConvexShape(4);
        bg.setPoint(0,sf::Vector2f(xSize,offset + i*(ySize + 10.f)));
        bg.setPoint(1,sf::Vector2f(2*xSize,offset + i*(ySize + 10.f)));
        bg.setPoint(2,sf::Vector2f(2*xSize,offset + ySize + i*(ySize + 10.f)));
        bg.setPoint(3,sf::Vector2f(xSize,offset + ySize + i*(ySize + 10.f)));
        bg.setFillColor(sf::Color(100,30,22));

        ui::Shape* shp1 = new ui::Shape(sf::Vector2f(xSize,offset + i*(ySize + 10.f)),
            sf::Vector2f(xSize,ySize));
        shp1->giveCS(bg);
        shp1->giveAltColor(sf::Color(115,45,37));

        ui::Functionality* funct = new ui::Functionality(shp1);
        switch (i)
        {
        case 0:
            funct->giveUpdFunc(updfnc::toGameState);
            break;

        case 1:
            funct->giveUpdFunc(updfnc::toMenuMainState);
            break;
        }

        ui::Click* click = new ui::Click(funct,sf::Mouse::Button::Left);
        ui::Hover* hover = new ui::Hover(click);
 
        container->addChild(hover);
    }

    setElement(n_state,container);
    return n_state;
    
}

