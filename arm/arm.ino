#include <SMS_STS.h>

#include "dbg.h"

#define array_len(arr) (sizeof(arr) / sizeof((arr)[0]))

#define delta(x, y)                             \
    ({                                          \
        typeof(x) _x = (x);                     \
        typeof(y) _y = (y);                     \
        _x > _y ? _x - _y : _y - _x;            \
    })

struct servo { int id; unsigned pos; };

enum { servos_cap = 3 };
struct servo servos[servos_cap] = {0};
unsigned servos_len = 0;

enum mode
{
    mode_nil = 0,
    mode_discover = 1,
    mode_set_id = 2,
    mode_test = 3,
} mode = mode_discover;

enum mode action = mode_test;
int action_set_id_to = 3;

SMS_STS st;

void setup() {
    Serial.begin(115200);

    Serial1.begin(1000000);
    st.pSerial = &Serial1;
}

void discover(void)
{
    for (unsigned id = 1; id < 100 && servos_len < array_len(servos); ++id) {
        if (st.Ping(id) < 0) continue;
        struct servo *servo = servos + servos_len;
        servos_len++;

        servo->id = id;
        servo->pos = st.ReadPos(servo->id);

        dbgf("[discover] id=%d, pos=%d", servo->id, servo->pos);
    }

    mode = servos_len > 0 ? action : mode_nil;
}

void set_id(struct servo *servo, int id)
{
    dbgf("[set-id] id=%d, to=%d", servos->id, id);

    st.unLockEprom(servos->id);
    st.writeByte(servos->id, SMS_STS_ID, id);
    st.LockEprom(id);

    servo->id = id;
    mode = mode_nil;

}

void wait_idle(struct servo *servo)
{
    unsigned prev = 0;
    delay(150);

    do {
        prev = servo->pos;
        delay(10);
        servo->pos = st.ReadPos(servo->id);
    } while (delta(servo->pos, prev));
}

// speed caps at around 3000
// acc caps at 100
void move(struct servo *servo, float angle, unsigned speed, unsigned acc = 100)
{
    unsigned pos = round((abs(angle) * 4096));
    st.WritePosEx(servo->id, pos, speed, acc);
    wait_idle(servo);
}

void test(void)
{
    float start[servos_cap] = {0};
    for (size_t i = 0; i < servos_len; ++i) {
        struct servo *servo = servos + i;
        start[i] = (float) servo->pos / 4096;
        move(servo, 0.50, 2000, 100);
    }

    for (size_t i = 0; i < servos_len; ++i) {
        struct servo *servo = servos + i;
        move(servo, 0.25, 2000, 100);
        move(servo, 0.75, 2000, 100);
        move(servo, 0.50, 2000, 100);
    }

    for (int i = servos_len - 1; i >= 0; --i) {
        struct servo *servo = servos + i;
        move(servo, start[i], 2000, 100);
    }

    mode = mode_nil;
}

void loop() {
    dbgf("[mode] %d", mode);

    switch (mode)
    {
    case mode_nil: while(true);
    case mode_discover: { discover(); break; }
    case mode_set_id: { set_id(servos, action_set_id_to); break; }
    case mode_test: { test(); break; }
    default: break;
    }
}
