#ifndef _APP_HEADER_
#define _APP_HEADER_

#include "ui/State.h"

class App
{
private:
    ui::State* m_curState;
    ui::UIState m_curStateType;

    void manageUpdate(ui::UpdateInfo&);
    void manageState(ui::UpdateInfo&); 

public:
    App();
    ~App();

    void run();
};


#endif