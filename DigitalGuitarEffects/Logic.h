#ifndef LOGIC_H
#define LOGIC_H
#include <Arduino.h>
#include "GuitarEffects.h"
#include "HardwareVariables.h"
#include "Lcd.h"

class Logic
{
private:
    GuitarEffects *m_effect;
    Lcd *m_lcd;
    int *m_ptr_input;
    int m_selectedEffect_1 = 0;
    int m_selectedEffect_2 = 1;
    int m_nowPlayingEffect = m_selectedEffect_1;
    bool m_isPlaying = true;
    bool m_switchState = true;
    uint8_t m_delayTime = 250;
    String m_effectNames[4] = {"Clean", "Distortion", "Fuzz", "Octave"};
    uint8_t m_effectsInTotal = ((sizeof(m_effectNames) / sizeof(m_effectNames[0])) - 1);

    void EffectsMenu();
    void SwitchEffect();
    void UpdateEffect();

public:
    Logic(int *ptr_input, int *ptr_output);
    GuitarEffects *GetEffect();
    Lcd *GetLcd();
    void ImplementEffect();
    void InitializeHardware();
    void CheckForEvents();

    // Used for debugging
    String GetEffectName();
};

#endif