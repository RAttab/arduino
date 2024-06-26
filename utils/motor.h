
// -----------------------------------------------------------------------------
// motor
// -----------------------------------------------------------------------------

struct motor
{
    struct { unsigned left, right, pwm; } pins;
    int speed;
};

enum { motor_speed_cap = 255 };

static void motor_setup(
        struct motor *motor, unsigned right, unsigned left, unsigned pwm)
{
    pinMode(motor->pins.right = right, OUTPUT);
    pinMode(motor->pins.left = left, OUTPUT);
    pinMode(motor->pins.pwm = pwm, OUTPUT);
    motor->speed = 0;
}

static void motor_set(struct motor *motor, int speed)
{
    motor->speed = constrain(speed, -motor_speed_cap, motor_speed_cap);

    if (!motor->speed) {
        digitalWrite(motor->pins.left, LOW);
        digitalWrite(motor->pins.right, LOW);
        digitalWrite(motor->pins.pwm, abs(0));
        return;
    }

    if (motor->speed < 0) {
        digitalWrite(motor->pins.left, LOW);
        digitalWrite(motor->pins.right, HIGH);
    }
    else {
        digitalWrite(motor->pins.left, HIGH);
        digitalWrite(motor->pins.right, LOW);
    }

    analogWrite(motor->pins.pwm, abs(motor->speed));
}

