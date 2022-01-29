#include "App.h"
#include "ui/Factory.h"

App::App()
{
    ui::fact::MenuMain mm = ui::fact::MenuMain();
    m_curState = mm.initState(sf::Vector2u(1920,1080));
    m_curStateType = ui::UIState::menuMain;
}

App::~App()
{
    if (m_curState != nullptr) delete m_curState;
}



// Private Functions
void App::manageUpdate(ui::UpdateInfo& uInfo)
{
    manageState(uInfo);
}

void App::manageState(ui::UpdateInfo& uInfo)
{
    if (uInfo.curStateType != m_curStateType)
    {
        delete m_curState;
        m_curStateType = uInfo.curStateType;

        uInfo.stallFrame = true;

        switch (m_curStateType)
        {
        case ui::UIState::menuMain:
            m_curState = ui::fact::MenuMain().initState(sf::Vector2u(1920,1080));
            break;
        
        case ui::UIState::settings:
            m_curState = ui::fact::Settings().initState(sf::Vector2u(1920,1080));
            break;

        case ui::UIState::game:
            m_curState = ui::fact::Game().initState(sf::Vector2u(1920,1080));
            break;
        }
    }
}






// Public Functions
void App::run()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080),"gsx");
    ui::UpdateInfo uInfo;

    while (window.isOpen())
    {
        sf::Event event;
        window.waitEvent(event);

        if (event.type == sf::Event::Closed) window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
        } 
        uInfo.msPosn = sf::Mouse::getPosition(window);
        window.clear();

        // We introduce a buffer so that we don't immediately click a
        // a button after swapping states
        // Not too concerend on performance due to stallFrame being false most of the time
        if (uInfo.stallFrame) uInfo.stallFrame = false; 
        else 
        {
            m_curState->update(uInfo);
            manageUpdate(uInfo);
        }
        
        m_curState->render(window);

        window.display(); 

    }
}
