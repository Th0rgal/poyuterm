#pragma once

#include "controllers/gameManager.hpp"

class ConsoleDisplay
{
public:
    ConsoleDisplay(InputsListener &inputsListener);
    void start();
private:
    InputsListener inputsListener;
};