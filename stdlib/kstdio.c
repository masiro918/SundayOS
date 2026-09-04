#include "../include/kstdio.h"
#include "../include/types.h"

#include <stdarg.h>

int timer_count = 0;
static int counter_printk = 0;

static int print_unsigned_base(unsigned int value, unsigned int base, int uppercase) {
    char buf[32];
    int i = 0;
    int written = 0;
    const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

    if (value == 0) {
        putc('0');
        return 1;
    }

    while (value > 0) {
        buf[i++] = digits[value % base];
        value /= base;
    }

    while (i-- > 0) {
        putc(buf[i]);
        written++;
    }

    return written;
}

static int print_signed(int value) {
    unsigned int u;
    int written = 0;

    if (value < 0) {
        putc('-');
        written++;
        u = (unsigned int)(-(long)value);
    } else {
        u = (unsigned int)value;
    }

    return written + print_unsigned_base(u, 10, 0);
}

int printk(const char *s) {
    putc('[');
    print_signed(timer_count);
    putc('.');
    print_signed(counter_printk);
    putc(']');
    counter_printk++;
    puts(s);
    return 0;
}