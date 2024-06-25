#include <dbg.h>
#include <motor.h>


enum pins
{
    pins_m0_right = 2,
    pins_m0_left = 3,
    pins_m0_pwm = 4,

    pins_m1_right = 5,
    pins_m1_left = 6,
    pins_m1_pwm = 7,

    pins_joy_switch = 8,
    pins_joy_x = A0,
    pins_joy_y = A1,
};


struct motor m0 = {0}, m1 = {0};

void setup()
{
    dbg_setup();
    motor_setup(&m0, pins_m0_right, pins_m0_left, pins_m0_pwm);
    motor_setup(&m1, pins_m1_right, pins_m1_left, pins_m1_pwm);
}

void loop()
{
    motor_set(&m0, 255);
}
