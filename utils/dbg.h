#pragma once

#include <avr/pgmspace.h>

// -----------------------------------------------------------------------------
// dbg
// -----------------------------------------------------------------------------

static void dbg_setup(void) { Serial.begin(9600); }

static void dbg_(const __FlashStringHelper *fmt_, ...)
{
    va_list args;
    va_start(args, fmt_);

    char fmt[256] = {0};
    strlcpy_PF(fmt, fmt_, sizeof(fmt));
    
    char buffer[256] = {0};
    int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
    Serial.write(buffer, n);

    va_end(args);
}

#define dbg(msg) dbg_(F(msg "\n"))
#define dbgf(fmt, ...) dbg_(F(fmt "\n"), __VA_ARGS__)

size_t dbg_bytes(const uint8_t *in,  size_t len, char *out, size_t cap)
{
    char *it = out;
    const char *const end = it + cap;

    it += snprintf(it, end - it, "%zu:[ ", len);
    for (size_t i = 0; i < len; ++i)
        it += snprintf(it, end - it, "%02x ", in[i]);
    it += snprintf(it, end - it, "]");

    return it - out;
}
