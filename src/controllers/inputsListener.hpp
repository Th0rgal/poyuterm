#pragma once
#include <functional>

void handleInputs(std::function<void()> applyMechanics);

void onKeyPressed(int code);

void translateLeft();
void translateRight();
void translateDown();