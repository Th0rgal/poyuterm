#include <ncurses.h>
#include <functional>
#include "controllers/inputsListener.hpp"

void handleInputs(std::function<void()> loop)
{
    int inputCode;
    while ((inputCode = getch()) != KEY_ENTER)
    {
        if (inputCode == ERR)
            loop();
        else
            onKeyPressed(inputCode);
    }
}

void onKeyPressed(int code)
{
    switch (code)
    {
    case KEY_LEFT:
        translateLeft();
        break;

    case KEY_RIGHT:
        translateRight();
        break;

    case KEY_DOWN:
        translateRight();
        break;
    }
}

void translateLeft()
{
}

void translateRight()
{
}

void translateDown()
{
}