#include <ncurses.h>
#include <functional>
#include "controllers/inputsListener.hpp"
#include <chrono>

using namespace std::chrono;

void handleInputs(std::function<void(int)> loop)
{
    int inputCode;
    high_resolution_clock::time_point previousTime = high_resolution_clock::now();
    while ((inputCode = getch()) != KEY_ENTER)
    {
        if (inputCode == ERR)
        {
            loop(int((high_resolution_clock::now() - previousTime).count()*1e-6));
            previousTime = high_resolution_clock::now();
        }
        else
        {
            onKeyPressed(inputCode);
        }
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
        translateDown();
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