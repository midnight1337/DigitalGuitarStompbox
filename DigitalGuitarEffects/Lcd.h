#ifndef LCD_H
#define LCD_H
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

class Lcd
{
private:
    LiquidCrystal_I2C *m_lcd;
    int *m_ptr_selectedEffect_1;
    int *m_ptr_selectedEffect_2;
    bool *m_ptr_isPlaying;
    String *m_ptr_effectNames;

public:
    Lcd(int *ptr_selectedEffect_1, int *ptr_selectedEffect_2, bool *ptr_isPlaying, String *ptr_effectNames);
    void PrintOnDisplay(uint8_t option);
    void InitializeLcd();

    // Used for debugging
    void PrintOutputValue(int output);
};

#endif