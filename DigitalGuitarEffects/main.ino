#include "GuitarEffects.h"
#include "Logic.h"
#include "Lcd.h"

/* Program Variables */
int input;
int output;
Logic logic = Logic(&input, &output);

void setup()
{
    InitializeADCRegisters();
    InitializePortRegisters();
    logic.InitializeHardware();
    logic.GetLcd()->InitializeLcd();
    logic.GetLcd()->PrintOnDisplay(0);
}

void loop()
{
    input = ADC;
    logic.CheckForEvents();
    logic.ImplementEffect();
    DAC();
}

void DAC()
{
    PORTD = output & B11111111;
    if ((((output >> 8) & B00000010) >> 1) == 1)
    {
        PORTB |= (1 << PORTB1);
    }
    else
    {
        PORTB &= (~(1 << PORTB1));
    }

    if (((output >> 8) & B00000001) == 1)
    {
        PORTB |= (1 << PORTB0);
    }
    else
    {
        PORTB &= (~(1 << PORTB0));
    }
}

void InitializeADCRegisters()
{
    ADCSRA = 0;
    ADMUX |= (0 << REFS1) | (1 << REFS0) | (0 << ADLAR);
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS0); // set ADC clock with 32 prescaler- 16mHz/32=500kHz, 500KHz/13 = 38.46KHz sampling rate
    ADCSRB = 0;
    DIDR0 = B00000001;
}

void InitializePortRegisters()
{
    DDRD = B11111111;
    PORTD = B00000000;
    DDRB = B11111;
    PORTB = B00000;
}

// used for debugging
void DACTEST()
{
    for (int i = 0; i < 1023; i++)
    {
        output = i;
        DAC();
    }
}
