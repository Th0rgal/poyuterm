#pragma once
#include <functional>

void handleInputs(std::function<void(double)> loop);

void onKeyPressed(int code);

void translateLeft();
void translateRight();
void translateDown();