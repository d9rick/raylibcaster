#include "button.h"

bool isButtonPressed(Button* button, Vector2 mousePos)
{
    if(CheckCollisionPointRec(mousePos, button->rect))
    {
        return true;
    }

    return false;
}

void drawButton(Button* button)
{
    DrawRectangleRec(button->rect, button->color);
    DrawText(button->text, button->rect.x + 10, button->rect.y + 10, 20, WHITE);
}

Button* newButton(char* text, int x, int y, int width, int height, Color color)
{
    Button* button = malloc(sizeof(Button));
    button->rect = (Rectangle){x, y, width, height};
    button->color = color;
    button->text = text;

    return button;
}