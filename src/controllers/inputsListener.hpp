#pragma once
#include <functional>

void handleInputs(std::function<void(int)> loop);

void onKeyPressed(int code);

void translateLeft();
void translateRight();
void translateDown();