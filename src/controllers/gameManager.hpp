#pragma once

void loop();

class InputsListener
{
public:
    InputsListener();

private:
    void onKeyPressed(int code);
    void onRightMove();
    void onLeftMove();
    void onDownMove();
};