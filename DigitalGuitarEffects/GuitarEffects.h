#ifndef GUITAREFFECTS_H
#define GUITAREFFECTS_H
#include <Arduino.h>

class GuitarEffects
{
private:
    int *m_ptr_input;
    int *m_ptr_output;
    int m_offsetInput;
    void MapInput();

public:
    GuitarEffects(int *ptr_input, int *ptr_output);
    const int m_resolution = 1023; // to ma byc publiczne bo prywatne albo inicjalizowane w konstruktorze przydziela inna wartosc, czemu? heh nie wiem ;-D
    const float m_e = 2.718281828459;
    void Clean();
    void Distortion();
    void Fuzz();
    void Octaver();
    void Overdrive();
    void HardClipping();
    void Echo();
};

#endif