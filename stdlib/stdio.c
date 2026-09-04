#include "../include/stdio.h"
#include "../include/types.h"

static int counter_printk = 0;

extern uint8_t putc(char c);

int puts(const char *s) {
    int len = 0;
	while (*s) {
        len++;
        putc(*s++);
    }
    len++;
    return len;
}

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

int printf(const char *fmt, ...) {
    va_list ap;
    int written = 0;

    va_start(ap, fmt);

    while (*fmt) {
        if (*fmt != '%') {
            putc(*fmt++);
            written++;
            continue;
        }

        fmt++; // ohita '%'

        if (*fmt == '\0') {
            break;
        }

        switch (*fmt) {
            case '%':
                putc('%');
                written++;
                break;

            case 'c': {
                char c = (char)va_arg(ap, int);
                putc(c);
                written++;
                break;
            }

            case 's': {
                const char *s = va_arg(ap, const char *);
                if (!s) s = "(null)";
                written += puts(s); // käyttää puts-funktiota
                break;
            }

            case 'd':
            case 'i': {
                int v = va_arg(ap, int);
                written += print_signed(v);
                break;
            }

            case 'u': {
                unsigned int v = va_arg(ap, unsigned int);
                written += print_unsigned_base(v, 10, 0);
                break;
            }

            case 'x': {
                unsigned int v = va_arg(ap, unsigned int);
                written += print_unsigned_base(v, 16, 0);
                break;
            }

            case 'X': {
                unsigned int v = va_arg(ap, unsigned int);
                written += print_unsigned_base(v, 16, 1);
                break;
            }

            default:
                putc('%');
                putc(*fmt);
                written += 2;
                break;
        }

        fmt++;
    }

    va_end(ap);
    return written;
}
