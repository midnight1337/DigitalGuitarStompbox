#include "Logic.h"

Logic::Logic(int *ptr_input, int *ptr_output)
{
    m_effect = new GuitarEffects(ptr_input, ptr_output);
    m_lcd = new Lcd(&m_selectedEffect_1, &m_selectedEffect_2, &m_isPlaying, &m_effectNames[0]);
    m_ptr_input = ptr_input;
}

GuitarEffects *Logic::GetEffect()
{
    return m_effect;
}

Lcd *Logic::GetLcd()
{
    return m_lcd;
}

void Logic::ImplementEffect()
{
    switch (m_nowPlayingEffect)
    {
    case 0:
    {
        m_effect->Clean();
        break;
    }
    case 1:
    {
        m_effect->Distortion();
        break;
    }
    case 2:
    {
        m_effect->Fuzz();
        break;
    }
    case 3:
    {
        m_effect->Octaver();
        break;
    }
    default:
    {
        break;
    }
    }
}

void Logic::CheckForEvents()
{
    // Check for input signal clipping
    if (*m_ptr_input == 1023 || *m_ptr_input == 0)
    {
        PORTB |= (1 << PORTB3);
    }
    else
    {
        PORTB &= ~(1 << PORTB3);
    }
    // Check for 3PDT press
    if (((PINB & B00010000) >> 4) == 0 && m_switchState == false || ((PINB & B00100000) >> 5) == 0 && m_switchState == true)
    {
        m_switchState = !m_switchState;
        SwitchEffect();
    }
    // Check for menu button press
    if (((PINC & B00010) >> 1) == 0)
    {
        EffectsMenu();
    }
}

void Logic::SwitchEffect()
{
    m_isPlaying = !m_isPlaying;
    if (m_isPlaying == true)
    {
        m_nowPlayingEffect = m_selectedEffect_1;
    }
    else if (m_isPlaying == false)
    {
        m_nowPlayingEffect = m_selectedEffect_2;
    }
    m_lcd->PrintOnDisplay(0);
}

void Logic::UpdateEffect()
{
    if (m_isPlaying == true)
    {
        m_nowPlayingEffect = m_selectedEffect_1;
    }
    else if (m_isPlaying == false)
    {
        m_nowPlayingEffect = m_selectedEffect_2;
    }
}

void Logic::EffectsMenu()
{
    delay(m_delayTime);
    // selectedEffect_1 loop
    while (digitalRead(PUSHBUTTON_MENU) != 0)
    {
        if (digitalRead(PUSHBUTTON_NEXT) == 0)
        {
            m_selectedEffect_1++;
            if (m_selectedEffect_1 > m_effectsInTotal)
            {
                m_selectedEffect_1 = 0;
            }
            if (m_selectedEffect_1 == m_selectedEffect_2)
            {
                m_selectedEffect_1++;
                if (m_selectedEffect_1 > m_effectsInTotal)
                {
                    m_selectedEffect_1 = 0;
                }
            }
        }
        if (digitalRead(PUSHBUTTON_PREV) == 0)
        {
            m_selectedEffect_1--;
            if (m_selectedEffect_1 < 0)
            {
                m_selectedEffect_1 = m_effectsInTotal;
            }
            if (m_selectedEffect_1 == m_selectedEffect_2)
            {
                m_selectedEffect_1--;
                if (m_selectedEffect_1 < 0)
                {
                    m_selectedEffect_1 = m_effectsInTotal;
                }
            }
        }
        // update lcd
        delay(m_delayTime);
        m_lcd->PrintOnDisplay(1);
    }

    delay(m_delayTime);
    // selectedEffect_2 loop
    while (digitalRead(PUSHBUTTON_MENU) != 0)
    {
        if (digitalRead(PUSHBUTTON_NEXT) == 0)
        {
            m_selectedEffect_2++;
            if (m_selectedEffect_2 > m_effectsInTotal)
            {
                m_selectedEffect_2 = 0;
            }
            if (m_selectedEffect_2 == m_selectedEffect_1)
            {
                m_selectedEffect_2++;
                if (m_selectedEffect_2 > m_effectsInTotal)
                {
                    m_selectedEffect_2 = 0;
                }
            }
        }
        if (digitalRead(PUSHBUTTON_PREV) == 0)
        {
            m_selectedEffect_2--;
            if (m_selectedEffect_2 < 0)
            {
                m_selectedEffect_2 = m_effectsInTotal;
            }
            if (m_selectedEffect_2 == m_selectedEffect_1)
            {
                m_selectedEffect_2--;
                if (m_selectedEffect_2 < 0)
                {
                    m_selectedEffect_2 = m_effectsInTotal;
                }
            }
        }
        // update lcd
        delay(m_delayTime);
        m_lcd->PrintOnDisplay(2);
    }
    // update lcd
    delay(m_delayTime);
    m_lcd->PrintOnDisplay(0);
    UpdateEffect();
}

void Logic::InitializeHardware()
{
    uint8_t hardware[5] = {PUSHBUTTON_MENU, PUSHBUTTON_NEXT, PUSHBUTTON_PREV, SWITCH_3PDT_1, SWITCH_3PDT_2};
    uint8_t hardware_size = ((sizeof(hardware) / sizeof(hardware[0])));
    uint8_t LEDs[1] = {CLIPPING_LED};
    uint8_t leds_size = ((sizeof(LEDs) / sizeof(LEDs[0])));
    for (int i = 0; i < hardware_size; i++)
    {
        pinMode(hardware[i], INPUT_PULLUP);
    }
    for (int i = 0; i < leds_size; i++)
    {
        pinMode(LEDs[i], OUTPUT);
    }
}

String Logic::GetEffectName()
{
    return m_effectNames[m_nowPlayingEffect];
}
