#ifndef _UI_UPDATEINFO_HEADER_
#define _UI_UPDATEINFO_HEADER_

#include <SFML/Graphics.hpp>

namespace ui
{
    enum class UIState { menuMain, settings, game };

    struct UpdateInfo
    {
        // Mouse Info
        sf::Vector2i msPosn;

        bool clickOn = false;
        bool hasItem = false;
        
        int stallFrame = false; // used to prevent multi-clicks when swapping states

        UIState curStateType = UIState::menuMain;
    };
}

namespace ui::updfnc
{
    typedef void (*fnct)(UpdateInfo&);

    void initNull(UpdateInfo&);
    void toMenuMainState(UpdateInfo&);
    void toSettingsState(UpdateInfo&);
    void toGameState(UpdateInfo&);
}


#endif