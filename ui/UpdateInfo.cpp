#include "UpdateInfo.h"
#include <iostream>

void ui::updfnc::initNull(UpdateInfo&)
{
}

void ui::updfnc::toMenuMainState(UpdateInfo& uInfo)
{
    uInfo.curStateType = ui::UIState::menuMain;
}

void ui::updfnc::toSettingsState(UpdateInfo& uInfo)
{
    uInfo.curStateType = ui::UIState::settings;
}

void ui::updfnc::toGameState(UpdateInfo& uInfo)
{
    uInfo.curStateType = ui::UIState::game;
}

