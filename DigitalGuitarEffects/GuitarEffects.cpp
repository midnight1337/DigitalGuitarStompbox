#include "GuitarEffects.h"

GuitarEffects::GuitarEffects(int *ptr_input, int *ptr_output)
{
    m_ptr_input = ptr_input;
    m_ptr_output = ptr_output;
}

void GuitarEffects::MapInput()
{
    m_offsetInput = map(*m_ptr_input, 0, 1023, -512, 511);
}

void GuitarEffects::Clean()
{
    *m_ptr_output = *m_ptr_input;
}

void GuitarEffects::Distortion()
{
    MapInput();
    *m_ptr_output = ((pow(m_offsetInput, 2)) / 256);
    if (*m_ptr_output > 823)
        *m_ptr_output = 823;
}

void GuitarEffects::Fuzz()
{
    MapInput();
    *m_ptr_output = (((float)m_offsetInput / (20 + abs((float)m_offsetInput))) * (512)) + (512);
}

void GuitarEffects::Octaver()
{
    MapInput();
    *m_ptr_output = map(abs(m_offsetInput), 0, 512, 256, 768);
}

// not used
void GuitarEffects::Overdrive()
{
    MapInput();
    if (m_offsetInput > 0)
        *m_ptr_output = (((1 + (1 - pow(m_e, -m_offsetInput))) * m_resolution) * 0.5);
    else
        *m_ptr_output = (((1 + (-1 + pow(m_e, m_offsetInput))) * m_resolution) * 0.5);
}

// not used
void GuitarEffects::HardClipping()
{
    if (*m_ptr_input > 511)
        *m_ptr_output = *m_ptr_input + 25;
    else if (*m_ptr_input < 511)
        *m_ptr_output = *m_ptr_input - 25;
    if (*m_ptr_input > 723)
        *m_ptr_output = 723;
    else if (*m_ptr_input < 300)
        *m_ptr_output = 300;
}

// not used
void GuitarEffects::Echo()
{
}
