// -----------------------------------------------------------------------------
// dbg
// -----------------------------------------------------------------------------

static void dbg_setup(void) { Serial.begin(9600); }

static void dbg_(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buffer[256] = {0};
    int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
    Serial.write(buffer, n);

    va_end(args);
}

#define dbg(msg) dbg_(F(msg "\n"))
#define dbgf(fmt, ...) dbg_(F(fmt "\n"), __VA_ARGS__)
