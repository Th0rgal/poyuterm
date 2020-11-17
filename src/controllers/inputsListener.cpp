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
}

void onRightMove()
{
}

void onLeftMove()
{
}

void onDownMove()
{
}