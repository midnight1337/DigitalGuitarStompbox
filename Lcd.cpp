#include "Lcd.h"

Lcd::Lcd(int *ptr_selectedEffect_1, int *ptr_selectedEffect_2, bool *ptr_isPlaying, String *ptr_effectNames)
{
    m_lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    m_ptr_selectedEffect_1 = ptr_selectedEffect_1;
    m_ptr_selectedEffect_2 = ptr_selectedEffect_2;
    m_ptr_isPlaying = ptr_isPlaying;
    m_ptr_effectNames = ptr_effectNames;
}

void Lcd::InitializeLcd()
{
    m_lcd->init();
    m_lcd->backlight();
}

void Lcd::PrintOnDisplay(uint8_t option)
{
    if (option == 0)
    {
        m_lcd->clear();
        m_lcd->print((*(m_ptr_effectNames + *m_ptr_selectedEffect_1)));
        m_lcd->setCursor(0, 1);
        m_lcd->print((*(m_ptr_effectNames + *m_ptr_selectedEffect_2)));
        if (*m_ptr_isPlaying == true)
        {
            m_lcd->setCursor(13, 0);
            m_lcd->print("<--");
        }
        else if (*m_ptr_isPlaying == false)
        {
            m_lcd->setCursor(13, 1);
            m_lcd->print("<--");
        }
    }
    // menu - effect 1
    else if (option == 1)
    {
        m_lcd->clear();
        m_lcd->print(String(*m_ptr_selectedEffect_1) + String(".") + (*(m_ptr_effectNames + *m_ptr_selectedEffect_1)));
        m_lcd->setCursor(13, 0);
        m_lcd->print("<->");
        m_lcd->setCursor(0, 1);
        m_lcd->print(String(*m_ptr_selectedEffect_2) + String(".") + (*(m_ptr_effectNames + *m_ptr_selectedEffect_2)));
    }
    // menu effect 2
    else if (option == 2)
    {
        m_lcd->clear();
        m_lcd->print(String(*m_ptr_selectedEffect_1) + String(".") + (*(m_ptr_effectNames + *m_ptr_selectedEffect_1)));
        m_lcd->setCursor(0, 1);
        m_lcd->print(String(*m_ptr_selectedEffect_2) + String(".") + (*(m_ptr_effectNames + *m_ptr_selectedEffect_2)));
        m_lcd->setCursor(13, 1);
        m_lcd->print("<->");
    }
}

// used for debugging
void Lcd::PrintOutputValue(int output)
{
    m_lcd->clear();
    m_lcd->print(output);
}