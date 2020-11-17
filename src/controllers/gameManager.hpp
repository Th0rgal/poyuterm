#pragma once

void loop();

class InputsListener
{
public:
    InputsListener();
    void onKeyPressed(int code);

private:
    void onRightMove();
    void onLeftMove();
    void onDownMove();
};