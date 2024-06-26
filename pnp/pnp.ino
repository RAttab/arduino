#include <dbg.h>

enum pins { pins_pwm = 4 };

void setup(void)
{
    pinMode(pins_pwm, OUTPUT);
}

void loop(void)
{
    analogWrite(pins_pwm, LOW);
}
